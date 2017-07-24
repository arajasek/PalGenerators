// This generates the script to prove
//For all n >= 6 with n even, every n-bit integer is the sum of at most
//10 binary palindromes of length exactly n-3.

#include <iostream>
#include <string> 
#include <vector>
#include <utility>

using namespace std;

string getAutomatonName(int i) {
	return("palChecker"+to_string(i));
}

// states are 2-tuples (c1,c2) where 
// c1 is the upper carry that needs to be produced
// c2 is the lower carry
string getStateName(int c1, int c2) {
	return ("q_"+to_string(c1)+"_"+to_string(c2));
}

void createStates(int palNumber) {
	cout << "states = { q\n";
	for(int i = 0; i < palNumber; i++)
		for (int j = 0; j < palNumber; j++)
			cout<<getStateName(i,j) <<endl;
	cout<<"r r1 r10 r11 r100 r101 r110 r111 acc},\n";
}

void addMiddleTransitions(int palNumber, int c1, int c2) {
	for(int i = 0; i <= palNumber; i++) {
		for (int newc1 = 0; newc1 < palNumber; newc1++) {		
				int lowerBit = (i+c2) % 2;
				int higherBit = (newc1 + i) % 2;
				int lowerCarry = (i+c2) / 2;
				int higherCarry = (newc1 + i ) / 2;
				if (higherCarry != c1)
					continue;
				cout << "("<<getStateName(c1, c2)<<" a" << higherBit << lowerBit << " " << getStateName(newc1, lowerCarry)<<")\n";
		}
	}
}

void addFinalTransitions(int palNumber, int c1, int c2) {
	for(int i = 0; i <= palNumber; i++) {
			int bit = (i+c2) % 2;
			int carry = (i+c2) / 2;
			if (carry != c1)
				continue;
			char letter = 'c' + bit;
			cout << "("<<getStateName(c1, c2) << " "<< letter <<" acc)\n";
	}
}

void addInitialTransitions(int palNumber) {
	cout<<"(r d r1) \n (r1 d r11) \n (r1 c r10)\n";
	cout<<"(r10 c r100) \n (r10 d r101) \n (r11 c r110) \n (r11 d r111) \n";
	for (int incomingCarry = 0; incomingCarry < palNumber; incomingCarry++) {
		int lowerBit = palNumber % 2;
		int higherBit = (palNumber + incomingCarry) % 2;
		int lowerCarry = palNumber / 2;
		int higherCarry = (palNumber + incomingCarry) / 2;
		switch (higherCarry) {
			case 4:
			cout << "(r100 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
			break;
			case 5:
			cout << "(r101 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
			break;
			case 6:
			cout << "(r110 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
			break;
			case 7:
			cout << "(r111 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
			break;
		}
	}
}

void addAllTransitions(int palNumber) {

	addInitialTransitions(palNumber);

	for(int i = 0; i < palNumber; i++) {
		for (int j = 0; j < palNumber; j++)
			addMiddleTransitions(palNumber, i,j);
	}

	for(int i = 0; i < palNumber; i++) {
		for (int j = 0; j < palNumber; j++)
			addFinalTransitions(palNumber, i,j);
	}
}

void createAutomaton (int palNumber) {
	cout << "FiniteAutomaton "<<getAutomatonName(palNumber)<<" = (\n";
	cout << "alphabet = {a00 a01 a10 a11 c d},";
	createStates(palNumber);
	cout << "initialStates = {r},\nfinalStates = {acc},\n";
	cout << "transitions = {\n";
	addAllTransitions(palNumber);
	cout << "\n}\n";
	cout << ");\n";
}

int main() {
	vector<string> autNames;
	int palNumberMax = 10;
	for (int i = 1; i <= palNumberMax; i++) {
		createAutomaton(i);
		autNames.push_back(getAutomatonName(i));
	}
	cout<<endl<<endl<<"FiniteAutomaton finalAut = Intersect(Complement("<<autNames.at(0)<<"), Complement("<<autNames.at(1)<<"));\n";
	for(int i = 2; i < autNames.size(); i++)
		cout<<"finalAut = Intersect(finalAut, Complement("<<autNames.at(i)<<"));\n";
	cout<<"finalAut = removeUnreachable(Complement(finalAut));";
}



