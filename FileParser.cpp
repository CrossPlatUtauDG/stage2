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

std::vector<Note*> FileParser::parse(std::string filepath)
{
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
				std::string noteProperty = key.substr(key.find(".") + 1, key.size());
#if DEBUG				
				std::clog << "DEBUG: Results from line parsing:\n";
				std::clog << "key = " << key << "\n" << "value = " << value << "\n"
					<< "noteNum = " << noteNum << "\n" << "noteProperty = "
					<< noteProperty << "\n\n";
#endif					
				// Set globals
				if (noteNum == "global") {
					if (noteProperty == "VB") globalVB = value;
					else if (noteProperty == "tempo") globalTempo = std::stod(value);
					else if (noteProperty == "flags") globalFlags = value;
					else if (noteProperty == "pitch") globalPitch = value;
					else if (noteProperty == "length") globalLength = std::stoi(value);
					else std::cerr << "Error: Invalid property: " << noteProperty << std::endl;
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
					if (notes[std::stoi(noteNum)] == nullptr) notes[std::stoi(noteNum)] =
						new Note("a", globalLength, globalPitch, 100, globalTempo, globalFlags);

					if (noteProperty == "content") notes[std::stoi(noteNum)]->setContent(value);
					else if (noteProperty == "length") notes[std::stoi(noteNum)]->setLength(std::stoi(value));
					else if (noteProperty == "pitch") notes[std::stoi(noteNum)]->setPitch(value);
					else if (noteProperty == "tempo") notes[std::stoi(noteNum)]->setTempo(std::stod(value));
					else if (noteProperty == "vel") notes[std::stoi(noteNum)]->setVelocity(std::stoi(value));
					else if (noteProperty == "flags") notes[std::stoi(noteNum)]->setFlags(value);
					else cout << "Invalid property: " << noteProperty << std::endl;
				}
			}
		}
	}

	//TODO: calculate offset and whatnot, invoke tools

	return notes;
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