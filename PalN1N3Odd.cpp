// Accept numbers that are the sum of n and n-1 palindromes

#include <iostream>
#include <string> 
#include <vector>
#include <utility>

using namespace std;

struct State {
	int na;
	int nb;
	int lowerCarry;
	int higherCarry;
	State(int q = 0, int w = 0, int a = 0, int s = 0) {
		na = q;
		nb = w;
		lowerCarry = a;
		higherCarry = s;		
	}
};

class AutomatonGenerator {
private:
	int n1, n3;
	int maxCarry;
	void addBTransitions(State s);

public:
	AutomatonGenerator(int, int);
	void createStates();
	void createFinalStates();
	string getStateName(State s);
	void addTransitions();
};

AutomatonGenerator::AutomatonGenerator (int nMinusOne, int nMinusThree) {
	n1 = nMinusOne;
	n3 = nMinusThree;
	maxCarry = n1 + n3 - 1;
}

string AutomatonGenerator::getStateName(State s) {
	int x = s.na*8 + s.nb*4 + s.lowerCarry * 2 + s.higherCarry + 3;
	return " Q" + to_string(x)+" ";
}

void AutomatonGenerator::createFinalStates() {
	for(int na = 0; na <=n1; na++) {
		for(int higherCarry = 0; higherCarry <=maxCarry; higherCarry++) {	
			cout << getStateName(State(na,na,higherCarry, higherCarry)) <<endl;	
		}
	}
}

void AutomatonGenerator::createStates() {
	for(int na = 0; na <=n1; na++) {
		for(int nb = 0; nb <=n1; nb++) {
			for(int lowerCarry = 0; lowerCarry <=maxCarry; lowerCarry++) {
				for(int higherCarry = 0; higherCarry <=maxCarry; higherCarry++) {	
					cout << getStateName(State(na,nb,lowerCarry, higherCarry)) <<endl;	
				}
			}
		}
	}
}

void AutomatonGenerator::addBTransitions(State s) {
	string sname = getStateName(s);
	for (int incomingCarry = 0; incomingCarry <= maxCarry; incomingCarry++) {
		for (int n1guess = 0; n1guess <= n1; n1guess++) {
			for (int n3guess = 0; n3guess <= n3; n3guess++) {
				int higherBit = (incomingCarry + n1guess + n3guess) % 2;
				int higherCarry = (incomingCarry + n1guess + n3guess) / 2;
				int lowerBit = (s.lowerCarry + s.na + n3guess) % 2;
				int lowerCarry = (s.lowerCarry + s.na + n3guess) / 2;
				if (higherCarry != s.higherCarry)
					continue;
				string destName = getStateName(State(s.nb, n1guess, lowerCarry, incomingCarry));
				cout << "(" << sname << "b" << higherBit << lowerBit << destName <<")\n";
			}
		}
	}
}

void AutomatonGenerator::addTransitions() {
	cout << "( Q0 a1 Q1 )\n";
	cout << "( Q1 a0 Q2 )\n";
	string sname = getStateName(State(1,1,0,1));
	cout << "( Q2 a0" << sname << ")\n";

	for(int na = 0; na <=n1; na++) {
		for(int nb = 0; nb <=n1; nb++) {
			for(int lowerCarry = 0; lowerCarry <=maxCarry; lowerCarry++) {
				for(int higherCarry = 0; higherCarry <=maxCarry; higherCarry++) {	
					addBTransitions (State(na,nb,lowerCarry, higherCarry));
					cout << endl;
				}
			}
		}
	}
}

int main() {

	// This automaton doesn't work unless the numbers are 1,1
	AutomatonGenerator a(1,1);


	cout << "FiniteAutomaton testMachine = (\n";	
	cout << "alphabet = {a0 a1 b00 b01 b10 b11},\n";

	cout << "states = {\n";
	cout << " Q0 \n Q1 \n Q2 \n";
	a.createStates();
	cout<<"},\n";

	cout << "initialStates = {\n Q0 \n},\n";
	cout << "finalStates = {\n";
	a.createFinalStates();
	cout<<"},\n";

	cout << "transitions = {\n";
	a.addTransitions();
	cout <<"\n}\n);\n";

	cout << "FiniteAutomaton finalAut = shrinkNwa(testMachine);\n";
	cout << "print(relabel(determinize(finalAut)));\n\n\n\n\n\n\n\n\n\n";
}