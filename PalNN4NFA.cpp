// Accept numbers that are the sum of n and n-4 palindromes

#include <iostream>
#include <string> 
#include <vector>
#include <utility>

using namespace std;

struct State {
	int na;
	int nb;
	int nc;
	int nd;
	int lowerCarry;
	int higherCarry;
	State(int q = 0, int w = 0, int e = 0, int r = 0, int a = 0, int s = 0) {
		na = q;
		nb = w;
		nc = e;
		nd = r;
		lowerCarry = a;
		higherCarry = s;		
	}
};

class AutomatonGenerator {
private:
	int n, n4;
	int maxCarry;
	void addATransitions();
	void addBTransitions(State s);
	void addCTransitions(State s);
	void addDTransitions(State s);
	void addETransitions(State s);
	void addFTransitions(State s);
	void addGTransitions(State s);
	void addStateTransitions(State s);

public:
	AutomatonGenerator(int, int);
	void createStates();
	string getStateName(State s);
	void addTransitions();
	void getFinalStates();
};

AutomatonGenerator::AutomatonGenerator (int n0, int nMinusFour) {
	n = n0;
	n4 = nMinusFour;
	maxCarry = n + n4 - 1;
}

string AutomatonGenerator::getStateName(State s) {
	string ret = " Q" + to_string(s.na) + to_string(s.nb);
	ret += to_string(s.nc) + to_string(s.nd);	

	return ret+"_"+to_string(s.lowerCarry)+"_"+to_string(s.higherCarry)+" ";
}

void AutomatonGenerator::getFinalStates() {
	for(int na = 0; na <=n; na++) {
		for(int nb = 0; nb <=n; nb++) {
			for(int carry = 0; carry <=maxCarry; carry++) {	
				cout << getStateName(State(na,nb,
					nb,na, carry, carry)) <<endl;	
			}
		}
	}
}


void AutomatonGenerator::createStates() {
	for(int na = 0; na <=n; na++) {
		for(int nb = 0; nb <=n; nb++) {
			for(int nc = 0; nc <=n; nc++) {
				for(int nd = 0; nd <=n; nd++) {
					for(int lowerCarry = 0; lowerCarry <=maxCarry; lowerCarry++) {
						for(int higherCarry = 0; higherCarry <=maxCarry; higherCarry++) {	
							cout << getStateName(State(na,nb,
								nc,nd,lowerCarry, higherCarry)) <<endl;	
						}
					}
				}
			}
		}
	}
}

void AutomatonGenerator::addGTransitions(State s) {
	if (s.nb != s.nd)
		return;
	string sname = getStateName(s);
	for (int n4guess = 0; n4guess <= n4; n4guess++) {
		int bit = (s.lowerCarry + s.na + n4guess) % 2;
		int carry = (s.lowerCarry + s.na + n4guess) / 2;
		if (carry != s.higherCarry)
			continue;
		cout << "(" << sname << "g" << bit << " acc)\n";
	}
}

void AutomatonGenerator::addFTransitions(State s) {
	string sname = getStateName(s);
	for (int incomingCarry = 0; incomingCarry <= maxCarry; incomingCarry++) {
		for (int nguess = 0; nguess <= n; nguess++) {
			for (int n4guess = 0; n4guess <= n4; n4guess++) {
				int higherBit = (incomingCarry + nguess + n4guess) % 2;
				int higherCarry = (incomingCarry + nguess + n4guess) / 2;
				int lowerBit = (s.lowerCarry + s.na + n4guess) % 2;
				int lowerCarry = (s.lowerCarry + s.na + n4guess) / 2;
				if (higherCarry != s.higherCarry)
					continue;
				string destName = getStateName(State(s.nb, s.nc, s.nd, nguess, lowerCarry, incomingCarry));
				cout << "(" << sname << "f" << higherBit << lowerBit << destName <<")\n";
			}
		}
	}
}

