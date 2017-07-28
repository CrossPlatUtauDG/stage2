#ifndef RNDSYS_H
#define RNDSYS_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Note.h"
#include "Oto.h"

using namespace std;

class RndSys {
	public:
		RndSys() { }
		~RndSys();
		
		void prepareRender(std::vector<Note*> noteList);
		void generateArgs(vector<Note*> notesIn, vector<std::string> resamplerArgs, 
			vector<std::string> wavtoolArgs); 
	
	private:
		std::map<std::string, Oto*> otos;

		void correctOvlPre();
};

#endif
