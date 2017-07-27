#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Note.h"
#include "FileParser.h"
#include "RndSys.h"

#define DEBUG true

using namespace std;

int main() {
	FileParser fParser;
	RndSys rendersys;
	std::vector<Note*> noteList = fParser.parse("example.s2s");
	
	for (unsigned int i = 0; i < noteList.size(); i++) {
		if (noteList[i] == nullptr) 
			std::cout << "Note " << std::to_string(i) << " is invalid";
#if DEBUG			
		std::cout << "Note " << i << ":" << endl;
		std::cout << "\tContent:\t" << noteList[i]->getContent() << std::endl;
		std::cout << "\tLength:\t\t" << noteList[i]->getLength() << std::endl;
		std::cout << "\tPitch:\t\t" << noteList[i]->getPitch() << std::endl;
		std::cout << "\tVelocity:\t" << noteList[i]->getVelocity() << std::endl;
		std::cout << "\tFlags:\t\t" << noteList[i]->getFlags() << std::endl;
		std::cout << "\tTempo:\t\t" << noteList[i]->getTempo() << std::endl;
		std::cout << "\tRest:\t\t" << noteList[i]->getRestLength() << std::endl;
		std::cout << "\tVB Path:\t" << noteList[i]->getVbPath() << std::endl;
		std::cout << std::endl;
		//std::cout << TODO: complete
#endif
	}
	
	rendersys.prepRnd(noteList);

	for (int i = 0; i < noteList.size(); i++) delete noteList[i];
		
    return 0;
}

