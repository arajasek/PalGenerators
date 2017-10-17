// - every length-n number, n odd, n>= 5, with at most finitely many 
// exceptions, is the sum of either

// - 1 or 2 antipalindromes of length n-1 and
//   - at most 2 antipalindromes of length n-3

// OR

//  1 antipalindrome of length n-1 and
// - at most 2 antipalindromes of length n-3 and
// the number 2 (which MUST appear)


#include <iostream>
#include <string> 

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

class AutomatonGeneratorCaseA {
public:
	string name;
	int maxCarry;
	int n1, n3;
	void createStates();
	void createInitialStates();
	void createFinalStates();
	string getStateName(State);
	void addAtransitions();
	void addBtransitions(State);
	void addCtransitions(State);
	void addDtransitions(State);
	void addTransitions();
	AutomatonGeneratorCaseA(int, int);
};

AutomatonGeneratorCaseA::AutomatonGeneratorCaseA(string n, int a, int b) {
	name = " " + n + "_";
	n1 = a;
	n3 = b;
	maxCarry = n1 + n3 - 1;
}

string AutomatonGeneratorCaseA::getStateName(State s) {
	string ret = name + to_string(s.na) + to_string(s.nb);
	return ret+"_"+to_string(s.lowerCarry)+"_"+to_string(s.higherCarry)+" ";
}

void AutomatonGeneratorCaseA::addDtransitions(State s) {
	string sname = getStateName(s);
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int z1 = 0; z1 <= n1; z1++) {
			for (int x1 = 0; x1 <= n3; x1++) {
				int higherBit = (c1 + z1 + x1) % 2;
				int higherCarry = (c1 + z1 + x1) / 2;
				int lowerBit = (s.na + x1) % 2;
				int lowerCarry = (s.na + x1) / 2;
				if (higherCarry == s.higherCarry)
					cout << "(" << sname<<" d" << higherBit << lowerBit << getStateName(State(s.nb, z1, lowerCarry, c1))<<")\n";
			}
		}
	}
}

void AutomatonGeneratorCaseA::addCtransitions(State s) {
	if ((s.na != n1) || (s.lowerCarry != 0))
		return;
	string sname = getStateName(s);
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int z1 = 0; z1 <= n1; z1++) {
			int higherBit = (c1 + z1 + n3) % 2;
			int higherCarry = (c1 + z1 + n3) / 2;
			int lowerBit = (s.na + n3) % 2;
			int lowerCarry = (s.na + n3) / 2;
			if (higherCarry == s.higherCarry)
				cout << "(" << sname<<" c" << higherBit << lowerBit << getStateName(State(s.nb, z1, lowerCarry, c1))<<")\n";
		}
	}
}


void AutomatonGeneratorCaseA::addBtransitions(State s) {
	if ((s.na != 0) || (s.lowerCarry != 0) || (s.nb != n1))
		return;
	string sname = getStateName(s);
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int z1 = 0; z1 <= n1; z1++) {
			int bit = (c1 + z1) % 2;
			int newCarry = (c1 + z1) / 2;
			if (newCarry == s.higherCarry)
				cout << "(" << sname<<" b" << bit << getStateName(State(s.nb, z1, 0, c1))<<")\n";
		}
	}
}

void AutomatonGeneratorCaseA::addAtransitions() {
	string initState = getStateName(State(0, 0, 0, 1));
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		int bit = (c1 + n1) % 2;
		int newCarry = (c1 + n1) / 2;
		if (newCarry == 1)
			cout << "(" << initState<<" a" << bit << getStateName(State(0, n1, 0, c1))<<")\n";
	}
}

void AutomatonGeneratorCaseA::createStates () {
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int c2 = 0; c2 <= maxCarry; c2++) {
			for (int z1 = 0; z1 <= n1; z1++) {
				for (int z2 = 0; z2 <= n1; z2++)
					cout<<getStateName(State(z1, z2, c1, c2))<<endl;
			}
		}
	}
}

void AutomatonGeneratorCaseA::createInitialStates() {
	cout << getStateName(State(0, 0, 0, 1))<<endl;
}

void AutomatonGeneratorCaseA::createFinalStates () {
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int z1 = 0; z1 <= n1; z1++)
			cout<<getStateName(State(z1, z1, c1, c1))<<endl;
	}
}

void AutomatonGeneratorCaseA::addTransitions() {
	addAtransitions();
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int c2 = 0; c2 <= maxCarry; c2++) {
			for (int z1 = 0; z1 <= n1; z1++) {
				for (int z2 = 0; z2 <= n1; z2++) {
					addBtransitions(State(z1, z2, c1, c2));
					addCtransitions(State(z1, z2, c1, c2));
					addDtransitions(State(z1, z2, c1, c2));
				}
			}
		}
	}
}

int main() {
	AutomatonGeneratorCaseA a1 (2, 0);
	AutomatonGeneratorCaseA a2 (1, 2);
	AutomatonGeneratorCaseA a3 (2, 2);
	AutomatonGeneratorCaseA b1 (2, 2);
	AutomatonGeneratorCaseA b2 (2, 2);
	cout << "FiniteAutomaton oddAntiPal = (\n";
	//the first input symbol is a0 / a1, then we read b0/b1,
	//then a c-pair, then d-pairs
	//note that the leading 1 is assumed
	cout << "alphabet = {a0 a1 b0 b1 c00 c01 c10 c11 " 
			<< "d00 d01 d10 d11},\n";
	cout << "states = { \n";
	a1.createStates();
	a2.createStates();
	a3.createStates();
	cout << "acc},\ninitialStates = {";
	a1.createInitialStates();
	a2.createInitialStates();
	a3.createInitialStates();
	cout<<"},\nfinalStates = {";
	a1.createFinalStates();
	a2.createFinalStates();
	a3.createFinalStates();
	cout<<"acc},\n";
	cout << "transitions = {\n";
	a1.addTransitions();
	a2.addTransitions();
	a3.addTransitions();
	cout << "}\n";
	cout << ");\nprint(numberOfStates(oddAntiPal));\n";
	cout << "FiniteAutomaton finalAut = shrinkNwa(oddAntiPal);\n";
	cout << "print(numberOfStates(finalAut));\n\n\n\n\n\n";
}