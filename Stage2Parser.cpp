#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Note.h"
#include "FileParser.h"

#define DEBUG true

using namespace std;

int main() {
	FileParser fParser;
	std::vector<Note*> noteList = fParser.parse("example.s2s");
#if DEBUG
	for (int i = 0; i < noteList.size(); i++) {
		std::cout << "Note " << i << ":" << endl;
		std::cout << "\tContent:\t" << noteList[i]->getContent() << std::endl;
		std::cout << "\tLength:\t\t" << noteList[i]->getLength() << std::endl;
		std::cout << "\tPitch:\t\t" << noteList[i]->getPitch() << std::endl;
		std::cout << "\tVelocity:\t" << noteList[i]->getVelocity() << std::endl;
		std::cout << "\tFlags:\t\t" << noteList[i]->getFlags() << std::endl;
		std::cout << "\tTempo:\t\t" << noteList[i]->getTempo() << std::endl;
		std::cout << "\tRest:\t\t" << noteList[i]->getRestLength() << std::end1;
		//std::cout << TODO: complete
	}
#endif
	for (int i = 0; i < noteList.size(); i++) delete noteList[i];
	
	
    return 0;
}

