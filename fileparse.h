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
		bool islnvalid(std::string line);
};