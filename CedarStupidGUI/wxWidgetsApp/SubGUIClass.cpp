#include "SubGUIClass.h"

SubGUIClass::SubGUIClass( wxWindow* parent )
:
GUIClass( parent )
{

}

void SubGUIClass::CircuitFileAdded( wxFileDirPickerEvent& event )
{
// TODO: Implement CircuitFileAdded
	circuitFilePath = event.GetPath();
}

void SubGUIClass::VectorFileAdded( wxFileDirPickerEvent& event )
{
// TODO: Implement VectorFileAdded
	vectorFilePath = event.GetPath();
}

void SubGUIClass::StartSimulation( wxCommandEvent& event )
{
// TODO: Implement StartSimulation
	if (circuitFilePath != nullptr && vectorFilePath != nullptr) {
        wxTextCtrl* textWindow = findSimulationSpace();
        textWindow->SetValue("");
        vector<Wire*> wires(20);
        vector<Gate*> gates;
        priority_queue<Event> eventQueue;

        readFunctionFile(wires, gates);
        readVectorFile(wires, gates, eventQueue);
        simulate(wires, gates, eventQueue);
        printSimulation(wires);

	}
}


wxTextCtrl* SubGUIClass::findSimulationSpace() {
	wxWindowList windowChildren = this->GetChildren();

	wxWindowList::iterator iter;

	//return wxDynamicCast(*(windowChildren.end()), wxStatusBar);
	for (iter = windowChildren.begin(); iter != windowChildren.end(); ++iter) {
		wxTextCtrl* statusBar = wxDynamicCast(*iter, wxTextCtrl);
		if (statusBar) {
			return statusBar;
		}
	}


	return nullptr;
}


void SubGUIClass::printSimulation(vector<Wire*>& w) {
    wxTextCtrl* textWindow = findSimulationSpace();
    for (int i = 0; i < w.size(); i++) {
        wxString wireOutput;
        if (w.at(i) != nullptr) {
            wireOutput = w.at(i)->getName();
            for (int z = 0; z < w.at(i)->getHistory().size(); z++) {
                char value = w.at(i)->getHistory().at(z);
                if (value == '1') {
                    wireOutput.append('-');
                }
                else if (value == '0') {
                    wireOutput.append('_');
                }
                else {
                    wireOutput.append(value);
                }
            }
            wireOutput.append("\n");
        }
        textWindow->AppendText(wireOutput);
    }
}


void SubGUIClass::readFunctionFile(vector<Wire*>& w, vector<Gate*>& g) {
    string line;
    ifstream myfile(string(circuitFilePath.mb_str()));
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            stringstream ss(line);

            string word;
            vector<string> data;
            while (ss >> word) {
                //cout << word << endl;
                data.push_back(word);

            }
            if (data.size() > 0) {
                if (data.at(0) == "INPUT" || data.at(0) == "OUTPUT") {
                    Wire* newWire = new Wire(data.at(1));
                    int index = atoi(&data.at(2).c_str()[0]);
                    vector<Wire*>::iterator it;
                    it = w.begin();
                    w.at(index) = newWire;
                }
                //This has to be a gate
                else if (data.at(0) != "CIRCUIT") {
                    //cout << data.size() << endl;
                    int delay = atoi(&data.at(1).c_str()[0]);
                    //Check to see if wires mentioned are uninitialized
                    for (int i = 2; i < data.size(); i++) {
                        int index = atoi(&data.at(i).c_str()[0]);
                        if (w.at(index) == nullptr) {

                            Wire* newWire = new Wire(to_string(index));
                            w.at(index) = newWire;
                        }
                    }
                    if (data.at(0) == "NOT") {
                        Gate* newGate = new Gate(data.at(0), delay, w.at(atoi(&data.at(2).c_str()[0])), nullptr, w.at(atoi(&data.at(3).c_str()[0])));
                        g.push_back(newGate);
                    }
                    else {
                        Gate* newGate = new Gate(data.at(0), delay, w.at(atoi(&data.at(2).c_str()[0])), w.at(atoi(&data.at(3).c_str()[0])), w.at(atoi(&data.at(4).c_str()[0])));
                        g.push_back(newGate);
                    }

                }
            }
           // cout << "Ended the goofy goober" << endl;
        }
        myfile.close();
    }
}

