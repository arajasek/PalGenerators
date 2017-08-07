/*

Every length-n ODD integer, n >= 8, is either represented by

(a) sum of at most 1 palindrome each of lengths n-1, n-2, n-3
(b) sum of at most 1 palindrome each of lengths n, n-2, n-3

This program generates the automaton for 

1 length n,
0 length n-2
1 length n-3

*/

#include <iostream>
#include <string> 

using namespace std;

//Q States are 6-tuples (carry, x,z, m1, m2, m3)
// a carry
// x, the next length-n guess
// z, the previous n-3 guess
// m1, m2 and m3 are the three previous n-3 guesses

class AutomatonGenerator {
private:
	string name;
	int maxCarry;
	string getQStateName(int carry, int x, int z, int m1, int m2, int m3);
	void createStates();
	void printCallTransitions();
	void printReturnTransitions();
	void printQReturnTransitions();
	void printSReturnTransitions();
	void printSingleQReturn(int, string);
	void printInternalTransitions();
public:
	AutomatonGenerator(string);
	void print();

};

AutomatonGenerator::AutomatonGenerator(string subname) {
	name = "palChecker_" + subname;
	maxCarry = 2;
}

string AutomatonGenerator::getQStateName(int carry, int x, int z, int m1, int m2, int m3) {
	return ("q_"+to_string(carry)+"_"+to_string(x)+to_string(z)+"_"
		+to_string(m1)+to_string(m2)+to_string(m3));
}

void AutomatonGenerator::printSReturnTransitions() {
	for (int stateCarry = 0; stateCarry < maxCarry; stateCarry++) {
		string currName = "s"+to_string(stateCarry);
		for (int carry = 0; carry <= maxCarry; carry++) {
			for (int x = 0; x <= 1; x++) {
				for (int z = 0; z <= 1; z++) {
					for (int m1 = 0; m1 <= 1; m1++) {
						for (int m2 = 0; m2 <= 1; m2++) {
							for (int m3 = 0; m3 <= 1; m3++) {
								string topName = getQStateName(carry, x, z, m1, m2, m3);
								int bit = (stateCarry + x + m3) % 2;
								int newCarry = (stateCarry + x + m3) / 2;
								char inp = 'e' + bit;
								cout<<"("<<currName<<" "<<topName<<" "<<inp<<" "<<"s"<<newCarry<<")\n";
							}
						}
					}
				}
			}
		}
	}
}

void AutomatonGenerator::printSingleQReturn(int c, string currName) {
	for (int carry = 0; carry <= maxCarry; carry++) {
		for (int x = 0; x <= 1; x++) {
			for (int z = 0; z <= 1; z++) {
				for (int m1 = 0; m1 <= 1; m1++) {
					for (int m2 = 0; m2 <= 1; m2++) {
						for (int m3 = 0; m3 <= 1; m3++) {
							string topName = getQStateName(carry, x, z, m1, m2, m3);
							int bit = (c + x + m3) % 2;
							int newCarry = (c + x + m3) / 2;
							char inp = 'e' + bit;
							cout<<"("<<currName<<" "<<topName<<" "<<inp<<" "<<"s"<<newCarry<<")\n";
						}
					}
				}
			}
		}
	}
}

void AutomatonGenerator::printQReturnTransitions() {
	for (int carry = 0; carry <= maxCarry; carry++) {
		for (int x = 0; x <= 1; x++) {
			for (int z = 0; z <= 1; z++) {
				for (int m1 = 0; m1 <= 1; m1++) {
					for (int m2 = 0; m2 <= 1; m2++) {
						string name = getQStateName(carry, x, z, m1, m2, m1);
						printSingleQReturn(carry, name);
					}
				}
			}
		}
	}
}

void AutomatonGenerator::printReturnTransitions() {
	cout << "returnTransitions = {\n";
	printQReturnTransitions();
	printSReturnTransitions();
	cout << "}\n);\n";
}

void AutomatonGenerator::printInternalTransitions() {
	cout << "internalTransitions = {\n";

	for (int carry = 0; carry <= maxCarry; carry++) {
		for (int x = 0; x <= 1; x++) {
			for (int z = 0; z <= 1; z++) {
				for (int m1 = 0; m1 <= 1; m1++) {
					for (int m2 = 0; m2 <= 1; m2++) {
						string name = getQStateName(carry, x, z, m1, m2, z);
						int bit = (carry + x + z) % 2;
						int newCarry = (carry + x +z) / 2;
						char inp = 'c' + bit;
						cout<<"("<<name<<" "<<inp<<" s"<<newCarry<<")\n";
					}
				}
			}
		}
	}

	cout << "},\n";
}

void AutomatonGenerator::printCallTransitions() {

	cout << "callTransitions = {\n";
	for (int carry = 0; carry <= maxCarry; carry++) {
		for (int x = 0; x <= 1; x++) {
			for (int z = 0; z <= 1; z++) {
				for (int m1 = 0; m1 <= 1; m1++) {
					for (int m2 = 0; m2 <= 1; m2++) {
						for (int m3 = 0; m3 <= 1; m3++) {
							string name = getQStateName(carry, x, z, m1, m2, m3);
							int bit = (carry + x + z) % 2;
							int newCarry = (carry + x +z) / 2;
							char inp = 'a' + bit;
							for (int x2 = 0; x2 <= 1; x2++) {
								for (int z2 = 0; z2 <= 1; z2++) {
									cout<<"("<<name<<" "<<inp<<" "<<getQStateName(newCarry, x2, z2, z, m1, m2)<<")\n";
								}
							}
						}
					}
				}
			}
		}
	}
	cout << "},\n";
}

void AutomatonGenerator::createStates () {
	cout << "states = { \n";
	for (int carry = 0; carry <= maxCarry; carry++) {
		for (int x = 0; x <= 1; x++) {
			for (int z = 0; z <= 1; z++) {
				for (int m1 = 0; m1 <= 1; m1++) {
					for (int m2 = 0; m2 <= 1; m2++) {
						for (int m3 = 0; m3 <= 1; m3++) {
							cout<<getQStateName(carry, x, z, m1, m2, m3)<<endl;

						}
					}
				}
			}
		}
	}
	for (int carry = 0; carry <= maxCarry; carry++) {
		cout<<"s"<<carry<<" ";
	}
	cout << "},\ninitialStates = {";
	cout << getQStateName(0, 1, 1, 0, 0, 0);
	cout<<"},\nfinalStates = {s0},\n";
}

void AutomatonGenerator::print() {
	cout << "NestedWordAutomaton "<<name<<" = (\n";
	cout << "callAlphabet = { a b },\ninternalAlphabet = { c d },\nreturnAlphabet = { e f },\n";
	createStates();
	printCallTransitions();
	printInternalTransitions();
	printReturnTransitions();
	cout << "print(numberOfStates("<<name<<"));\n";
}

int main() {
	AutomatonGenerator a ("1_0_1");
	a.print();
}