#ifndef RNDSYS_H
#define RNDSYS_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Note.h"
#include "Oto.h"
#include "VoiceProp.h"

class RndSys {
	public:
		RndSys() { }
		~RndSys();
		
		std::map<int, VoiceProp> getVoiceProps(std::vector<Note*> noteList);

		/**
			Overrides oto default VoiceProps and applies 食い込み補正 (Bite correction)
		*/
		void correctVoiceProps(std::vector<Note*> *noteList, std::map<int, VoiceProp> *voiceProps);

		std::string generateResamplerArg(std::string samplePath, std::string outputWav, std::string pitch,
			int velocity, std::string flags, double start, double lengthRequire, double consonant,
			double end, int volume, int modulation, double tempo, std::string pitchCode);

		std::string generateWavtoolArg(std::string outputWav, std::string tempWav, double stp, std::string length, std::string envelope);

		void generateArgs(std::vector<Note*> *notesList, std::map<int, VoiceProp> *voiceProps,
			std::vector<std::string> *resamplerArgs, std::vector<std::string> *wavtoolArgs); 
	
	private:
		std::map<std::string, Oto*> otos;
};

#endif
