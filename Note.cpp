#include <vector>
#include <string>

#include "Note.h"

Note::Note(std::string content, int length, std::string pitch, int velocity, double tempo, std::string flags,
	int restlength, std::string vbpath, int modulation, std::string pitchcode, vector<int> envelope) {
	this->content = content;
	this->length = length;
	this->pitch = pitch;
	this->velocity = velocity;
	this->tempo = tempo;
	this->flags = flags;
}

Note::~Note() { }

void Note::setContent(std::string lyric) { this->content = lyric; }
void Note::setLength(int length) { this->length = length; }
void Note::setPitch(std::string pitch) { this->pitch = pitch; }
void Note::setVelocity(int velocity) { this->velocity = velocity; }
void Note::setTempo(double tempo) { this->tempo = tempo; }
void Note::setFlags(std::string flags) { this->flags = flags; }
void Note::setRestLength(int restlength) { this->restlength = restlength; }
void Note::setVbPath(std::string vbpath) { this->vbpath = vbpath; }
void Note::setModulation(int modulation) { this->modulation = modulation; }
void Note::setPitchCode(string pitchcode) { this->pitchcode = pitchcode; }
void Note::setEnvelope(vector<int> envelope) { this->envelope = envelope; }

std::string Note::getContent() { return content; }
int Note::getLength() { return length; }
std::string Note::getPitch() { return pitch; }
int Note::getVelocity() { return velocity; }
double Note::getTempo() { return tempo; }
std::string Note::getFlags() { return flags; }
int Note::getRestLength() { return restlength; }
std::string Note::getVbPath() { return vbpath; }
int Note::getModulation() { return modulation; }
std::string Note::getPitchCode() { return pitchcode; }
vector<int> Note::getEnvelope() { return envelope; }