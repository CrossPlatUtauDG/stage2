#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <vector>

class Note {
public:
	Note(int noteId, std::string content, int length, std::string pitch, int velocity, double tempo, std::string flags, 
		int restlength, std::string vbpath, int modulation, std::string pitchcode, std::vector<int> envelope);
	~Note();

	int getLengthInMs();

	void setNoteId(int noteId);
	void setContent(std::string content);
	void setLength(int length);
	void setPitch(std::string pitch);
	void setVelocity(int velocity);
	void setTempo(double tempo);
	void setFlags(std::string flags);
	void setRestLength(int restlength);
	void setVbPath(std::string vbpath);
	void setModulation(int modulation);
	void setConsonant(double consonant);
	void setOverlap(double overlap);
	void setPreutterance(double preutterance);
	void setStp(double stp);
	void setPitchCode(std::string pitchcode);

	int getNoteId();
	std::string getContent();
	int getLength();
	std::string getPitch();
	int getVelocity();
	double getTempo();
	std::string getFlags();	
	int getRestLength();
	std::string getVbPath();
	int getModulation();
	double getConsonant();
	double getOverlap();
	double getPreutterance();
	double getStp();
	std::string getPitchCode();

private:
	int noteId;
	std::string content;
	int length;
	std::string pitch;
	int velocity;
	double tempo;
	std::string flags;	
	int restlength;
	std::string vbpath;
	int modulation;
	double consonant = -1;
	double overlap = -1;
	double preutterance = -1;
	double stp = 0;
	std::string pitchcode;
	std::vector<int> envelope;
};
#endif
