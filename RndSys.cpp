#include <string>
#include <vector>

#include "Note.h"
#include "RndSys.h"
#include "Oto.h"
#include "VoiceProp.h"

using namespace std;

void RndSys::prepRnd(vector<Note*> ntlist) {
	std::string globalvb = ntlist[0]->getVbPath();
	Oto *otoread = new Oto(globalvb);
	
	for (int i = 0; i < ntlist.size(); i++) {
		VoiceProp *vprop;
		
		if (ntlist[i]->getVbPath() != globalvb && ntlist[i]->getVbPath() != "") {
			globalvb = ntlist[i]->getVbPath();
			otoread = new Oto(globalvb);
		}
		
		// supposed to get the voiceprop from the note text/content (but it's broken)
		// otoread->getVPfromName(ntlist[i]->getContent(), *vprop);
	}

	delete otoread;
};