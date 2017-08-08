#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include <exception>

#include "Note.h"
#include "RndSys.h"
#include "Oto.h"
#include "VoiceProp.h"

#define DEBUG true

using namespace std;

RndSys::~RndSys() {
	for (auto& oto : otos) {
		delete oto.second;
	}
}

std::map<int, VoiceProp> RndSys::getVoiceProps(std::vector<Note*> noteList) {
	std::map<int, VoiceProp> voiceProps;
	for (Note* note : noteList) {
		try {
			if (otos[note->getVbPath()] == nullptr) otos[note->getVbPath()] = new Oto(note->getVbPath());
			VoiceProp voiceprop = otos[note->getVbPath()]->getVPfromName(note->getContent());
#if DEBUG
			std::clog << "DEBUG: OTO data for note " << note->getNoteId() << std::endl;
			std::clog << "fileName = " << voiceprop.getFileName() << std::endl;
			std::clog << "sampleName = " << voiceprop.getSampleName() << std::endl;
			std::clog << "alias = " << voiceprop.getAlias() << std::endl;
			std::clog << "start = " << std::to_string(voiceprop.getStart()) << std::endl;
			std::clog << "consonant = " << std::to_string(voiceprop.getConsonant()) << std::endl;
			std::clog << "end = " << std::to_string(voiceprop.getEnd()) << std::endl;
			std::clog << "preutterance = " << std::to_string(voiceprop.getPreutterance()) << std::endl;
			std::clog << "overlap = " << std::to_string(voiceprop.getOverlap()) << std::endl;
			std::clog << std::endl;
#endif
			voiceProps.insert(std::pair<int, VoiceProp>(note->getNoteId(), voiceprop));
		} catch (std::exception e) {
			std::clog << "Exception Thrown: " << e.what() << std::endl << std::endl;
		}
	}
	return voiceProps;
};

void RndSys::correctVoiceProps(std::vector<Note*> *noteList, std::map<int, VoiceProp> *voiceProps) {
	for (unsigned int i = 0; i < noteList->size(); i++) {
#if DEBUG
		std::clog << "DEBUG: Correcting note: " << noteList->at(i)->getNoteId() << std::endl;
#endif
		try {
			// Consonant/Preutterance/Overlap override
			if (noteList->at(i)->getConsonant() != -1) {
				voiceProps->at(noteList->at(i)->getNoteId()).setConsonant(noteList->at(i)->getConsonant());
#if DEBUG
				std::clog << "DEBUG: Consonant Override at note " << noteList->at(i)->getNoteId() << std::endl;
#endif
			}
			if (noteList->at(i)->getPreutterance() != -1) {
				voiceProps->at(noteList->at(i)->getNoteId()).setPreutterance(noteList->at(i)->getPreutterance());
#if DEBUG
				std::clog << "DEBUG: Preutterance Override at note " << noteList->at(i)->getNoteId() << std::endl;
#endif
			}
			if (noteList->at(i)->getOverlap() != -1) {
				voiceProps->at(noteList->at(i)->getNoteId()).setOverlap(noteList->at(i)->getOverlap());
#if DEBUG
				std::clog << "DEBUG: Overlap Override at note " << noteList->at(i)->getNoteId() << std::endl;
#endif
			}

			if (i == 0) continue; // First note does not need Kuikomi correction

			try {
				int currentNoteId = noteList->at(i)->getNoteId();
				if (voiceProps->at(currentNoteId).getPreutterance() - voiceProps->at(currentNoteId).getOverlap() > noteList->at(i-1)->getLengthInMs() / 2) {
					double oldPreutterance = voiceProps->at(currentNoteId).getPreutterance();
					double oldOverlap = voiceProps->at(currentNoteId).getOverlap();
					double correctionFactor = (noteList->at(i - 1)->getLengthInMs() / 2) / (oldPreutterance - oldOverlap);
					voiceProps->at(currentNoteId).setPreutterance(oldPreutterance * correctionFactor);
					voiceProps->at(currentNoteId).setOverlap(oldOverlap * correctionFactor);
					noteList->at(i)->setStp(oldPreutterance - voiceProps->at(currentNoteId).getPreutterance());
#if DEBUG
					std::clog << "DEBUG: Applied bite correction to note " << currentNoteId << std::endl;
					std::clog << "\tOld Preutterance: " << oldPreutterance << std::endl;
					std::clog << "\tNew Preutterance: " << voiceProps->at(currentNoteId).getPreutterance() << std::endl;
					std::clog << "\tOld Overlap: " << oldOverlap << std::endl;
					std::clog << "\tNew Overlap: " << voiceProps->at(currentNoteId).getOverlap() << std::endl;

#endif
				}
			} catch (std::out_of_range e) {
				// No match in oto for previous note. Treat as rest
				std::cerr << "No match in oto for current note, I guess" << std::endl;
			}


		} catch (std::out_of_range e) {
			std::cerr << e.what() << std::endl;
		}
	}
}

void RndSys::generateArgs(std::vector<Note*> *notesList, std::map<int, VoiceProp> *voiceProps, std::vector<std::string> *resamplerArgs, std::vector<std::string> *wavtoolArgs) {
	for (unsigned int i = 0; i < notesList->size(); i++) {
		try {
			int noteId = notesList->at(i)->getNoteId();
			std::string fileName = voiceProps->at(noteId).getFileName();
		}
		catch (std::out_of_range e) { // Treat as rest
			int noteId = notesList->at(i)->getNoteId();
			int nextNoteId = notesList->at(i+1)->getNoteId();
			double correctionValue;
			try {
				correctionValue = 0 - voiceProps->at(nextNoteId).getPreutterance() + voiceProps->at(nextNoteId).getOverlap();
			} catch (std::out_of_range e) { // Next note is rest as well, correction value is 0
				correctionValue = 0;
			}
			std::stringstream cvStream;
			cvStream << fixed << setprecision(1) << correctionValue;
			std::string correctionValueString = cvStream.str();

			std::stringstream tempoStream;
			tempoStream << fixed << setprecision(1) << notesList->at(i)->getTempo();
			if (correctionValue >= 0) correctionValueString = "+" + correctionValueString;
			std::string wavtoolArg = "temp.wav " + notesList->at(i)->getVbPath() + "/" + notesList->at(i)->getContent() + ".wav 0 " + std::to_string(notesList->at(i)->getLength()) + "@" + tempoStream.str() + correctionValueString + " 0 0";
			resamplerArgs->push_back("");
			wavtoolArgs->push_back(wavtoolArg);
		}
	}
}
