#ifndef OTO_H
#define OTO_H

#include <string>
#include <vector>

#include "VoiceProp.h"

class Oto {
	public: 
		Oto(std::string path);
		~Oto();
		
		void getVPfromName(std::string smpName, VoiceProp *vp);
	private:
		std::string filePath;
		std::string otoText;
		int lines;
		
		std::vector<VoiceProp*> voices;
		
		void openFile();
};
#endif