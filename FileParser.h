#ifndef FILEPARSER_H
#define FILEPARSER_H

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
		std::string globalContent = "a";
		std::string globalFlags = "";
		std::string globalPitch = "C4";
		std::string globalPitchCode = "";
		int globalLength = 480;
		int globalVelocity = 100;
		int globalRest = 0;
		int globalModulation = 0;
		double globalTempo = 120;
		vector<int> globalEnv = {0, 0, 100, 5, 100, 35, 0, 0};

		bool isLineValid(std::string line);
		void fillInvalidNotes(vector<Note*>* notelist);
		vector<int> envFromStr(std::string envstr);
};

#endif
