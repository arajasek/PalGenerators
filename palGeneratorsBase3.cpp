// This generates the script to prove
//For all n >= 8 with n even, every n-bit integer is the sum of at most
//28 binary palindromes of length exactly n-3.


	// 100 9
	// 101 10
	// 102 11
	// 110 12
	// 111 13
	// 112 14
	// 120 15
	// 121 16
	// 122 17
	// 200 18
	// 201 19
	// 202 20
	// 210 21
	// 211 22
	// 212 23
	// 220 24
	// 221 25
	// 222 26

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
	cout<<"r r1 r2 r10 r11 r12 r20 r21 r22 r100 r101 r102 r110 r111 r112 r120 r121 r122 \n";
	cout <<"r200 r201 r202 r210 r211 r212 r220 r221 r222 acc},\n";
}

void addMiddleTransitions(int palNumber, int c1, int c2) {
	for(int i = 0; i <= palNumber*2; i++) {
		for (int newc1 = 0; newc1 < palNumber; newc1++) {		
				int lowerBit = (i+c2) % 3;
				int higherBit = (newc1 + i) % 3;
				int lowerCarry = (i+c2) / 3;
				int higherCarry = (newc1 + i ) / 3;
				if (higherCarry != c1)
					continue;
				cout << "("<<getStateName(c1, c2)<<" a" << higherBit << lowerBit << " " << getStateName(newc1, lowerCarry)<<")\n";
		}
	}
}

void addFinalTransitions(int palNumber, int c1, int c2) {
	for(int i = 0; i <= palNumber*2; i++) {
			int bit = (i+c2) % 3;
			int carry = (i+c2) / 3;
			if (carry != c1)
				continue;
			char letter = 'c' + bit;
			cout << "("<<getStateName(c1, c2) << " "<< letter <<" acc)\n";
	}
}

void addInitialTransitions(int palNumber) {
	cout<<"(r d r1) \n (r e r2) \n (r1 d r11) \n (r1 c r10)\n";
	cout<<"(r1 e r12) \n (r2 c r20) \n (r2 d r21) \n (r2 e r22) \n";

	cout<<"(r10 c r100) \n (r10 d r101) \n (r10 e r102) \n (r11 c r110) \n (r11 d r111) \n (r11 e r112) \n";
	cout<<"(r12 c r120) \n (r12 d r121) \n (r12 e r122) \n";

	cout<<"(r20 c r200) \n (r20 d r201) \n (r20 e r202) \n (r21 c r210) \n (r21 d r211) \n (r21 e r212) \n";
	cout<<"(r22 c r220) \n (r22 d r221) \n (r22 e r222) \n";

	for (int incomingCarry = 0; incomingCarry < palNumber; incomingCarry++) {
		for (int palsUsed = palNumber; palsUsed <= palNumber*2; palsUsed++) {
			int lowerBit = palsUsed % 3;
			int higherBit = (palsUsed + incomingCarry) % 3;
			int lowerCarry = palsUsed / 3;
			int higherCarry = (palsUsed + incomingCarry) / 3;
			switch (higherCarry) {
				case 9:
				cout << "(r100 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
				break;
				case 10:
				cout << "(r101 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
				break;
				case 11:
				cout << "(r102 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
				break;
				case 12:
				cout << "(r110 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
				break;
				case 13:
				cout << "(r111 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
				break;
				case 14:
				cout << "(r112 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
				break;
				case 15:
				cout << "(r120 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
				break;
				case 16:
				cout << "(r121 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
				break;
				case 17:
				cout << "(r122 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
				break;
				case 18:
				cout << "(r200 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
				break;
				case 19:
				cout << "(r201 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
				break;
				case 20:
				cout << "(r202 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
				break;
				case 21:
				cout << "(r210 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
				break;
				case 22:
				cout << "(r211 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
				break;
				case 23:
				cout << "(r212 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
				break;
				case 24:
				cout << "(r220 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
				break;
				case 25:
				cout << "(r221 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
				break;
				case 26:
				cout << "(r222 a" << higherBit << lowerBit << " " << getStateName(incomingCarry, lowerCarry)<<")\n";
				break;
			}
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
	cout << "alphabet = {a00 a01 a02 a10 a11 a12 a20 a21 a22 c d e},\n";
	createStates(palNumber);
	cout << "initialStates = {r},\nfinalStates = {acc},\n";
	cout << "transitions = {\n";
	addAllTransitions(palNumber);
	cout << "\n}\n";
	cout << ");\n";
}

int main() {
	vector<string> autNames;
	int palNumberMax = 28;
	for (int i = 1; i <= palNumberMax; i++) {
		createAutomaton(i);
		autNames.push_back(getAutomatonName(i));
	}
	cout<<endl<<endl<<"FiniteAutomaton finalAut = intersect(complement("<<autNames.at(0)<<"), complement("<<autNames.at(1)<<"));\n";
	for(int i = 2; i < autNames.size(); i++) {
		cout<<"finalAut = removeUnreachable(finalAut);\n";
		cout<<"finalAut = intersect(finalAut, complement("<<autNames.at(i)<<"));\n";
	}
	cout<<"finalAut = removeUnreachable(complement(finalAut));\n\n\n";
	cout<<"// print(getAcceptedWord(difference(syntaxChecker, finalAut)));\n";
	cout<<"assert(isIncluded(syntaxChecker, finalAut));\n\n\n\n";
}



