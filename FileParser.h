#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Note.h"

using namespace std;
 
class FileParser {
	public:
		FileParser();
		~FileParser();
		
		std::vector<Note*> parse(std::string filepath);
		
	private:
		std::vector<Note*> notes;
		std::string globalVB;
		double globalTempo = 120;
		std::string globalFlags = "";
		std::string globalPitch = "C4";
		int globalLength = 480;

		bool isLineValid(std::string line);
};