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
private:
	string name;
	int maxCarry;
	int base;
	void createStates();
	string getStateName(int, int, int, int, int);
	void addBtransitions();
	void addAtransitions();
	void addCtransitions();

public:
	AutomatonGeneratorCaseA(string, int, int);
	void print();
};

AutomatonGeneratorCaseA::AutomatonGeneratorCaseA(string subname, int mc, int b) {
	name = "palChecker_" + subname;
	maxCarry = mc;
	base = b;
}

// //Q States are 5-tuples (c1, c2, x, y, z)
// // c1, expected higher carry
// // c2, produced lower carry
// // x, the next lower guess of the n-word
// // y, the two-away lower guess of the n-word
// // z, the next lower guess of the n-1-word

string AutomatonGeneratorCaseA::getStateName(int c1, int c2, int x, int y, int z) {
	return ("q_"+to_string(c1)+"_"+to_string(c2)+"_"+to_string(x)+to_string(y)+to_string(z));
}

void AutomatonGeneratorCaseA::addAtransitions() {
	cout << "transitions = {\n";
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
											cout << "(" << originState <<" a" << higherBit << lowerBit;
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

void AutomatonGeneratorCaseA::addCtransitions() {
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int x = 0; x < base; x++) {
			string originState = getStateName(c1, 0, 0, x, 0);
			for (int newc1 = 0; newc1 <= maxCarry; newc1++) {
				for (int newx = 0; newx < base; newx++) {
					for (int j = 0; j < base; j++) {
						int bit = (newc1 + newx + j) % base;
						int newCarry = (newc1 + newx + j) / base;
						if (newCarry == c1)
							cout << "(" << originState <<" c" << bit << " " << getStateName(newc1, 0, x, newx, j)<<")\n";
					}	
				}
			}
		}
	}
	cout << "}\n";
	cout << ");\n";
}

void AutomatonGeneratorCaseA::addBtransitions() {
	string initState = getStateName(0, 0, 0, 0, 0);
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int y = 0; y < base; y++) {
			int bit = (c1 + y) % base;
			int newCarry = (c1 + y) / base;
			if (bit != 0)
				cout << "(" << initState<<" b" << bit << " " << getStateName(c1, 0, 0, y, 0)<<")\n";
		}
	}
}

void AutomatonGeneratorCaseA::createStates () {
	cout << "states = { \n";
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
	cout << "},\ninitialStates = {";
	cout << getStateName(0, 0, 0, 0, 0);
	cout<<"},\nfinalStates = {";
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int x = 0; x < base; x++) {
			for (int y = 0; y < base; y++) {
				for (int z = 0; z < base; z++) {
					cout<<getStateName(c1, c1, x, y, z)<<endl;
				}
			}
		}
	}
	cout<<"},\n";
}

void AutomatonGeneratorCaseA::print() {
	cout << "FiniteAutomaton "<<name<<" = (\n";
	//the first input symbol is either b0/b1, then we read c0/c1/c2, and then a-pairs
	cout << "alphabet = {a00 a01 a02 a10 a11 a12 a20 a21 a22 b1 b2 c0 c1 c2},\n";
	createStates();
	addAtransitions();
	addBtransitions();
	addCtransitions();
	cout << "FiniteAutomaton finalAut = shrinkNwa(complement("<<name<<"));\n";
}

class AutomatonGeneratorCaseB {
private:
	string name;
	int maxCarry;
	int base;
	void createStates();
	string getStateName(int, int, int, int, int);
	void addBtransitions();
	void addAtransitions();
	void addCtransitions();

public:
	AutomatonGeneratorCaseB(string, int, int);
	void print();
};

AutomatonGeneratorCaseB::AutomatonGeneratorCaseB(string subname, int mc, int b) {
	name = "palChecker_" + subname;
	maxCarry = mc;
	base = b;
}

//Q States are 5-tuples (c1, c2, x, y, z)
// c1, expected higher carry
// c2, produced lower carry
// x, the next lower guess of the n-word
// y, the two-away lower guess of the n-word
// z, the next lower guess of the n-1-word

string AutomatonGeneratorCaseB::getStateName(int c1, int c2, int x, int y, int z) {
	return ("q_"+to_string(c1)+"_"+to_string(c2)+"_"+to_string(x)+to_string(y)+to_string(z));
}

void AutomatonGeneratorCaseB::addAtransitions() {
	cout << "transitions = {\n";
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
											cout << "(" << originState <<" a" << higherBit << lowerBit;
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
		for (int x = 0; x < base; x++) {
			string originState = getStateName(c1, 0, 0, x, 0);
			for (int newc1 = 0; newc1 <= maxCarry; newc1++) {
				for (int newx = 0; newx < base; newx++) {
					int bit = (newc1 + newx) % base;
					int newCarry = (newc1 + newx) / base;
					if (newCarry == c1)
						cout << "(" << originState <<" c" << bit << " " << getStateName(newc1, 0, x, newx, 0)<<")\n";
				}
			}
		}
	}
	cout << "}\n";
	cout << ");\n";
}

