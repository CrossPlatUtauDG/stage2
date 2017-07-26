#ifndef RNDSYS_H
#define RNDSYS_H

#include <string>
#include <vector>

#include "Note.h"

using namespace std;

class RndSys {
	public:
		RndSys(vector<Note> ntlist) { ntlst = ntlist; }
		~RndSys();
		
		void prepRnd(vector<Note>);
		void genArgs(vector<Note>);
	
	private:
		vector<Note> ntlst;
};

#endif
