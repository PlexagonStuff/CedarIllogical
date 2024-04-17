#include "Wire.h"
#include "Gate.h"


void Wire::setValue(char v) {
	value - v;
}

void Wire::setDrive(Gate* gate) {
	drives.push_back(gate);
}

void Wire::setHistory(vector<char> newWireHistory) {
	history = newWireHistory;
}

char Wire::getValue() const {
	return value;
}

string Wire::getName() const {
	return name;
}

vector<char> Wire::getHistory() const {
	return history;
}

vector<Gate*> Wire::getDrives() const {
	return drives;
}

void Wire::printHistory() const {
	return;

}