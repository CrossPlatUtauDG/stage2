#include <string>
#include <vector>
#include <map>

#include "Note.h"
#include "RndSys.h"
#include "Oto.h"
#include "VoiceProp.h"

#define DEBUG true

using namespace std;

RndSys::~RndSys() {
	for (auto& oto : otos) {
		delete oto.second;
	}
}

void RndSys::prepareRender(std::vector<Note*> noteList) {
	for (Note* note : noteList) {
		try {
			if (otos[note->getVbPath()] == nullptr) otos[note->getVbPath()] = new Oto(note->getVbPath());
			VoiceProp voiceprop = otos[note->getVbPath()]->getVPfromName(note->getContent());
#if DEBUG
			std::clog << "DEBUG: OTO data for note " << note->getNoteId() << std::endl;
			std::clog << "fileName = " << voiceprop.fileName << std::endl;
			std::clog << "sampleName = " << voiceprop.sampleName << std::endl;
			std::clog << "start = " << std::to_string(voiceprop.start) << std::endl;
			std::clog << "consonant = " << std::to_string(voiceprop.consonant) << std::endl;
			std::clog << "end = " << std::to_string(voiceprop.end) << std::endl;
			std::clog << "preutterance = " << std::to_string(voiceprop.preutterance) << std::endl;
			std::clog << "overlap = " << std::to_string(voiceprop.overlap) << std::endl;
			std::clog << std::endl;
#endif
		} catch (std::exception e) {
			std::clog << "Exception Thrown: " << e.what() << std::endl << std::endl;
		}
	}
};
