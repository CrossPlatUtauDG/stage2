#include <string>
#include <vector>

#include "VoiceProp.h"

VoiceProp::VoiceProp(std::string fileDir, std::string fileName, std::string sampleName, std::string alias, double start, double consonant, double end, double preutterance, double overlap)
	: fileDir (fileDir), fileName (fileName), sampleName (sampleName), alias (alias), start (start), consonant (consonant), end (end), preutterance (preutterance), overlap (overlap) {}

VoiceProp::~VoiceProp() {}

std::string VoiceProp::getSamplePath() {
	return fileDir + fileName;
}

void VoiceProp::setFileDir(std::string) { this->fileDir = fileDir; }
void VoiceProp::setFileName(std::string) { this->fileName = fileName; }
void VoiceProp::setSampleName(std::string) { this->sampleName = sampleName; }
void VoiceProp::setAlias(std::string) { this->alias = alias; }
void VoiceProp::setStart(double start) { this->start = start; }
void VoiceProp::setConsonant(double consonant) { this->consonant = consonant; }
void VoiceProp::setEnd(double end) { this->end = end; }
void VoiceProp::setPreutterance(double preutterance) { this->preutterance = preutterance; }
void VoiceProp::setOverlap(double overlap) { this->overlap = overlap; }

std::string VoiceProp::getFileDir() { return fileDir; }
std::string VoiceProp::getFileName() { return fileName; }
std::string VoiceProp::getSampleName() { return sampleName; }
std::string VoiceProp::getAlias() { return alias; }
double VoiceProp::getStart() { return start; }
double VoiceProp::getConsonant() { return consonant; }
double VoiceProp::getEnd() { return end; }
double VoiceProp::getPreutterance() { return preutterance; }
double VoiceProp::getOverlap() { return overlap; }

