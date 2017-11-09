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
	void addCTransitions(State s);

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

void AutomatonGenerator::addATransitions(State s) {
	if (s.nb != s.nc)
		return;
	string sname = getStateName(s);
	for (int n3guess = 0; n3guess <= n3; n3guess++) {
		int bit = (s.lowerCarry + s.na + n3guess) % 2;
		int carry = (s.lowerCarry + s.na + n3guess) / 2;
		if (carry != s.higherCarry)
			continue;
		cout << "(" << sname << "a" << bit <<" acc )\n";
	}
}


void AutomatonGenerator::addCTransitions(State s) {
	string sname = getStateName(s);
	for (int incomingCarry = 0; incomingCarry <= maxCarry; incomingCarry++) {
		for (int nguess = 0; nguess <= n; nguess++) {
			for (int n3guess = 0; n3guess <= n3; n3guess++) {
				int higherBit = (incomingCarry + nguess + n3guess) % 2;
				int higherCarry = (incomingCarry + nguess + n3guess) / 2;
				if (higherCarry != s.higherCarry)
					continue;
				int lowerBit = (s.lowerCarry + s.na + n3guess) % 2;
				int lowerCarry = (s.lowerCarry + s.na + n3guess) / 2;			
				string destName = getStateName(State(s.nb, s.nc, nguess, lowerCarry, incomingCarry));
				cout << "(" << sname << "c" << higherBit << lowerBit << destName <<")\n";
			}
		}
	}
}

void AutomatonGenerator::addBTransitions(State s) {
	string sname = getStateName(s);
	for (int incomingCarry = 0; incomingCarry <= maxCarry; incomingCarry++) {
		for (int nguess = 0; nguess <= n; nguess++) {
			int higherBit = (incomingCarry + nguess + n3) % 2;
			int higherCarry = (incomingCarry + nguess + n3) / 2;
			if (higherCarry != s.higherCarry)
				continue;
			int lowerBit = (n + n3) % 2;
			int lowerCarry = (n + n3) / 2;			
			string destName = getStateName(State(s.nb, s.nc, nguess, lowerCarry, incomingCarry));
			cout << "(" << sname << "b" << higherBit << lowerBit << destName <<")\n";
		}
	}
}

// s0: must produce 0, guessed bit 0
// s1: must produce 0, guessed bit 1
// s2: must produce 1, guessed bit 0

void AutomatonGenerator::addInitTransitions() {
	cout<<"( r0 a1 r1 )\n";
	cout<<"( r1 a0 s0 )\n";
	cout<<"( r1 a1 s1 )\n";
	cout<<"( r1 a1 s2 )\n";
	cout<<"( s0 a0 " << getStateName(State(1,0,0,0,0))<<" )\n";
	cout<<"( s0 a1 " << getStateName(State(1,0,1,0,0))<<" )\n";
	cout<<"( s0 a1 " << getStateName(State(1,0,0,0,1))<<" )\n";
	cout<<"( s1 a0 " << getStateName(State(1,1,0,0,0))<<" )\n";
	cout<<"( s1 a1 " << getStateName(State(1,1,1,0,0))<<" )\n";
	cout<<"( s1 a1 " << getStateName(State(1,1,0,0,1))<<" )\n";
	cout<<"( s2 a0 " << getStateName(State(1,0,1,0,1))<<" )\n";
}
void AutomatonGenerator::addTransitions() {
	addInitTransitions();
	for(int nb = 0; nb <=n; nb++) {
		for(int nc = 0; nc <=n; nc++) {
			for(int higherCarry = 0; higherCarry <=maxCarry; higherCarry++) {
				if (nb + nc + higherCarry == 3)
					continue;
				addBTransitions (State(1,nb,
					nc,0, higherCarry));
					cout << endl;
			}
		}
	}
	for(int na = 0; na <=n; na++) {
		for(int nb = 0; nb <=n; nb++) {
			for(int nc = 0; nc <=n; nc++) {
				for(int lowerCarry = 0; lowerCarry <=maxCarry; lowerCarry++) {
					for(int higherCarry = 0; higherCarry <=maxCarry; higherCarry++) {	
						addCTransitions (State(na,nb,
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
	cout << "alphabet = {a0 a1 b00 b10 c00 c01 c10 c11},\n";

	cout << "states = { r0\nr1\ns0\ns1\ns2\n";
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