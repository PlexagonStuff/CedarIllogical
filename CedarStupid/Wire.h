#pragma once
using namespace std;
#include <string>
#include <vector>

class Gate;

class Wire {
	public:
		Wire(string name = "N/A", char v = 'X', vector<Gate*> d = {}) {
			value = v;
			this->name = name;
			drives = d;
			setHistory(vector<char> {'X'});
		}
		void setValue(char v);
		void setDrive(Gate* gate);
		void setHistory(vector<char> newWireHistory);
		char getValue() const;
		vector<char> getHistory() const;
		string getName() const;
		vector<Gate*> getDrives() const;
		void printHistory() const;

	private:
		char value;
		string name;
		vector<Gate*> drives;
		vector<char> history;


};