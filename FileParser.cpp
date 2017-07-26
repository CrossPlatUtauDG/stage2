#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Note.h"
#include "FileParser.h"

#define DEBUG true

using namespace std;

FileParser::FileParser() { }
FileParser::~FileParser() { }

std::vector<Note*> FileParser::parse(std::string filepath) {
	bool autoCountNote = true;

	std::ifstream s2s;
	s2s.open(filepath);
	if (s2s.is_open()) {
		std::string line;
		while (getline(s2s, line)) {
#if DEBUG 
			std::clog << "DEBUG: Working on line: " << line << "\n";
			std::clog << "DEBUG: isLineValid returns " << std::noboolalpha << isLineValid(line) << "\n\n";
#endif			
			if (isLineValid(line)) {
				// Parse line
				std::string key = line.substr(0, line.find("="));
				std::string value = line.substr(line.find("=") + 1, line.size());
				std::string noteNum = key.substr(0, key.find("."));
				std::string noteProp = key.substr(key.find(".") + 1, key.size());

#if DEBUG				
				std::clog << "DEBUG: Results from line parsing:\n";
				std::clog << "key = " << key << "\n" << "value = " << value << "\n"
					<< "noteNum = " << noteNum << "\n" << "NoteProp = "
					<< noteProp << "\n\n";
#endif					
				// Set globals TODO: this needs all the properties a Note does
				if (noteNum == "global") {
					if (noteProp == "vb") globalVB = value;
					else if (noteProp == "tempo") globalTempo = std::stod(value);
					else if (noteProp == "flags") globalFlags = value;
					else if (noteProp == "pitch") globalPitch = value;
					else if (noteProp == "length") globalLength = std::stoi(value);	
					else if (noteProp == "vb") globalVB = value;
					else std::cerr << "Error: Invalid property: " << noteProp << std::endl;
					cout << "past this \n";
				}
				// enable/disable auto note counting
				else {
					// count notes, set properties
					unsigned int oldListSize = notes.size();
					if (autoCountNote && (unsigned int)std::stoi(noteNum) >= notes.size()) {
#if DEBUG
						std::clog << "DEBUG: Current notes size: " << notes.size() << std::endl;
#endif 						
						notes.resize(std::stoi(noteNum) + 1);
#if DEBUG
						std::clog << "DEBUG: New Notes size: " << notes.size() << "\n";
#endif						
					}
					
					bool isNoteNew = false;
					if (notes[std::stoi(noteNum)] == nullptr) {
						notes[std::stoi(noteNum)] = new Note(globalContent, globalLength, globalPitch, globalVelocity, globalTempo,
							globalFlags, globalRest, globalVB, globalModulation, globalPitchCode, globalEnv);
						isNoteNew = true;
					}

					if (noteProp == "content") notes[std::stoi(noteNum)]->setContent(value);
					else if (noteProp == "length") notes[std::stoi(noteNum)]->setLength(std::stoi(value));
					else if (noteProp == "pitch") notes[std::stoi(noteNum)]->setPitch(value);
					else if (noteProp == "tempo") notes[std::stoi(noteNum)]->setTempo(std::stod(value));
					else if (noteProp == "vel") notes[std::stoi(noteNum)]->setVelocity(std::stoi(value));
					else if (noteProp == "flags") notes[std::stoi(noteNum)]->setFlags(value);
					else if (noteProp == "rest") notes[std::stoi(noteNum)]->setRestLength(std::stoi(value));
					else if (noteProp == "vb") notes[std::stoi(noteNum)]->setVbPath(value);
					else if (noteProp == "mod") notes[std::stoi(noteNum)]->setModulation(std::stoi(value));
					else if (noteProp == "pitdata") notes[std::stoi(noteNum)]->setPitchCode(value);
					//else if (noteProp == "env") notes[std::stoi(noteNum)]->envelope)[]
					//TODO: make envelopes work...
					else if (isNoteNew) { //Invalid new note. Revert vector resize.
						cout << "Error: Invalid property: " << noteProp << std::endl;
						cout << "Error: Resizing vector back from " << notes.size() << " to " << oldListSize << std::endl;
						delete notes[std::stoi(noteNum)];
						notes.resize(oldListSize);
					} else {
						cout << "Error: Invalid property: " << noteProp << std::endl;
					}
				}
			}
		}
	}
	fillInvalidNotes(&notes);
	return notes;
}

vector<int> FileParser::envFromStr(std::string envstr) {
	vector<std::string> envPointsStrs;
	vector<int> envPoints;
	int envPointIndex = 0;
#if DEBUG
	std::clog << "DEBUG: Attempting to convert env " << envstr << std::endl;
#endif	
	for (unsigned int i = 0; i < envstr.length(); i++) {
		if (envstr[i] == ',') { 
			envPointIndex++;
#if DEBUG
			std::clog << "DEBUG: Envelope point " << std::to_string(envPointIndex)
				<< " = " << envPointsStrs[envPointIndex];
#endif
		}
		else envPointsStrs[envPointIndex][i] = envstr[i];
	}
	
	envPointIndex = 0;
	
	for (string str: envPointsStrs) {
		envPoints[envPointIndex] = std::stoi(str);		
		envPointIndex++;
	}
	
	return envPoints;
}

bool FileParser::isLineValid(std::string line) {
	//Checks if the line is empty or is a comment
	if (line.empty() || line.at(0) == '#')
		return false;

	//Checks if the line contains an = sign
	if (line.find("=") == std::string::npos) {
		std::cerr << "Error: Invalid line: " << line << std::endl;
		return false;
	}

	//Checks if key follows the noteID.property format
	std::string key = line.substr(0, line.find("="));
	if (key.find(".") == std::string::npos) {
		std::cerr << "Error: Invalid key: " << line << std::endl;
		return false;
	}

	//Checks if noteID is valid
	std::string noteID = line.substr(0, key.find("."));
	if (noteID != "global") {
		for (unsigned int i = 0; i < noteID.size(); i++) {
			if (!isdigit(noteID[i])) {
				std::cerr << "Error: Invalid noteID: " << line << std::endl;
				return false;
			}
		}
	}

	//Checks if value is not empty
	std::string value = line.substr(line.find("=") + 1, line.size());
	if (value.empty()) {
		std::cerr << "Error: Value is empty: " << line << std::endl;
		return false;
	}

	return true;
}

void FileParser::fillInvalidNotes(std::vector<Note*> *notelist) {
#if DEBUG
	std::clog << std::endl << "DEBUG: Filling up empty notes" << std::endl;
#endif
	int emptyNotes = 0;
	for (unsigned int i = 0; i < notelist->size(); i++) {
		if (notelist->at(i) == nullptr) {
			notelist->at(i) = new Note(globalContent, globalLength, globalPitch, globalVelocity, globalTempo,
				globalFlags, globalRest, globalVB, globalModulation, globalPitchCode, globalEnv);
#if DEBUG
			std::clog << "DEBUG: Filled up empty note: " << i << std::endl;
#endif
			emptyNotes++;
		}
	}
#if DEBUG
	std::clog << "DEBUG: " << emptyNotes << " notes were filled" << std::endl << std::endl;
#endif
}