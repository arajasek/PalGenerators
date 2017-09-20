// Conjecture:
// Every length-n base-4 number, n >= 7, is the sum of either

// (a) exactly one each of palindromes of lengths n, n-2, n-3

// or

// (b) exactly one each with lengths n-1, n-2, n-3

// Jeff

#include <iostream>
#include <string> 

using namespace std;

class AutomatonGeneratorCaseB {
public:
	string name;
	int maxCarry;
	int base;
	void createStates();
	void createInitialStates();
	void createFinalStates();

	string getStateName(int, int, int, int, int);
	void addBtransitions();
	void addAtransitions();
	void addCtransitions();
	void addDtransitions();
	void addEtransitions();
	void addTransitions();

	AutomatonGeneratorCaseB(int);
};

AutomatonGeneratorCaseB::AutomatonGeneratorCaseB(int b) {
	maxCarry = 2;
	base = b;
}
//Q States are 5-tuples (c1, c2, x, y, z)
// c1, expected higher carry
// c2, produced lower carry
// x, the next lower guess of the n-word
// y, the two-away lower guess of the n-word
// z, the next lower guess of the n-1-word

string AutomatonGeneratorCaseB::getStateName(int c1, int c2, int x, int y, int z) {
	return ("B_"+to_string(c1)+"_"+to_string(c2)+"_"+to_string(x)+to_string(y)+to_string(z));
}

void AutomatonGeneratorCaseB::addEtransitions() {
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int c2 = 0; c2 <= maxCarry; c2++) {
			for (int x = 0; x < base; x++) {
				for (int y = 0; y < base; y++) {
					for (int z = 0; z < base; z++) {
						string originState = getStateName(c1, c2, x, y, z);
						for (int j = 0; j < base; j++) {
							int bit = (x + j + c2 + z) % base;
							int carry = (x + j + c2 + z) / base;										
							if (carry == c1) {
								cout << "(" << originState <<" e" << bit <<" acc)\n";
							}
						}
					}
				}
			}
		}
	}
}


void AutomatonGeneratorCaseB::addDtransitions() {
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int c2 = 0; c2 <= maxCarry; c2++) {
			for (int x = 0; x < base; x++) {
				for (int y = 0; y < base; y++) {
					for (int z = 0; z < base; z++) {
						string originState = getStateName(c1, c2, x, y, z);
						for (int newc1 = 0; newc1 <= maxCarry; newc1++) {
							for (int i = 0; i < base; i++) {
								for (int j = 0; j < base; j++) {
									for (int k = 0; k < base; k++) {
										int higherBit = (i + j + newc1 + z) % base;
										int higherCarry = (i + j + newc1 + z) / base;
										int lowerBit = (x + j + c2 + k) % base;
										int lowerCarry = (x + j + c2 + k) / base;
										if (higherCarry == c1) {
											cout << "(" << originState <<" d" << higherBit << lowerBit;
											cout << " " << getStateName(newc1, lowerCarry, y, i, k)<<")\n";
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void AutomatonGeneratorCaseB::addCtransitions() {
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int x = 1; x < base; x++) {
			for (int y = 0; y < base; y++) {
				string originState = getStateName(c1, 0, x, y, 0);
				for (int newc1 = 0; newc1 <= maxCarry; newc1++) {
					for (int i = 0; i < base; i++) {
						for (int j = 1; j < base; j++) {
							for (int k = 1; k < base; k++) {
								int higherBit = (i + j + newc1) % base;
								int higherCarry = (i + j + newc1) / base;
								int lowerBit = (x + j + k) % base;
								int lowerCarry = (x + j + k) / base;
								if (higherCarry == c1) {
									cout << "(" << originState <<" c" << higherBit << lowerBit;
									cout << " " << getStateName(newc1, lowerCarry, y, i, k)<<")\n";
								}
							}
						}
					}
				}
			}
		}
	}
}

void AutomatonGeneratorCaseB::addBtransitions() {
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int x = 1; x < base; x++) {
			string originState = getStateName(c1, 0, 0, x, 0);
			for (int newc1 = 0; newc1 <= maxCarry; newc1++) {
				for (int newx = 0; newx < base; newx++) {
					int bit = (newc1 + newx) % base;
					int newCarry = (newc1 + newx) / base;
					if (newCarry == c1)
						cout << "(" << originState <<" b" << bit << " " << getStateName(newc1, 0, x, newx, 0)<<")\n";
				}
			}
		}
	}
}

void AutomatonGeneratorCaseB::addAtransitions() {
	string initState = getStateName(0, 0, 0, 0, 0);
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int y = 1; y < base; y++) {
			int bit = (c1 + y) % base;
			int newCarry = (c1 + y) / base;
			if ((bit != 0) && (newCarry == 0))
				cout << "(" << initState<<" a" << bit << " " << getStateName(c1, 0, 0, y, 0)<<")\n";
		}
	}
}

void AutomatonGeneratorCaseB::createStates () {
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int c2 = 0; c2 <= maxCarry; c2++) {
			for (int x = 0; x < base; x++) {
				for (int y = 0; y < base; y++) {
					for (int z = 0; z < base; z++) {
						cout<<getStateName(c1, c2, x, y, z)<<endl;
					}
				}
			}
		}
	}
}
void AutomatonGeneratorCaseB::createInitialStates() {
	cout << getStateName(0, 0, 0, 0, 0)<<endl;
}
void AutomatonGeneratorCaseB::createFinalStates() {
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int x = 0; x < base; x++) {
			for (int z = 0; z < base; z++) {
				cout<<getStateName(c1, c1, x, x, z)<<endl;
			}
		}
	}
}

