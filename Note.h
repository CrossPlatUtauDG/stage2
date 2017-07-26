#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <vector>

using namespace std;

class Note {
public:
	Note(std::string content, int length, std::string pitch, int velocity, double tempo, std::string flags, 
		int restlength, std::string vbpath, int modulation, std::string pitchcode, vector<int> envelope);
	~Note();

	void setContent(std::string content);
	void setLength(int length);
	void setPitch(std::string pitch);
	void setVelocity(int velocity);
	void setTempo(double tempo);
	void setFlags(std::string flags);
	void setRestLength(int restlength);
	void setVbPath(std::string vbpath);
	void setModulation(int modulation);
	void setPitchCode(string pitchcode);
	void setEnvelope(vector<int> envelope);

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
	vector<int> getEnvelope();

private:
	std::string content;
	int length;
	std::string pitch;
	int velocity;
	double tempo;
	std::string flags;	
	int restlength;
	std::string vbpath;
	int modulation;
	string pitchcode;	
	vector<int> envelope;
	
};

#endif