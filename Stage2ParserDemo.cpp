#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Note.h"
#include "fileparse.h"

using namespace std;

int main() {
	parser fparser;
	vector<Note*> notelst = fparser.fparse("example.s2s");

	for (int i = 0; i < notelst.size(); i++) {
		cout << "Note " << i << ":" << endl;
		cout << "\tContent:\t" << notelst[i]->getContent() << endl;
		cout << "\tLength:\t\t" << notelst[i]->getLength() << endl;
		cout << "\tPitch:\t\t" << notelst[i]->getPitch() << endl;
		cout << "\tVelocity:\t" << notelst[i]->getVelocity() << endl;
		cout << "\tFlags:\t\t" << notelst[i]->getFlags() << endl;
		cout << "\tTempo:\t\t" << notelst[i]->getTempo() << endl;
	}

    return 0;
}

