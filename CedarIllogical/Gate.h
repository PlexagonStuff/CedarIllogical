#pragma once

#include <string>
//#include "Wire.h"

using namespace std;



class Wire;

class Gate {

	public:
		Gate(string t, int d, Wire* i1, Wire* i2, Wire* o);
		int getDelay() const;
		Wire* getInput(int num) const;
		Wire* getOutput() const;
		char evaluate(int time) const;


	private:
		string type;
		int delay;
		Wire* input1;
		Wire* input2;
		Wire* output;
};