void AutomatonGeneratorCaseB::addTransitions() {
	addAtransitions();
	addBtransitions();
	addCtransitions();
	addDtransitions();
	addEtransitions();
}

class AutomatonGeneratorCaseC {
public:
	int maxCarry;
	int base;
	void createStates();
	void createInitialStates();
	void createFinalStates();

	string getStateName(int, int, int, int);
	void addBtransitions();
	void addAtransitions();
	void addCtransitions();
	void addDtransitions();
	void addEtransitions();
	void addTransitions();
	AutomatonGeneratorCaseC(int);
};

AutomatonGeneratorCaseC::AutomatonGeneratorCaseC(int b) {
	maxCarry = 2;
	base = b;
}

//Q States are -tuples (c1, c2, x, z)
// c1, expected higher carry
// c2, produced lower carry
// x, the next lower guess of the n-1-word
// z, the next higher guess of the n-3-word

string AutomatonGeneratorCaseC::getStateName(int c1, int c2, int x, int z) {
	return ("C_"+to_string(c1)+"_"+to_string(c2)+"_"+to_string(x)+to_string(z));
}

void AutomatonGeneratorCaseC::addEtransitions() {
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int c2 = 0; c2 <= maxCarry; c2++) {
			for (int x = 0; x < base; x++) {
				for (int z = 0; z < base; z++) {
					string originState = getStateName(c1, c2, x, z);
					for (int j = 0; j < base; j++) {
							int bit = (x + c2 + j + z) % base;
							int carry = (x + c2 + j + z) / base;
							if (carry == c1) {
								cout << "(" << originState <<" e" << bit << " acc)\n";
						}
					}
				}
			}
		}
	}
}

