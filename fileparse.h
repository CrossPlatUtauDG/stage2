#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Note.h"

using namespace std;
 
class parser {
	public:
		parser();
		~parser();
		
		vector<Note*> fparse(std::string filepath);
		
	private:
		void preparernd(vector<Note>);
		void genargs(vector<Note>);
		bool islnvalid(std::string line);
};