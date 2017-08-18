/*

Conjecture:  Consider the length-n integers in base 3 that are the sums 
of either

(a) one each exactly of palindromes of length n, n-1, n-2

(b) one each exactly of palindromes of length n, n-2, n-3

(c) one each exactly of palindromes of length n-1, n-2, n-3

Then all integers are represented with only finitely many exceptions.

*/

#include <iostream>
#include <string> 

using namespace std;

class AutomatonGeneratorCaseA {
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
	AutomatonGeneratorCaseA(int);
};

AutomatonGeneratorCaseA::AutomatonGeneratorCaseA(int b) {
	maxCarry = 2;
	base = b;
}

// //Q States are 5-tuples (c1, c2, x, y, z)
// // c1, expected higher carry
// // c2, produced lower carry
// // x, the next lower guess of the n-word
// // y, the two-away lower guess of the n-word
// // z, the next lower guess of the n-1-word

string AutomatonGeneratorCaseA::getStateName(int c1, int c2, int x, int y, int z) {
	return ("A_"+to_string(c1)+"_"+to_string(c2)+"_"+to_string(x)+to_string(y)+to_string(z));
}

void AutomatonGeneratorCaseA::addEtransitions() {
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
										int higherBit = (i + j + newc1 + k) % base;
										int higherCarry = (i + j + newc1 + k) / base;
										int lowerBit = (x + z + c2 + k) % base;
										int lowerCarry = (x + z + c2 + k) / base;
										if (higherCarry == c1) {
											cout << "(" << originState <<" e" << higherBit << lowerBit;
											cout << " " << getStateName(newc1, lowerCarry, y, i, j)<<")\n";
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

void AutomatonGeneratorCaseA::addBtransitions() {
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int x = 0; x < base; x++) {
			string originState = getStateName(c1, 0, 0, x, 0);
			for (int newc1 = 0; newc1 <= maxCarry; newc1++) {
				for (int newx = 0; newx < base; newx++) {
					for (int j = 0; j < base; j++) {
						int bit = (newc1 + newx + j) % base;
						int newCarry = (newc1 + newx + j) / base;
						if (newCarry == c1)
							cout << "(" << originState <<" b" << bit << " " << getStateName(newc1, 0, x, newx, j)<<")\n";
					}	
				}
			}
		}
	}
}

void AutomatonGeneratorCaseA::addAtransitions() {
	string initState = getStateName(0, 0, 0, 0, 0);
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int y = 1; y < base; y++) {
			int bit = (c1 + y) % base;
			int newCarry = (c1 + y) / base;
			if (bit != 0)
				cout << "(" << initState<<" a" << bit << " " << getStateName(c1, 0, 0, y, 0)<<")\n";
		}
	}
}

void AutomatonGeneratorCaseA::createStates () {
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
void AutomatonGeneratorCaseA::createInitialStates() {
	cout << getStateName(0, 0, 0, 0, 0)<<endl;
}
void AutomatonGeneratorCaseA::createFinalStates() {
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int x = 0; x < base; x++) {
			for (int z = 0; z < base; z++) {
				cout<<getStateName(c1, c1, x, x, z)<<endl;
			}
		}
	}
}

void AutomatonGeneratorCaseA::addTransitions() {
	addAtransitions();
	addBtransitions();
	addCtransitions();
	addDtransitions();
	addEtransitions();
}

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
						for (int newc1 = 0; newc1 <= maxCarry; newc1++) {
							for (int i = 0; i < base; i++) {
								for (int j = 0; j < base; j++) {
									for (int k = 0; k < base; k++) {
										int higherBit = (i + j + newc1 + z) % base;
										int higherCarry = (i + j + newc1 + z) / base;
										int lowerBit = (x + j + c2 + k) % base;
										int lowerCarry = (x + j + c2 + k) / base;
										if (higherCarry == c1) {
											cout << "(" << originState <<" e" << higherBit << lowerBit;
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

void AutomatonGeneratorCaseB::addBtransitions() {
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int x = 0; x < base; x++) {
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
			if (bit != 0)
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
						for (int newc1 = 0; newc1 <= maxCarry; newc1++) {
							for (int i = 0; i < base; i++) {
								for (int j = 0; j < base; j++) {
									for (int k = 0; k < base; k++) {
										int higherBit = (i + j + newc1 + z) % base;
										int higherCarry = (i + j + newc1 + z) / base;
										int lowerBit = (x + j + c2 + k) % base;
										int lowerCarry = (x + j + c2 + k) / base;
										if (higherCarry == c1) {
											cout << "(" << originState <<" e" << higherBit << lowerBit;
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
		for (int x = 0; x < base; x++) {
			string originState = getStateName(c1, 0, x, 0);
			for (int newc1 = 0; newc1 <= maxCarry; newc1++) {
				for (int i = 0; i < base; i++) {
					for (int j = 1; j < base; j++) {
						for (int k = 0; k < base; k++) {
							int higherBit = (i + j + newc1 + z) % base;
							int higherCarry = (i + j + newc1 + z) / base;
							int lowerBit = (x + j + c2 + k) % base;
							int lowerCarry = (x + j + c2 + k) / base;
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
			for (int newx = 0; newx < base; newx++) {
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
		int newCarry = c1 / base;
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
	AutomatonGeneratorCaseA a (3);
	AutomatonGeneratorCaseB b (3);
	AutomatonGeneratorCaseC c (3);
	cout << "FiniteAutomaton palBase3 = (\n";
	//the first input symbol is either b0/b1, then we read c0/c1/c2, and then a-pairs
	cout << "alphabet = {a1 a2 b0 b1 b2 c00 c01 c02 c10 c11 c12 c20 c21 c22" 
			<< "d00 d01 d02 d10 d11 d12 d20 d21 d22 e00 e01 e02 e10 e11 e12 e20 e21 e22 },\n";
	cout << "states = { \n";
	a.createStates();
	b.createStates();
	c.createStates();
	cout << "},\ninitialStates = {";
	a.createInitialStates();
	b.createInitialStates();
	c.createInitialStates();
	cout<<"},\nfinalStates = {";
	a.createFinalStates();
	b.createFinalStates();
	c.createFinalStates();
	cout<<"},\n";
	cout << "transitions = {\n";
	a.addTransitions();
	b.addTransitions();
	c.addTransitions();
	cout << "}\n";
	cout << ");\nprint(numberOfStates(palBase3));\n";
	cout << "FiniteAutomaton finalAut = shrinkNwa(palBase3);\n";
	cout << "print(numberOfStates(finalAut));\n\n\n\n\n\n";
	cout << "print(accepts(finalAut, [b1 c1 a22 a10]));\n\n\n\n\n\n";
}