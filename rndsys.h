#include <string>
#include <vector>

#include "Note.h"

using namespace std;

class rndsys {
	public:
		rndsys(vector<Note> ntlist) { ntlst = ntlist; }
		~rndsys();
		
		void preparernd(vector<Note>);
		void genargs(vector<Note>);
	
	private:
		vector<Note> ntlst;
};