#ifndef OTO_H
#define OTO_H

#include <string>
#include <map>

#include "VoiceProp.h"

class Oto {
	public: 
		Oto(std::string path);
		~Oto();
		
		VoiceProp* getVPfromName(std::string sampleName);
	private:
		std::string filePath;
		std::string otoText;
		int lines;
		
		std::map<std::string, VoiceProp*> otoEntries;
		
		void openFile();
};
#endif