void AutomatonGeneratorCaseB::addBtransitions() {
	string initState = getStateName(0, 0, 0, 0, 0);
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int y = 0; y < base; y++) {
			int bit = (c1 + y) % base;
			int newCarry = (c1 + y) / base;
			if (bit != 0)
				cout << "(" << initState<<" b" << bit << " " << getStateName(c1, 0, 0, y, 0)<<")\n";
		}
	}
}

void AutomatonGeneratorCaseB::createStates () {
	cout << "states = { \n";
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
	cout << "},\ninitialStates = {";
	cout << getStateName(0, 0, 0, 0, 0);
	cout<<"},\nfinalStates = {";
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int x = 0; x < base; x++) {
			for (int y = 0; y < base; y++) {
				for (int z = 0; z < base; z++) {
					cout<<getStateName(c1, c1, x, y, z)<<endl;
				}
			}
		}
	}
	cout<<"},\n";
}

void AutomatonGeneratorCaseB::print() {
	cout << "FiniteAutomaton "<<name<<" = (\n";
	//the first input symbol is either b0/b1, then we read c0/c1/c2, and then a-pairs
	cout << "alphabet = {a00 a01 a02 a10 a11 a12 a20 a21 a22 b1 b2 c0 c1 c2},\n";
	createStates();
	addAtransitions();
	addBtransitions();
	addCtransitions();
	cout << "FiniteAutomaton " << name <<"Comp = shrinkNwa(complement(" << name << "));\n";
	cout << "finalAut = shrinkNwa(intersect(finalAut, "<<name<<"Comp));\n";
}

class AutomatonGeneratorCaseC {
private:
	string name;
	int maxCarry;
	int base;
	void createStates();
	string getStateName(int, int, int, int);
	void addBtransitions();
	void addAtransitions();
	void addCtransitions();

public:
	AutomatonGeneratorCaseC(string, int, int);
	void print();
};

AutomatonGeneratorCaseC::AutomatonGeneratorCaseC(string subname, int mc, int b) {
	name = "palChecker_" + subname;
	maxCarry = mc;
	base = b;
}

//Q States are -tuples (c1, c2, x, z)
// c1, expected higher carry
// c2, produced lower carry
// x, the next lower guess of the n-1-word
// z, the next higher guess of the n-3-word

string AutomatonGeneratorCaseC::getStateName(int c1, int c2, int x, int z) {
	return ("q_"+to_string(c1)+"_"+to_string(c2)+"_"+to_string(x)+to_string(z));
}

void AutomatonGeneratorCaseC::addAtransitions() {
	cout << "transitions = {\n";
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
											cout << "(" << originState <<" a" << higherBit << lowerBit;
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
		string originState = getStateName(c1, 0, 0, 0);
		for (int newc1 = 0; newc1 <= maxCarry; newc1++) {
			for (int newx = 0; newx < base; newx++) {
				int bit = (newc1 + newx) % base;
				int newCarry = (newc1 + newx) / base;
				if (newCarry == c1)
					cout << "(" << originState <<" c" << bit << " " << getStateName(newc1, 0, newx, 0)<<")\n";
			}
		}
	}
	cout << "}\n";
	cout << ");\n";
}

void AutomatonGeneratorCaseC::addBtransitions() {
	string initState = getStateName(0, 0, 0, 0);
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		int bit = c1 % base;
		int newCarry = c1 / base;
		if (bit != 0)
			cout << "(" << initState<<" b" << bit << " " << getStateName(c1, 0, 0, 0)<<")\n";
	}
}

void AutomatonGeneratorCaseC::createStates () {
	cout << "states = { \n";
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int c2 = 0; c2 <= maxCarry; c2++) {
			for (int x = 0; x < base; x++) {
				for (int z = 0; z < base; z++) {
					cout<<getStateName(c1, c2, x, z)<<endl;
				}
			}
		}
	}
	cout << "},\ninitialStates = {";
	cout << getStateName(0, 0, 0, 0);
	cout<<"},\nfinalStates = {";
	for (int c1 = 0; c1 <= maxCarry; c1++) {
		for (int x = 0; x < base; x++) {
			for (int z = 0; z < base; z++) {
				cout<<getStateName(c1, c1, x, z)<<endl;
			}
		}
	}
	cout<<"},\n";
}

void AutomatonGeneratorCaseC::print() {
	cout << "FiniteAutomaton "<<name<<" = (\n";
	//the first input symbol is either b0/b1, then we read c0/c1/c2, and then a-pairs
	cout << "alphabet = {a00 a01 a02 a10 a11 a12 a20 a21 a22 b1 b2 c0 c1 c2},\n";
	createStates();
	addAtransitions();
	addBtransitions();
	addCtransitions();
	cout << "FiniteAutomaton " << name <<"Comp = shrinkNwa(complement(" << name << "));\n";
	cout << "finalAut = shrinkNwa(intersect(finalAut, "<<name<<"Comp));\n";
	cout << "finalAut = shrinkNwa(complement(finalAut));\n\n\n\n\n\n";
}


int main() {
	AutomatonGeneratorCaseA a ("caseA", 2, 3);
	a.print();
	AutomatonGeneratorCaseB b ("caseB", 2, 3);
	b.print();
	AutomatonGeneratorCaseC c ("caseC", 2, 3);
	c.print();
}