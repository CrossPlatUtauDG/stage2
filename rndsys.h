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
		
		void prepRnd(vector<Note*> ntlist);
		void genArgs(vector<Note*> notesIn, vector<std::string> resamplerArgs, 
			vector<std::string> wavtoolArgs); 
	
	private:
		vector<Note> ntlst;
		
		void correctOvlPre();
};

#endif
