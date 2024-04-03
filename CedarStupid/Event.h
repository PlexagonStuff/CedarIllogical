#pragma once
#include <string>
using namespace std;

//The Event Class signifies an event happening to a wire, naming the wire, what time the event occurs, the value the wire switches to, and the count for sorting
class Event {

public:
	Event();
	Event(int index, int t, int v, int c, string n);
	friend bool operator<(const Event& c1, const Event& c2);

private:
	int wireIndex;
	int time;
	int value;
	int count;
	string name;
	 
};