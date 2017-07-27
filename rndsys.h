#ifndef RNDSYS_H
#define RNDSYS_H

#include <string>
#include <vector>
#include <iostream>

#include "Note.h"

using namespace std;

class RndSys {
	public:
		RndSys() { }
		~RndSys() { }
		
		void prepareRender(std::vector<Note*> noteList);
		void genArgs(vector<Note*> notesIn, vector<std::string> resamplerArgs, 
			vector<std::string> wavtoolArgs); 
	
	private:
		std::vector<Note> noteList;
		
		void correctOvlPre();
};

#endif
