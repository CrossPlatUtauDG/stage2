#ifndef NOTE_H
#define NOTE_H

#include <string>

class Note {
public:
	Note(std::string content, int length, std::string pitch, int velocity, double tempo, std::string flags);
	~Note();

	void setContent(std::string content);
	void setLength(int length);
	void setPitch(std::string pitch);
	void setVelocity(int velocity);
	void setTempo(double tempo);
	void setFlags(std::string flags);

	std::string getContent();
	int getLength();
	std::string getPitch();
	int getVelocity();
	std::string getFlags();
	double getTempo();

private:
	std::string content;
	int length;
	std::string pitch;
	int velocity;
	std::string flags;
	double tempo;
};

#endif