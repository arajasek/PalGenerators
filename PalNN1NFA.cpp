// Accept numbers that are the sum of n and n-1 palindromes

#include <iostream>
#include <string> 
#include <vector>
#include <utility>

using namespace std;

struct State {
	int na;
	int lowerCarry;
	int higherCarry;
	State(int q = 0, int a = 0, int s = 0) {
		na = q;
		lowerCarry = a;
		higherCarry = s;		
	}
};

class AutomatonGenerator {
private:
	int n, n1;
	int maxCarry;
	void addATransitions(State s);
	void addOneTransitions();
	void addBTransitions(State s);

public:
	AutomatonGenerator(int, int);
	void createStates();
	string getStateName(State s);
	void addTransitions();
};

AutomatonGenerator::AutomatonGenerator (int n0, int nMinusOne) {
	n = n0;
	n1 = nMinusOne;
	maxCarry = n + n1 - 1;
}

string AutomatonGenerator::getStateName(State s) {
	int x = s.na*4 + s.lowerCarry * 2 + s.higherCarry + 2;
	return " Q" + to_string(x)+" ";
}

void AutomatonGenerator::createStates() {
	for(int na = 0; na <=n; na++) {
		for(int lowerCarry = 0; lowerCarry <=maxCarry; lowerCarry++) {
			for(int higherCarry = 0; higherCarry <=maxCarry; higherCarry++) {	
				cout << getStateName(State(na,lowerCarry, higherCarry)) <<endl;	
			}
		}
	}
}

void AutomatonGenerator::addBTransitions(State s) {
	string sname = getStateName(s);
	for (int incomingCarry = 0; incomingCarry <= maxCarry; incomingCarry++) {
		for (int nguess = 0; nguess <= n; nguess++) {
			for (int n1guess = 0; n1guess <= n1; n1guess++) {
				int higherBit = (incomingCarry + nguess + n1guess) % 2;
				int higherCarry = (incomingCarry + nguess + n1guess) / 2;
				int lowerBit = (s.lowerCarry + s.na + n1guess) % 2;
				int lowerCarry = (s.lowerCarry + s.na + n1guess) / 2;
				if (higherCarry != s.higherCarry)
					continue;
				string destName = getStateName(State(nguess, lowerCarry, incomingCarry));
				cout << "(" << sname << "b" << higherBit << lowerBit << destName <<")\n";
			}
		}
	}
}

void AutomatonGenerator::addOneTransitions() {
	for (int incomingCarry = 0; incomingCarry <= maxCarry; incomingCarry++) {
		for (int nguess = 0; nguess <= n; nguess++) {
			int higherBit = (incomingCarry + nguess + n1) % 2;
			int higherCarry = (incomingCarry + nguess + n1) / 2;
			int lowerBit = (n + n1) % 2;
			int lowerCarry = (n + n1) / 2;
			if (higherCarry != 0)
				continue;
			string destName = getStateName(State(nguess, lowerCarry, incomingCarry));
			cout << "( Q1 b" << higherBit << lowerBit << destName <<")\n";
		}
	}
}

void AutomatonGenerator::addATransitions(State s) {
	string sname = getStateName(s);
	for (int n1guess = 0; n1guess <= n1; n1guess++) {
		int bit = (s.lowerCarry + s.na + n1guess) % 2;
		int carry = (s.lowerCarry + s.na + n1guess) / 2;
		if (carry != s.higherCarry)
			continue;
		cout << "(" << sname << "a" << bit << " Q10 )\n";
	}
}

void AutomatonGenerator::addTransitions() {
	cout << "( Q0 a1 Q1 )\n";
	addOneTransitions();
	for(int na = 0; na <=n; na++) {
		for(int lowerCarry = 0; lowerCarry <=maxCarry; lowerCarry++) {
			for(int higherCarry = 0; higherCarry <=maxCarry; higherCarry++) {	
				addBTransitions (State(na,lowerCarry, higherCarry));
				addATransitions (State(na,lowerCarry, higherCarry));
				cout << endl;
			}
		}
	}
}

int main() {

	AutomatonGenerator a(1,1);


	cout << "FiniteAutomaton testMachine = (\n";	
	cout << "alphabet = {a0 a1 b00 b01 b10 b11},\n";

	cout << "states = {\n";
	cout << " Q0 \n Q1 \n";
	a.createStates();
	cout<<" Q10 \n},\n";

	cout << "initialStates = {\n Q0 \n},\n";
	cout << "finalStates = {\n";
	a.createStates();
	cout<<" Q10 \n},\n";

	cout << "transitions = {\n";
	a.addTransitions();
	cout <<"\n}\n);\n";

	cout << "FiniteAutomaton finalAut = shrinkNwa(testMachine);\n";
	cout << "print(relabel(determinize(finalAut)));\n\n\n\n\n\n\n\n\n\n";
}