void AutomatonGenerator::addETransitions(State s) {
	if (s.lowerCarry != 0)
		return;
	string sname = getStateName(s);
	for (int incomingCarry = 0; incomingCarry <= maxCarry; incomingCarry++) {
		for (int nguess = 0; nguess <= n; nguess++) {
			int higherBit = (incomingCarry + nguess + n4) % 2;
			int higherCarry = (incomingCarry + nguess + n4) / 2;
			int lowerBit = (s.na + n4) % 2;
			int lowerCarry = (s.na + n4) / 2;
			if (higherCarry != s.higherCarry)
				continue;
			string destName = getStateName(State(s.nb, s.nc, s.nd, nguess, lowerCarry, incomingCarry));
			cout << "(" << sname << "e" << higherBit << lowerBit << destName <<")\n";
		}
	}
}

void AutomatonGenerator::addDTransitions(State s) {
	if ((s.na + s.lowerCarry) != 0)
		return;
	string sname = getStateName(s);
	for (int incomingCarry = 0; incomingCarry <= maxCarry; incomingCarry++) {
		for (int nguess = 0; nguess <= n; nguess++) {
			int higherBit = (incomingCarry + nguess) % 2;
			int higherCarry = (incomingCarry + nguess) / 2;
			if (higherCarry != s.higherCarry)
				continue;
			string destName = getStateName(State(s.na, s.nb, s.nc, nguess, 0, incomingCarry));
			cout << "(" << sname << "d" << higherBit << destName <<")\n";
		}
	}
}

void AutomatonGenerator::addCTransitions(State s) {
	if ((s.na + s.nb + s.lowerCarry) != 0)
		return;
	string sname = getStateName(s);
	for (int incomingCarry = 0; incomingCarry <= maxCarry; incomingCarry++) {
		for (int nguess = 0; nguess <= n; nguess++) {
			int higherBit = (incomingCarry + nguess) % 2;
			int higherCarry = (incomingCarry + nguess) / 2;
			if (higherCarry != s.higherCarry)
				continue;
			string destName = getStateName(State(0, s.na, s.nb, nguess, 0, incomingCarry));
			cout << "(" << sname << "c" << higherBit << destName <<")\n";
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

void AutomatonGenerator::addATransitions() {
	string sname = getStateName(State());
	for (int incomingCarry = 0; incomingCarry <= maxCarry; incomingCarry++) {
		int higherBit = (incomingCarry + n) % 2;
		int higherCarry = (incomingCarry + n) / 2;
		if ((higherBit != 1) || (higherCarry != 0))
			continue;
		string destName = getStateName(State(0, 0, 0, n, 0, incomingCarry));
		cout << "(" << sname << "a1 " << destName <<")\n";
	}
}

void AutomatonGenerator::addStateTransitions(State s) {
	addBTransitions(s);
	addCTransitions(s);
	addDTransitions(s);
	addETransitions(s);
	addFTransitions(s);
	addGTransitions(s);
}


void AutomatonGenerator::addTransitions() {
	addATransitions();
	for(int na = 0; na <=n; na++) {
		for(int nb = 0; nb <=n; nb++) {
			for(int nc = 0; nc <=n; nc++) {
				for(int nd = 0; nd <=n; nd++) {
					for(int lowerCarry = 0; lowerCarry <=maxCarry; lowerCarry++) {
						for(int higherCarry = 0; higherCarry <=maxCarry; higherCarry++) {	
							addStateTransitions (State(na,nb,
								nc,nd,lowerCarry, higherCarry));
								cout << endl;
						}
					}
				}
			}
		}
	}
}

int main() {

	AutomatonGenerator a(1,1);


	cout << "FiniteAutomaton testMachine = (\n";	
	cout << "alphabet = {a1 b0 b1 c0 c1 d0 d1 e00 e01 e10 e11 f0 f1},\n";

	cout << "states = {\n";
	a.createStates();
	cout<<"\nacc},\n";

	cout << "initialStates = {\n";
	cout << a.getStateName(State())<<endl;
	cout << "},\nfinalStates = {";
	a.getFinalStates();
	cout<<"\nacc},\n";

	cout << "transitions = {\n";
	a.addTransitions();
	cout <<"\n}\n);\n";

	cout << "FiniteAutomaton finalAut = shrinkNwa(testMachine);\n";
	cout << "print(numberOfStates(finalAut));\n\n\n\n\n\n\n\n\n\n";
}