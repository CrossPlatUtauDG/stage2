#ifndef VOICEPROP_H
#define VOICEPROP_H

#include <string>
#include <vector>

class VoiceProp {
	public:
		VoiceProp() {} 
		~VoiceProp() {}
	
		std::string sampleName;
		std::string fileName;
		std::string fileDir;
		
		double start;
		double consonant;
		double end;
		double preutterance;
		double overlap;
		double adj_preutterance;
		double adj_overlap;
		
		std::string getSamplePath() { return fileDir + fileName; }
};
#endif