void SubGUIClass::readVectorFile(vector<Wire*>& w, vector<Gate*>& g, priority_queue<Event>& eq) {
    string line;
    ifstream myfile(string(vectorFilePath.mb_str()));
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
               // cout << word << endl;
                data.push_back(word);
            }
            if (data.size() > 0) {
                if (data.at(0) != "VECTOR") {
                    int wireIndex;
                    for (int i = 0; i < w.size(); i++) {
                        if (w.at(i) != nullptr) {
                            if (w.at(i)->getName() == data.at(1)) {
                                wireIndex = i;
                            }
                        }
                    }
                    newEvent = Event(wireIndex, atoi(&data.at(2).c_str()[0]), data.at(3).c_str()[0], counter, data.at(1));
                    eq.push(newEvent);
                    counter++;
                }
            }

           // cout << "Another Goofy Goober" << endl;
        }
        myfile.close();
    }
}

void SubGUIClass::simulate(vector<Wire*>& w, vector<Gate*>& g, priority_queue<Event>& eq) {
    //https://cplusplus.com/reference/queue/priority_queue/pop/
    int eventCount = eq.size();
    while (!eq.empty())
    {
        Event taco = eq.top();
        int wireIndex = taco.getWireIndex();
        int eventTime = taco.getTime();
        char newWireValue = taco.getValue();
        if (eventTime > 60) {
            return;
        }
        //I like making these organized arrays to store things, yes I know this is inefficient, shut up.
        vector<int> gateIndex;
        vector<char> gateInitialOutput;
        vector<char>gateCurrentOutput;

        for (int i = 0; i < g.size(); i++) {
            Gate* gate = g.at(i);
            if (gate->getInput(1) == w.at(wireIndex) || gate->getInput(2) == w.at(wireIndex)) {
                //This gate has the wire as an input
                gateIndex.push_back(i);
                //The event must be evaluated at the gate delayed time
                gateInitialOutput.push_back(gate->evaluate(eventTime + gate->getDelay()));
            }
        }
        //Update the wire status
        w.at(wireIndex)->setValue(newWireValue);
        //Update the wire history
        vector<char> wireHistory = w.at(wireIndex)->getHistory();
        int i = wireHistory.size() - 1;
        //This is the value that will continue as long as there is no change with the wire
        char concurrentValue = wireHistory.at(wireHistory.size() - 1);
        while (i < eventTime) {
            wireHistory.push_back(concurrentValue);
            i++;
        }
        wireHistory.at(eventTime) = newWireValue;
        w.at(wireIndex)->setHistory(wireHistory);

        //Update all wires, moving their current values forward to the current time
        for (int i = 0; i < w.size(); i++) {
            if (i != wireIndex && w.at(i) != nullptr) {
                vector<char> wireHistory = w.at(i)->getHistory();
                int z = wireHistory.size() - 1;
                //This is the value that will continue as long as there is no change with the wire
                char concurrentValue = wireHistory.at(wireHistory.size() - 1);
                while (z < eventTime) {
                    wireHistory.push_back(concurrentValue);
                    z++;
                }
                w.at(i)->setHistory(wireHistory);
            }
        }

        //Check the changed gates again lol since we have updated a wire's status
        for (int i = 0; i < gateIndex.size(); i++) {
            Gate* gate = g.at(gateIndex.at(i));
            gateCurrentOutput.push_back(gate->evaluate(eventTime + gate->getDelay()));
        }
        //Create events if the goofy goober has changed
        for (int i = 0; i < gateIndex.size(); i++) {
            if (gateInitialOutput.at(i) != gateCurrentOutput.at(i)) {
                //Create an event
                Gate* gate = g.at(gateIndex.at(i));
                Wire* outputWire = gate->getOutput();
                int wireIndex;
                for (int i = 0; i < w.size(); i++) {
                    if (w.at(i) == outputWire) {
                        wireIndex = i;
                    }
                }
                Event newEvent;
                eventCount++;
                newEvent = Event(wireIndex, eventTime + gate->getDelay(), gateCurrentOutput.at(i), eventCount, outputWire->getName());
                eq.push(newEvent);
            }
        }


        //hello moto
        //Do stuff with each event
        taco.print();
        eq.pop();
    }
}