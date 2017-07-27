#include <string>
#include <vector>

#include "Note.h"
#include "RndSys.h"
#include "Oto.h"
#include "VoiceProp.h"

#define DEBUG true

using namespace std;

void RndSys::prepareRender(std::vector<Note*> noteList) {
	std::string globalvb = noteList[0]->getVbPath();
	Oto *otoread = new Oto(globalvb);
	
	for (unsigned int i = 0; i < noteList.size(); i++) {
		VoiceProp *voiceprop = nullptr;
		
		if (noteList[i]->getVbPath() != globalvb && noteList[i]->getVbPath() != "") {
			globalvb = noteList[i]->getVbPath();
			otoread = new Oto(globalvb);
		}
		
		// supposed to get the voiceprop from the note text/content (but it's broken)
		voiceprop = otoread->getVPfromName(noteList[i]->getContent());
#if DEBUG
		std::clog << "DEBUG: OTO data for note " << std::to_string(i) << std::endl;
		std::clog << "fileName = " << voiceprop->fileName << std::endl;
		std::clog << "sampleName = " << voiceprop->sampleName << std::endl;
		std::clog << "start = " << std::to_string(voiceprop->start) << std::endl;
		std::clog << "consonant = " << std::to_string(voiceprop->consonant) << std::endl;
		std::clog << "end = " << std::to_string(voiceprop->end) << std::endl;
		std::clog << "preutterance = " << std::to_string(voiceprop->preutterance) << std::endl;
		std::clog << "overlap = " << std::to_string(voiceprop->overlap) << std::endl;
		std::clog << std::endl;
#endif
	}
	//TODO: Implement destruction of voiceprops. Perhaps in otoread destructor
	delete otoread;
};