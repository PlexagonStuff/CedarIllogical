#include <iostream>
#include <string>
#include <vector>
#include "Wire.h"
#include "Gate.h"
#include "Event.h"
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

void readFunctionFile(vector<Wire*>& w, vector<Gate*>& g);
void readVectorFile(vector<Wire*>& w, vector<Gate*>& g, priority_queue<Event> eq);
void simulate(vector<Wire*>& w, vector<Gate*>& g, priority_queue<Event> eq);

int main() {
	vector<Wire*> wires(10);
	vector<Gate*> gates;
    priority_queue<Event> eventQueue;

    readFunctionFile(wires, gates);
    readVectorFile(wires, gates, eventQueue);
    simulate(wires, gates, eventQueue);

	return 0;
}


void readFunctionFile(vector<Wire*> &w, vector<Gate*> &g) {
    string line;
    ifstream myfile("C:/Users/plexa/Downloads/Term Project Files CS1220/Term Project Files/Additional Circuit Description Files/circuit0.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            stringstream ss(line);

            string word;
            vector<string> data;
            while (ss >> word) {
                cout << word <<endl;
                data.push_back(word);
                
            }
            if (data.at(0) == "INPUT" || data.at(0) == "OUTPUT") {
                Wire* newWire = new Wire(data.at(1));
                int index = atoi(&data.at(2).c_str()[0]);
                vector<Wire *>::iterator it;
                it = w.begin();
                w.insert(it + (index), newWire);
            }
            //This has to be a gate
            else if (data.at(0) != "CIRCUIT") {
                cout << data.size() << endl;
                int delay = atoi(&data.at(1).c_str()[0]);
                if (data.at(0) == "NOT") {
                    Gate* newGate = new Gate(data.at(0), delay, w.at(atoi(&data.at(2).c_str()[0])), nullptr, w.at(atoi(&data.at(3).c_str()[0])));
                    g.push_back(newGate);
                }
                else {
                    Gate* newGate = new Gate(data.at(0), delay, w.at(atoi(&data.at(2).c_str()[0])), w.at(atoi(&data.at(3).c_str()[0])), w.at(atoi(&data.at(4).c_str()[0])));
                    g.push_back(newGate);
                }
                
            }
            cout << "Ended the goofy goober" << endl;
        }
        myfile.close();
    }
}

void readVectorFile(vector<Wire*>& w, vector<Gate*>& g, priority_queue<Event> eq) {
    string line;
    ifstream myfile("C:/Users/plexa/Downloads/Term Project Files CS1220/Term Project Files/Additional Circuit Description Files/circuit0_v.txt");
    if (myfile.is_open())
    {
        Event newEvent;
        int counter = 0;
        while (getline(myfile, line))
        {
            stringstream ss(line);

            string word;
            vector<string> data;
            while (ss >> word) {
                cout << word << endl;
                data.push_back(word);
            }
            if (data.at(0) != "VECTOR") {
                int wireIndex;
                for (int i = 0; i < w.size(); i++) {
                    if (w.at(i) != nullptr) {
                        if (w.at(i)->getName() == data.at(1)) {
                            wireIndex = i;
                        }
                    }
                }
                newEvent = Event(wireIndex, atoi(&data.at(2).c_str()[0]), atoi(&data.at(3).c_str()[0]), counter, data.at(1));
                eq.push(newEvent);
                counter++;
            }
            
            cout << "Another Goofy Goober" << endl;
        }
        myfile.close();
    }
}

void  simulate(vector<Wire*>& w, vector<Gate*>& g, priority_queue<Event> eq) {
    //https://cplusplus.com/reference/queue/priority_queue/pop/
    while (!eq.empty())
    {
        Event taco = eq.top();
        //Do stuff with each event
        eq.pop();
    }
}