#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>

#include "Note.h"
#include "FileParser.h"
#include "RndSys.h"

#define DEBUG true

using namespace std;

int main(int argc, char* argv[]) {
	
	// Uncomment to accept filename as argument
	//if (argc < 2) {
	//	std::cerr << "Usage: " << argv[0] << "s2s_file" << std::endl;
	//	return 1;
	//}
	
	FileParser fParser;
	RndSys renderSystem;
	std::vector<Note*> noteList;

	try {
		// Uncomment following line to receive filename from argument
		//std::string s2sFilePath(argv[1]);
		// Remove following line to receive filename from argument
		std::string s2sFilePath = "example.s2s";
		noteList = fParser.parse(s2sFilePath);
	} catch (std::exception e) {
		std::cerr << "Exception Thrown: " << e.what() << std::endl;
		return 1;
	}

#if DEBUG
	for (Note* note : noteList) {
		std::cout << "Note " << note->getNoteId() << ":" << endl;
		std::cout << "\tContent:\t" << note->getContent() << std::endl;
		std::cout << "\tLength:\t\t" << note->getLength() << std::endl;
		std::cout << "\tPitch:\t\t" << note->getPitch() << std::endl;
		std::cout << "\tVelocity:\t" << note->getVelocity() << std::endl;
		std::cout << "\tFlags:\t\t" << note->getFlags() << std::endl;
		std::cout << "\tTempo:\t\t" << note->getTempo() << std::endl;
		std::cout << "\tRest:\t\t" << note->getRestLength() << std::endl;
		std::cout << "\tVB Path:\t" << note->getVbPath() << std::endl;
		std::cout << std::endl;
		//std::cout << TODO: complete
	}
#endif
	
	renderSystem.prepareRender(noteList);

	for (unsigned int i = 0; i < noteList.size(); i++) delete noteList[i];
		
    return 0;
}

