#pragma once
#include <string>
using namespace std;

//The Event Class signifies an event happening to a wire, naming the wire, what time the event occurs, the value the wire switches to, and the count for sorting
class Event {

public:
	Event();
	Event(int index, int t, char v, int c, string n);
	void print();
	friend bool operator<(const Event& c1, const Event& c2);
	int getWireIndex() const { return wireIndex; }
	int getTime() const { return time; }
	char getValue() const { return value; }
	int getCount() const { return count; }
	string getName() const {return name;}

private:
	int wireIndex;
	int time;
	int count;
	char value;

	string name;
	 
};