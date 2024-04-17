#include "Gate.h"
#include "Wire.h"

Gate::Gate(string t, int d, Wire* i1, Wire* i2, Wire* o) {
	type = t;
	delay = d;
	input1 = i1;
	input2 = i2;
	output = o;
}

int Gate::getDelay() const {
	return delay;
}

Wire* Gate::getInput(int num) const {
	if (num == 1) {
		return input1;
	}
	else {
		return input2;
	}
}

Wire* Gate::getOutput() const {
	return output;
}

char Gate::evaluate(int time) const {
	int evalTime = time - delay;
	if (evalTime > input1->getHistory().size()-1) {
		evalTime = input1->getHistory().size() - 1;
	}
	if (type == "NOT") {
		if (input1->getHistory().at(evalTime) == 'X') {
			return 'X';
		}
		else {
			if (input1->getHistory().at(evalTime) == '1') {
				return '0';
			}
			else {
				return '1';
			}
		}
	}
	if (type == "AND") {
		if (input1->getHistory().at(evalTime) == '1' && input2->getHistory().at(evalTime) == '1') {
			return '1';
		}
		else if (input1->getHistory().at(evalTime) == '0' || input2->getHistory().at(evalTime) == '0') {
			return '0';
		}
		else {
			return 'X';
		}
	}
	if (type == "OR") {
		if (input1->getHistory().at(evalTime) == '1' || input2->getHistory().at(evalTime) == '1') {
			return '1';
		}
		else if (input1->getHistory().at(evalTime) == '0' && input2->getHistory().at(evalTime) == '0') {
			return '0';
		}
		else {
			return 'X';
		}
	}
	if (type == "XOR") {
		if ((input1->getHistory().at(evalTime) == '0' && input2->getHistory().at(evalTime) == '0') || (input1->getHistory().at(evalTime) == '1' && input2->getHistory().at(evalTime) == '1')) {
			return '0';
		}
		else if (input1->getHistory().at(evalTime) == 'X' || input2->getHistory().at(evalTime) == 'X') {
			return 'X';
		}
		else {
			return '1';
		}
	}
	if (type == "NAND") {
		if (input1->getHistory().at(evalTime) == '1' && input2->getHistory().at(evalTime) == '1') {
			return '0';
		}
		else if (input1->getHistory().at(evalTime) == '0' || input2->getHistory().at(evalTime) == '0') {
			return '1';
		}
		else {
			return 'X';
		}
	}
	if (type == "NOR") {
		if (input1->getHistory().at(evalTime) == '1' || input2->getHistory().at(evalTime) == '1') {
			return '0';
		}
		else if (input1->getHistory().at(evalTime) == '0' && input2->getHistory().at(evalTime) == '0') {
			return '1';
		}
		else {
			return 'X';
		}
	}
	if (type == "XNOR") {
		if ((input1->getHistory().at(evalTime) == '0' && input2->getHistory().at(evalTime) == '0') || (input1->getHistory().at(evalTime) == '1' && input2->getHistory().at(evalTime) == '1')) {
			return '1';
		}
		else if (input1->getHistory().at(evalTime) == 'X' || input2->getHistory().at(evalTime) == 'X') {
			return 'X';
		}
		else {
			return '0';
		}
	}


}


