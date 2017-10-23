// Accept even-length numbers that are the sum of n and n-3 palindromes

#include <iostream>
#include <string> 
#include <vector>
#include <utility>

using namespace std;

struct State {
	int na;
	int nb;
	int nc;
	int lowerCarry;
	int higherCarry;
	State(int q = 0, int w = 0, int e = 0, int a = 0, int s = 0) {
		na = q;
		nb = w;
		nc = e;
		lowerCarry = a;
		higherCarry = s;		
	}
};

class AutomatonGenerator {
private:
	int n, n3;
	int maxCarry;
	void addInitTransitions();
	void addATransitions(State s);
	void addBTransitions(State s);

public:
	AutomatonGenerator(int, int);
	void createStates();
	string getStateName(State s);
	void addTransitions();
};

AutomatonGenerator::AutomatonGenerator (int n0, int nMinusThree) {
	n = n0;
	n3 = nMinusThree;
	maxCarry = n + n3 - 1;
}

string AutomatonGenerator::getStateName(State s) {
	// string ret = " Q" + to_string(s.na) + to_string(s.nb);
	// ret += to_string(s.nc) + to_string(s.nd);	

	// return ret+"_"+to_string(s.lowerCarry)+"_"+to_string(s.higherCarry)+" ";

	int i = 0;
	i += s.higherCarry;
	i += 2*s.lowerCarry;
	i += 4*s.nc;
	i += 8*s.nb;
	i += 16*s.na;

	return " q" + to_string(i) + " ";
}

void AutomatonGenerator::createStates() {
	for(int na = 0; na <=n; na++) {
		for(int nb = 0; nb <=n; nb++) {
			for(int nc = 0; nc <=n; nc++) {
				for(int lowerCarry = 0; lowerCarry <=maxCarry; lowerCarry++) {
					for(int higherCarry = 0; higherCarry <=maxCarry; higherCarry++) {	
						cout << getStateName(State(na,nb,
							nc,lowerCarry, higherCarry)) <<endl;	
					}
				}
			}
		}
	}
}

void AutomatonGenerator::addBTransitions(State s) {
	if ((s.na + s.nb + s.nc + s.lowerCarry) != 0)
		return;
	string sname = getStateName(s);
	for (int incomingCarry = 0; incomingCarry <= maxCarry; incomingCarry++) {
		for (int nguess = 0; nguess <= n; nguess++) {
			int higherBit = (incomingCarry + nguess) % 2;
			int higherCarry = (incomingCarry + nguess) / 2;
			if (higherCarry != s.higherCarry)
				continue;
			string destName = getStateName(State(0, 0, s.na, nguess, 0, incomingCarry));
			cout << "(" << sname << "b" << higherBit << destName <<")\n";
		}
	}
}

// void AutomatonGenerator::addATransitions() {
// 	string sname = getStateName(State());
// 	for (int incomingCarry = 0; incomingCarry <= maxCarry; incomingCarry++) {
// 		int higherBit = (incomingCarry + n) % 2;
// 		int higherCarry = (incomingCarry + n) / 2;
// 		if ((higherBit != 1) || (higherCarry != 0))
// 			continue;
// 		string destName = getStateName(State(0, 0, 0, n, 0, incomingCarry));
// 		cout << "(" << sname << "a1" << destName <<")\n";
// 	}
// }

// s0: must produce 0, guessed bit 0
// s1: must produce 0, guessed bit 1
// s2: must produce 1, guessed bit 0

void AutomatonGenerator::addInitTransitions() {
	cout<<"( r0 a1 r1 )\n";
	cout<<"( r1 a0 s0 )\n";
	cout<<"( r1 a1 s1 )\n";
	cout<<"( r1 a1 s2 )\n";
	cout<<"( s0 a0 " << getStateName(State(1,0,0,0,0))<<")\n";
	cout<<"( s0 a1 " << getStateName(State(1,0,1,0,0))<<")\n";
	cout<<"( s0 a1 " << getStateName(State(1,0,0,0,1))<<")\n";
	cout<<"( s1 a0 " << getStateName(State(1,1,0,0,0))<<")\n";
	cout<<"( s1 a1 " << getStateName(State(1,1,1,0,0))<<")\n";
	cout<<"( s1 a1 " << getStateName(State(1,1,0,0,1))<<")\n";
	cout<<"( s2 a0 " << getStateName(State(1,0,1,0,0))<<")\n";
	cout<<"( s2 a1 " << getStateName(State(1,0,1,0,0))<<")\n";
	cout<<"( s2 a1 " << getStateName(State(1,0,0,0,1))<<")\n";
}
void AutomatonGenerator::addTransitions() {
	addInitTransitions();
	for(int na = 0; na <=n; na++) {
		for(int nb = 0; nb <=n; nb++) {
			for(int nc = 0; nc <=n; nc++) {
				for(int lowerCarry = 0; lowerCarry <=maxCarry; lowerCarry++) {
					for(int higherCarry = 0; higherCarry <=maxCarry; higherCarry++) {	
						addBTransitions (State(na,nb,
							nc,lowerCarry, higherCarry));
							cout << endl;
						addATransitions (State(na,nb,
							nc,lowerCarry, higherCarry));
							cout << endl;
					}
				}
			}
		}
	}
}

int main() {

	AutomatonGenerator a(1,1);


	cout << "FiniteAutomaton testMachine = (\n";	
	cout << "alphabet = {a0 a1 b00 b01 b10 b11},\n";

	cout << "states = { r0\nr1\n";
	a.createStates();
	cout<<"\nacc},\n";

	cout << "initialStates = { r0\n";
	cout << "},\nfinalStates = {";
	cout<<"\nacc},\n";

	cout << "transitions = {\n";
	a.addTransitions();
	cout <<"\n}\n);\n";

	cout << "FiniteAutomaton finalAut = shrinkNwa(testMachine);\n";
	cout << "print(numberOfStates(determinize(finalAut)));\n\n\n\n\n\n\n\n\n\n";
}