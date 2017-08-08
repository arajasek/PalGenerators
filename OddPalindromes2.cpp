/*

Every length-n ODD integer, n >= 8, is either represented by

(a) sum of at most 1 palindrome each of lengths n-1, n-2, n-3
(b) sum of at most 1 palindrome each of lengths n, n-2, n-3

This program generates the automaton for 

1 length n,
1 length n-2
0 length n-3

*/

#include <iostream>
#include <string> 

using namespace std;

//Q States are 5-tuples (carry, x,y, l1,l2)
// a carry
// x, the next length-n guess
// y, the next n-2 guess
// l1 and l2 are the two previous n-2 guesses

class AutomatonGenerator {
private:
	string name;
	int maxCarry;
	string getQStateName(int carry, int x, int y, int l1, int l2);
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
	maxCarry = 1;
}

string AutomatonGenerator::getQStateName(int carry, int x, int y, int l1, int l2) {
	return ("q_"+to_string(carry)+"_"+to_string(x)+to_string(y)+"_"
		+to_string(l1)+to_string(l2));
}

void AutomatonGenerator::printSReturnTransitions() {
	for (int stateCarry = 0; stateCarry < maxCarry; stateCarry++) {
		string currName = "s"+to_string(stateCarry);
		for (int carry = 0; carry <= maxCarry; carry++) {
			for (int x = 0; x <= 1; x++) {
				for (int y = 0; y <= 1; y++) {
					for (int l1 = 0; l1 <= 1; l1++) {
						for (int l2 = 0; l2 <= 1; l2++) {
							string topName = getQStateName(carry, x, y, l1, l2);
							int bit = (stateCarry + x + l2) % 2;
							int newCarry = (stateCarry + x + l2) / 2;
							char inp = 'e' + bit;
							cout<<"("<<currName<<" "<<topName<<" "<<inp<<" "<<"s"<<newCarry<<")\n";
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
				for (int l1 = 0; l1 <= 1; l1++) {
					for (int l2 = 0; l2 <= 1; l2++) {
						string topName = getQStateName(carry, x, y, l1, l2);
						int bit = (c + x + l2) % 2;
						int newCarry = (c + x + l2) / 2;
						char inp = 'e' + bit;
						cout<<"("<<currName<<" "<<topName<<" "<<inp<<" "<<"s"<<newCarry<<")\n";
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
				for (int l1 = 0; l1 <= 1; l1++) {
					string name = getQStateName(carry, x, y, l1, l1);
					printSingleQReturn(carry, name);
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
				for (int l1 = 0; l1 <= 1; l1++) {
					string name = getQStateName(carry, x, y, l1, y);
					int bit = (carry + x + y) % 2;
					int newCarry = (carry + x + y) / 2;
					char inp = 'c' + bit;
					cout<<"("<<name<<" "<<inp<<" s"<<newCarry<<")\n";
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
				for (int l1 = 0; l1 <= 1; l1++) {
					for (int l2 = 0; l2 <= 1; l2++) {
						string name = getQStateName(carry, x, y, l1, l2);
						int bit = (carry + x + y) % 2;
						int newCarry = (carry + x + y) / 2;
						char inp = 'a' + bit;
						for (int x2 = 0; x2 <= 1; x2++) {
							for (int y2 = 0; y2 <= 1; y2++) {
								cout<<"("<<name<<" "<<inp<<" "<<getQStateName(newCarry, x2, y2, y, l1)<<")\n";
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
					for (int l1 = 0; l1 <= 1; l1++) {
						for (int l2 = 0; l2 <= 1; l2++) {
										cout<<getQStateName(carry, x, y, l1, l2)<<endl;
					}
				}
			}
		}
	}
	for (int carry = 0; carry <= maxCarry; carry++) {
		cout<<"s"<<carry<<" ";
	}
	cout << "},\ninitialStates = {";
	cout << getQStateName(0, 1, 1, 0, 0);
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
	cout << "finalAut = intersect(finalAut, complement("<<name<<"));\n";
}

int main() {
	AutomatonGenerator a ("1_0_1_0");
	a.print();
}