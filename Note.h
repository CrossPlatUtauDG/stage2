#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <vector>

using namespace std;

class Note {
public:
	Note(int noteId, std::string content, int length, std::string pitch, int velocity, double tempo, std::string flags, 
		int restlength, std::string vbpath, int modulation, std::string pitchcode, std::vector<int> envelope);
	~Note();

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
	std::string pitchcode;
	std::vector<int> envelope;
};
#endif