void AutomatonGeneratorCaseC::addDtransitions() {
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int c2 = 0; c2 <= maxCarry; c2++) {
			for (int x = 0; x < base; x++) {
				for (int z = 0; z < base; z++) {
					string originState = getStateName(c1, c2, x, z);
					for (int newc1 = 0; newc1 <= maxCarry; newc1++) {
						for (int i = 0; i < base; i++) {
							for (int j = 0; j < base; j++) {
								for (int k = 0; k < base; k++) {
									int higherBit = (i + j + newc1 + z) % base;
									int higherCarry = (i + j + newc1 + z) / base;
									int lowerBit = (x + j + c2 + k) % base;
									int lowerCarry = (x + j + c2 + k) / base;
									if (higherCarry == c1) {
										cout << "(" << originState <<" d" << higherBit << lowerBit;
										cout << " " << getStateName(newc1, lowerCarry, i, k)<<")\n";
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void AutomatonGeneratorCaseC::addCtransitions() {
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int x = 1; x < base; x++) {
			string originState = getStateName(c1, 0, x, 0);
			for (int newc1 = 0; newc1 <= maxCarry; newc1++) {
				for (int i = 0; i < base; i++) {
					for (int j = 1; j < base; j++) {
						for (int k = 1; k < base; k++) {
							int higherBit = (i + j + newc1) % base;
							int higherCarry = (i + j + newc1) / base;
							int lowerBit = (x + j + k) % base;
							int lowerCarry = (x + j + k) / base;
							if (higherCarry == c1) {
								cout << "(" << originState <<" c" << higherBit << lowerBit;
								cout << " " << getStateName(newc1, lowerCarry, i, k)<<")\n";
							}
						}
					}
				}
			}
		}
	}
}

void AutomatonGeneratorCaseC::addBtransitions() {
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		string originState = getStateName(c1, 0, 0, 0);
		for (int newc1 = 0; newc1 <= maxCarry; newc1++) {
			for (int newx = 1; newx < base; newx++) {
				int bit = (newc1 + newx) % base;
				int newCarry = (newc1 + newx) / base;
				if (newCarry == c1)
					cout << "(" << originState <<" b" << bit << " " << getStateName(newc1, 0, newx, 0)<<")\n";
			}
		}
	}
}

void AutomatonGeneratorCaseC::addAtransitions() {
	string initState = getStateName(0, 0, 0, 0);
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		int bit = c1 % base;
		if (bit != 0)
			cout << "(" << initState<<" a" << bit << " " << getStateName(c1, 0, 0, 0)<<")\n";
	}
}

void AutomatonGeneratorCaseC::createStates () {
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int c2 = 0; c2 <= maxCarry; c2++) {
			for (int x = 0; x < base; x++) {
				for (int z = 0; z < base; z++) {
					cout<<getStateName(c1, c2, x, z)<<endl;
				}
			}
		}
	}
}

void AutomatonGeneratorCaseC::createInitialStates() {
	cout << getStateName(0, 0, 0, 0)<<endl;
}

void AutomatonGeneratorCaseC::createFinalStates() {
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int x = 0; x < base; x++) {
			for (int z = 0; z < base; z++) {
				cout<<getStateName(c1, c1, x, z)<<endl;
			}
		}
	}
}

void AutomatonGeneratorCaseC::addTransitions() {
	addAtransitions();
	addBtransitions();
	addCtransitions();
	addDtransitions();
	addEtransitions();
}


int main() {
	AutomatonGeneratorCaseB b (4);
	AutomatonGeneratorCaseC c (4);
	cout << "FiniteAutomaton palBase4 = (\n";
	//the first input symbol is either a1/a2, then we read b0/b1/b2,
	//then a c-pair, then d-pairs, and finally a terminal e-element if odd-length input
	cout << "alphabet = {a1 a2 a3 b0 b1 b2 b3 \n";
	cout << "c00 c01 c02 c03 c10 c11 c12 c13 c20 c21 c22 c23 c30 c31 c32 c33 \n";
	cout << "d00 d01 d02 d03 d10 d11 d12 d13 d20 d21 d22 d23 d30 d31 d32 d33 \n";
	cout << "e0 e1 e2 e3},\n";
	cout << "states = { \n";
	b.createStates();
	c.createStates();
	cout << "acc},\ninitialStates = {";
	b.createInitialStates();
	c.createInitialStates();
	cout<<"},\nfinalStates = {";
	b.createFinalStates();
	c.createFinalStates();
	cout<<"acc},\n";
	cout << "transitions = {\n";
	b.addTransitions();
	c.addTransitions();
	cout << "}\n";
	cout << ");\nprint(numberOfStates(palBase4));\n";
	cout << "FiniteAutomaton finalAut = shrinkNwa(palBase4);\n";
	cout << "print(numberOfStates(finalAut));\n\n\n\n\n\n";
}