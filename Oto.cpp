#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <stdlib.h>

#include "Note.h"
#include "VoiceProp.h"
#include "Oto.h"

#define DEBUG true
#define DEBUG_FULL false // enables debug output on every oto line, may result in a LOT of output

using namespace std;

Oto::Oto(std::string path) {
	filePath = path;
	openFile();
}

Oto::~Oto() {
	for (auto& voiceprop : otoEntries) {
		delete voiceprop.second;
	}
#if DEBUG
	std::clog << "Oto object destructed: " << filePath << std::endl;
#endif
}

void Oto::openFile() {
	std::ifstream otoStream;
	otoStream.open(filePath + "/oto.ini");
	
	if (!otoStream) {
		throw std::runtime_error("Could not read " + filePath + "/oto.ini");
	}
	
	if (otoStream.is_open()) {
		std::string otoItem;
		unsigned int index = 0;
		
		
		// This was mostly ported from FVSS, there probably will be errors
		// Also needs error handling 
		while (getline(otoStream, otoItem)) {
			VoiceProp *vp = new VoiceProp();
			
			// needed because of newline fix
			std::string item = otoItem;
#if DEBUG_FULL
			clog << "DEBUG_FULL: oto line " << std::to_string(index) << ":" << std::endl;
			clog << "	" << item << std::endl;
#endif
			try {
				//TODO: maybe remove newlines that get left behind
				
				// Get indexes from line
				int index1 = item.find('=');
                int index2 = item.find(",", index1 + 1);
                int index3 = item.find(",", index2 + 1);
                int index4 = item.find(",", index3 + 1);
                int index5 = item.find(",", index4 + 1);
                int index6 = item.find(",", index5 + 1);
#if DEBUG_FULL 
				clog << "DEBUG_FULL: Printing all OTO content indexes" << std::endl;
				clog << "	" << std::to_string(index1) << std::endl;
				clog << "	" << std::to_string(index2) << std::endl;
				clog << "	" << std::to_string(index3) << std::endl;
				clog << "	" << std::to_string(index4) << std::endl;
				clog << "	" << std::to_string(index5) << std::endl;
#endif
				// Chop up line into individual properties and add them to vp
				vp->fileName = item.substr(0, index1);
				vp->sampleName = item.substr(index1 + 1, index2 - index1 - 1);
#if DEBUG_FULL
				clog << "DEBUG_FULL: OTO fileName: " << vp->fileName << std::endl;
				clog << "DEBUG_FULL: OTO sampleName: " << vp->sampleName << std::endl;
#endif
				vp->start = std::stod(item.substr(index2 + 1, index3 - index2 - 1));
                vp->consonant = std::stod(item.substr(index3 + 1, index4 - index3 - 1));
                vp->end = std::stod(item.substr(index4 + 1, index5 - index4 - 1));
                vp->preutterance = std::stod(item.substr(index5 + 1, index6 - index5 - 1));
                vp->overlap = std::stod(item.substr(index6 + 1));
#if DEBUG_FULL
				clog << "DEBUG_FULL: Printing all parsed OTO properties:" << std::endl;
				clog << "	" << std::to_string(vp->start) << std::endl;
				clog << "	" << std::to_string(vp->consonant) << std::endl;
				clog << "	" << std::to_string(vp->end) << std::endl;
				clog << "	" << std::to_string(vp->preutterance) << std::endl;
				clog << "	" << std::to_string(vp->overlap) << std::endl;
#endif				
				//TODO: might need to remove newlines from FileName property
				
				otoEntries[vp->sampleName] = vp;
				otoEntries[vp->fileName.substr(0, vp->fileName.length()-4)] = vp;
#if DEBUG_FULL				
				//print the first 2 oto property lists
				if (index < 2) {
					clog << "DEBUG: OTO data from entry " << std::to_string(index) << std::endl;
					clog << "fileName = " << otoEntries[vp->sampleName]->fileName << std::endl;
					clog << "sampleName = " << otoEntries[vp->sampleName]->sampleName << std::endl;
					clog << "start = " << std::to_string(otoEntries[vp->sampleName]->start) << std::endl;
					clog << "consonant = " << std::to_string(otoEntries[vp->sampleName]->consonant) << std::endl;
					clog << "end = " << std::to_string(otoEntries[vp->sampleName]->end) << std::endl;
					clog << "preutterance = " << std::to_string(otoEntries[vp->sampleName]->preutterance) << std::endl;
					clog << "overlap = " << std::to_string(otoEntries[vp->sampleName]->overlap) << std::endl;
					std::clog << std::endl;
				}
#endif
			}			
			catch (...) { }
			
			index++;
		}
	}
}

VoiceProp Oto::getVPfromName(std::string sampleName) {
	if (otoEntries.find(sampleName) != otoEntries.end()) {
		return *otoEntries[sampleName];
	} else {
		throw std::runtime_error(std::string("No match for note with content ") + sampleName + std::string(" in voicebank oto"));
	}
}
