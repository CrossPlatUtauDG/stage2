#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Note.h"
#include "fileparse.h"

#define DEBUG true

using namespace std;
 
parser::parser() { }
parser::~parser() { }
 
vector<Note*> parser::fparse(std::string filepath)
{
	int noteCount;
	string globalVB;
	double globalTempo;
	string globalFlags;
	string globalPitch;
	int globalLength;
	bool autoCountNote = true;

	vector<Note*> notes;
	ifstream s2f;
	s2f.open(filepath);
	
	if (s2f.is_open()) {
		string line;
		while (getline(s2f, line)) {
#if DEBUG 
			cout << "working on line " << line << "\n";
			cout << "islnvalid returns " << std::noboolalpha << islnvalid(line) << "\n\n";
#endif			
			if (islnvalid(line)) {
				// parse line
				string key = line.substr(0, line.find("="));
				string value = line.substr(line.find("=") + 1, line.size());
				string noteNum = key.substr(0, key.find("."));
				string noteProperty = key.substr(key.find(".")+1, key.size());
#if DEBUG				
				cout << "Results from line parsing:\n";
				cout << "key = " << key << "\n" << "value = " << value << "\n"
					<< "noteNum = " << noteNum << "\n" << "noteProperty" 
					<< noteProperty << "\n\n";
#endif					
				// set globals
				if (noteNum == "global") {
					if (noteProperty == "VB") globalVB = value;
					else if (noteProperty == "tempo") globalTempo = stod(value);
					else if (noteProperty == "flags") globalFlags = value;
					else if (noteProperty == "pitch") globalPitch = value;
					else if (noteProperty == "length") globalLength = stoi(value);
					else cout << "Invalid property: " << noteProperty << endl;
				} 
				// enable/disable auto note counting
				else {
					// count notes, set properties
					if (autoCountNote && stoi(noteNum) >= notes.size()) {
#if DEBUG
						cout << "Current notes size: " << notes.size() << endl;
#endif 						
						notes.resize(stoi(noteNum) + 1);
#if DEBUG
						cout << "New Notes size: " << notes.size() << "\n";
#endif						
					}
					if (notes[stoi(noteNum)] == nullptr) notes[stoi(noteNum)] = 
					    new Note("a", globalLength, globalPitch, 100, globalTempo, globalFlags);
						
					if (noteProperty == "content") notes[stoi(noteNum)]->setContent(value);					
					else if (noteProperty == "length") notes[stoi(noteNum)]->setLength(stoi(value));
					else if (noteProperty == "pitch") notes[stoi(noteNum)]->setPitch(value);
					else if (noteProperty == "tempo") notes[stoi(noteNum)]->setTempo(stod(value));
					else if (noteProperty == "vel") notes[stoi(noteNum)]->setVelocity(stoi(value));
					else if (noteProperty == "flags") notes[stoi(noteNum)]->setFlags(value);
					else cout << "Invalid property: " << noteProperty << endl;
				}
			}
		}
	}
	
	//TODO: calculate offset and whatnot, invoke tools

    return notes;
}

bool parser::islnvalid(string line) {
	if (!line.empty() && line.at(0) != '#' && line.find("=") != std::string::npos)
		return true;
	else return false;
}