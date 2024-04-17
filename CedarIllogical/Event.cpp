#include "Event.h"
#include "Gate.h"
#include "Wire.h"
#include <iostream>

Event::Event() {
	wireIndex = 0;
	time = 0;
	value = 0;
	count = 0;
	name = "";
}


Event::Event(int index, int t, char v, int c, string n) {
	wireIndex = index;
	time = t;
	value = v;
	count = c;
	name = n;
}

void Event::print() {
	cout << "[" << wireIndex << ", " << time << ", " << value << ", " << count << ", " << name << "]" << endl;
}

bool operator<(const Event& c1, const Event& c2)
{
	//Time is the primary key, Count is the secondary key
	if (c1.time == c2.time) {
		return c1.count > c2.count;
	}
	return  (c1.time > c2.time);
}