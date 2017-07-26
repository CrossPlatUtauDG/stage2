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
				
				int noteindex = std::stoi(noteNum);
#if DEBUG				
				std::clog << "DEBUG: Results from line parsing:\n";
				std::clog << "key = " << key << "\n" << "value = " << value << "\n"
					<< "noteNum = " << noteNum << "\n" << "NoteProp = "
					<< noteProp << "\n\n";
#endif					
				// Set globals
				if (noteNum == "global") {
					if (noteProp == "vb") globalVB = value;
					else if (noteProp == "tempo") globalTempo = std::stod(value);
					else if (noteProp == "flags") globalFlags = value;
					else if (noteProp == "pitch") globalPitch = value;
					else if (noteProp == "length") globalLength = std::stoi(value);	
					else std::cerr << "Error: Invalid property: " << noteProp << std::endl;
					cout << "past this \n";
				}
				// enable/disable auto note counting
				else {
					// count notes, set properties
					if (autoCountNote && std::stoi(noteNum) >= notes.size()) {
#if DEBUG
						cout << "Current notes size: " << notes.size() << std::endl;
#endif 						
						notes.resize(std::stoi(noteNum) + 1);
#if DEBUG
						cout << "New Notes size: " << notes.size() << "\n";
#endif						
					}
					if (notes[noteindex] == nullptr) notes[noteindex] =
						new Note(globalContent, globalLength, globalPitch, globalVelocity, globalTempo, 
							globalFlags, globalRest, globalVB, globalModulation, globalPitchCode, globalEnv);

					if (noteProp == "content") notes[noteindex]->setContent(value);
					else if (noteProp == "length") notes[noteindex]->setLength(std::stoi(value));
					else if (noteProp == "pitch") notes[noteindex]->setPitch(value);
					else if (noteProp == "tempo") notes[noteindex]->setTempo(std::stod(value));
					else if (noteProp == "vel") notes[noteindex]->setVelocity(std::stoi(value));
					else if (noteProp == "flags") notes[noteindex]->setFlags(value);
					else if (noteProp == "rest") notes[noteindex]->setRestLength(std::stoi(value));
					else if (noteProp == "vb") notes[noteindex]->setVbPath(value);
					else if (noteProp == "mod") notes[noteindex]->setModulation(std::stoi(value));
					else if (noteProp == "pitdata") notes[noteindex]->setPitchCode(value);
					else if (noteProp == "env") notes[noteindex]->setEnvelope(envFromStr(value));
					else cout << "Invalid property: " << noteProp << std::endl;
				}
			}
		}
	}
	
	return notes;
}

vector<int> FileParser::envFromStr(std::string envstr) {
	vector<std::string> envPointsStrs;
	vector<int> envPoints;
	int envPointIndex = 0;
#if DEBUG
	std::clog << "DEBUG: Attempting to convert env " << envstr << std::endl;
#endif	
	for (int i = 0; i < envstr.length(); i++) {
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
		for (int i = 0; i < noteID.size(); i++) {
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