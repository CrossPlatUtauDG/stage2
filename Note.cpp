#include "Note.h"

Note::Note(std::string content, int length, std::string pitch, int velocity, double tempo, std::string flags) {
	this->content = content;
	this->length = length;
	this->pitch = pitch;
	this->velocity = velocity;
	this->tempo = tempo;
	this->flags = flags;
}

Note::~Note() {
}

void Note::setContent(std::string lyric) {
	this->content = lyric;
}

void Note::setLength(int length) {
	this->length = length;
}

void Note::setPitch(std::string pitch) {
	this->pitch = pitch;
}

void Note::setVelocity(int velocity) {
	this->velocity = velocity;
}

void Note::setTempo(double tempo) {
	this->tempo = tempo;
}

void Note::setFlags(std::string flags) {
	this->flags = flags;
}

std::string Note::getContent() {
	return content;
}

int Note::getLength() {
	return length;
}

std::string Note::getPitch() {
	return pitch;
}

int Note::getVelocity() {
	return velocity;
}

std::string Note::getFlags() {
	return flags;
}

double Note::getTempo() {
	return tempo;
}