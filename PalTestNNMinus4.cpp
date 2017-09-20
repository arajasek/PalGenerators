/*

This program generates the automaton for 

1 length n,
1 length n-4

*/

#include <iostream>
#include <string> 

using namespace std;

//Q States are 7-tuples (carry, x,y, m1, m2, m3, m4)
// a carry
// x, the next length-n guess
// y, the next n-4 guess
// m1, m2, m3 and m4 are the four previous n-4 guesses

class AutomatonGenerator {
private:
	string name;
	int maxCarry;
	string getQStateName(int carry, int x, int y, int m1, int m2, int m3, int m4);
	void createStates();
	void printCallTransitions();
	void printReturnTransitions();
	void printQReturnTransitions();
	void printSReturnTransitions();
	void printSingleQReturn(int, string);
	void printInternalTransitions();
public:
	AutomatonGenerator();
	void print();

};

AutomatonGenerator::AutomatonGenerator() {
	name = "palChecker";
	maxCarry = 1;
}

string AutomatonGenerator::getQStateName(int carry, int x, int y, int m1, int m2, int m3, int m4) {
	return ("q_"+to_string(carry)+"_"+to_string(x)+to_string(y)+"_"
		+to_string(m1)+to_string(m2)+to_string(m3)+to_string(m4));
}

void AutomatonGenerator::printSReturnTransitions() {
	for (int stateCarry = 0; stateCarry <= maxCarry; stateCarry++) {
		string currName = "s"+to_string(stateCarry);
		for (int carry = 0; carry <= maxCarry; carry++) {
			for (int x = 0; x <= 1; x++) {
				for (int y = 0; y <= 1; y++) {
					for (int m1 = 0; m1 <= 1; m1++) {
						for (int m2 = 0; m2 <= 1; m2++) {
							for (int m3 = 0; m3 <= 1; m3++) {
								for (int m4 = 0; m4 <= 1; m4++) {
									string topName = getQStateName(carry, x, y, m1, m2, m3, m4);
									int bit = (stateCarry + x + m4) % 2;
									int newCarry = (stateCarry + x + m4) / 2;
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
}

void AutomatonGenerator::printSingleQReturn(int c, string currName) {
	for (int carry = 0; carry <= maxCarry; carry++) {
		for (int x = 0; x <= 1; x++) {
			for (int y = 0; y <= 1; y++) {
				for (int m1 = 0; m1 <= 1; m1++) {
					for (int m2 = 0; m2 <= 1; m2++) {
						for (int m3 = 0; m3 <= 1; m3++) {
							for (int m4 = 0; m4 <= 1; m4++) {
								string topName = getQStateName(carry, x, y, m1, m2, m3, m4);
								int bit = (c + x + m4) % 2;
								int newCarry = (c + x + m4) / 2;
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

void AutomatonGenerator::printQReturnTransitions() {
	for (int carry = 0; carry <= maxCarry; carry++) {
		for (int x = 0; x <= 1; x++) {
			for (int y = 0; y <= 1; y++) {
				for (int m1 = 0; m1 <= 1; m1++) {
					for (int m2 = 0; m2 <= 1; m2++) {
						string name = getQStateName(carry, x, y, m1, m2, m2, m1);
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
			for (int y = 0; y <= 1; y++) {
				for (int m1 = 0; m1 <= 1; m1++) {
					for (int m2 = 0; m2 <= 1; m2++) {
						string name = getQStateName(carry, x, y, m1, m2, m1, y);
						int bit = (carry + x + y) % 2;
						int newCarry = (carry + x + y) / 2;
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
			for (int y = 0; y <= 1; y++) {
				for (int m1 = 0; m1 <= 1; m1++) {
					for (int m2 = 0; m2 <= 1; m2++) {
						for (int m3 = 0; m3 <= 1; m3++) {
							for (int m4 = 0; m4 <= 1; m4++) {
								string name = getQStateName(carry, x, y, m1, m2, m3, m4);
								int bit = (carry + x + y) % 2;
								int newCarry = (carry + x + y) / 2;
								char inp = 'a' + bit;
								for (int x2 = 0; x2 <= 1; x2++) {
									for (int y2 = 0; y2 <= 1; y2++) {
										cout<<"("<<name<<" "<<inp<<" "<<getQStateName(newCarry, x2, y2, y, m1, m2, m3)<<")\n";
									}
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
			for (int y = 0; y <= 1; y++) {
				for (int m1 = 0; m1 <= 1; m1++) {
					for (int m2 = 0; m2 <= 1; m2++) {
						for (int m3 = 0; m3 <= 1; m3++) {
							for (int m4 = 0; m4 <= 1; m4++) {
								cout<<getQStateName(carry, x, y, m1, m2, m3, m4)<<endl;
							}
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
	cout << getQStateName(0, 1, 1, 0, 0, 0, 0);
	cout<<"},\nfinalStates = {s0},\n";
}

void AutomatonGenerator::print() {
	cout << "NestedWordAutomaton "<<name<<" = (\n";
	cout << "callAlphabet = { a b },\ninternalAlphabet = { c d },\nreturnAlphabet = { e f },\n";
	createStates();
	printCallTransitions();
	printInternalTransitions();
	printReturnTransitions();
}

int main() {
	AutomatonGenerator a;
	a.print();
}