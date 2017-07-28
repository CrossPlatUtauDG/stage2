#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>

#include "Note.h"
#include "FileParser.h"

#define DEBUG true

using namespace std;

FileParser::FileParser() { }
FileParser::~FileParser() { }

std::vector<Note*> FileParser::parse(std::string filepath) {
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
				std::string keyName = key.substr(0, key.find("."));
				std::string keyProp = key.substr(key.find(".") + 1, key.size());

#if DEBUG				
				std::clog << "DEBUG: Results from line parsing:\n";
				std::clog << "key = " << key << "\n"
					<< "value = " << value << "\n"
					<< "keyName = " << keyName << "\n"
					<< "keyProp = " << keyProp << "\n\n";
#endif					
				// Set globals TODO: this needs all the properties a Note does
				if (keyName == "global") {
					if (keyProp == "vb") globalVB = value;
					else if (keyProp == "tempo") globalTempo = std::stod(value);
					else if (keyProp == "flags") globalFlags = value;
					else if (keyProp == "pitch") globalPitch = value;
					else if (keyProp == "length") globalLength = std::stoi(value);
					else if (keyProp == "vb") globalVB = value;
					else std::cerr << "Error: Invalid property: " << keyProp << std::endl << std::endl;
				} else {
					unsigned int noteId = std::stoi(keyName);
					unsigned int oldListSize = notes.size();
					if (noteId >= notes.size()) {
#if DEBUG
						std::clog << "DEBUG: Current notes size: " << notes.size() << std::endl;
#endif 						
						notes.resize(noteId + 1);
#if DEBUG
						std::clog << "DEBUG: New Notes size: " << notes.size() << "\n";
#endif				
					}
					
					bool isNoteNew = false;
					if (notes[noteId] == nullptr) {
						notes[noteId] = new Note(noteId, globalContent, globalLength, globalPitch, globalVelocity, globalTempo,
							globalFlags, globalRest, globalVB, globalModulation, globalPitchCode, globalEnv);
						isNoteNew = true;
					}

					if (keyProp == "content") notes[noteId]->setContent(value);
					else if (keyProp == "length") notes[noteId]->setLength(std::stoi(value));
					else if (keyProp == "pitch") notes[noteId]->setPitch(value);
					else if (keyProp == "tempo") notes[noteId]->setTempo(std::stod(value));
					else if (keyProp == "vel") notes[noteId]->setVelocity(std::stoi(value));
					else if (keyProp == "flags") notes[noteId]->setFlags(value);
					else if (keyProp == "rest") notes[noteId]->setRestLength(std::stoi(value));
					else if (keyProp == "vb") notes[noteId]->setVbPath(value);
					else if (keyProp == "mod") notes[noteId]->setModulation(std::stoi(value));
					else if (keyProp == "consonant") notes[noteId]->setModulation(std::stoi(value));
					else if (keyProp == "overlap") notes[noteId]->setModulation(std::stoi(value));
					else if (keyProp == "preutterance") notes[noteId]->setModulation(std::stoi(value));
					else if (keyProp == "pitdata") notes[noteId]->setPitchCode(value);
					//else if (noteProp == "env") notes[std::stoi(noteNum)]->envelope)[]
					//TODO: make envelopes work...
					else if (isNoteNew) { //Invalid new note. Revert vector resize.
						cout << "Error: Invalid property: " << keyProp << std::endl;
						cout << "Error: Resizing vector back from " << notes.size() << " to " << oldListSize << std::endl;
						delete notes[noteId];
						notes.resize(oldListSize);
					} else {
						cout << "Error: Invalid property: " << keyProp << std::endl;
					}
				}
			}
		}
	} else {
		throw std::runtime_error("s2s file could not be opened");
	}
	deleteEmptyNotes(&notes);
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

void FileParser::deleteEmptyNotes(std::vector<Note*> *noteList) {
#if DEBUG
	std::clog << std::endl << "DEBUG: Filling up empty notes" << std::endl;
#endif
	int emptyNotes = 0;
	for (unsigned int i = 0; i < noteList->size(); i++) {
		if (noteList->at(i) == nullptr) {
			noteList->erase(noteList->begin()+i);
			i--;
		}
	}
#if DEBUG
	std::clog << "DEBUG: " << emptyNotes << " empty notes were deleted" << std::endl << std::endl;
#endif
}
