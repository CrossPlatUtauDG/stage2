#ifndef VOICEPROP_H
#define VOICEPROP_H

#include <string>
#include <vector>

class VoiceProp {
public:
	VoiceProp(std::string fileDir, std::string fileName, std::string sampleName, std::string alias, double start, double consonant, double end, double preutterance, double overlap);
	~VoiceProp();
	
	std::string getSamplePath();

	void setFileDir(std::string);
	void setFileName(std::string);
	void setSampleName(std::string);
	void setAlias(std::string);
	void setStart(double start);
	void setConsonant(double consonant);
	void setEnd(double end);
	void setPreutterance(double preutterance);
	void setOverlap(double overlap);

	std::string getFileDir();
	std::string getFileName();
	std::string getSampleName();
	std::string getAlias();
	double getStart();
	double getConsonant();
	double getEnd();
	double getPreutterance();
	double getOverlap();

private:
	std::string fileDir;
	std::string fileName;
	std::string sampleName;
	std::string alias;
	double start;
	double consonant;
	double end;
	double preutterance;
	double overlap;

	double adj_preutterance;
	double adj_overlap;
};
#endif