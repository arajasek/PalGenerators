#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

string printInt(int n) {
	double p = log10(n) / log10(2);
	int len = p + 1;
	if (len % 2 != 0)
		return "AAAAA";
	string str(len, 'f');
	for(int i = str.length() - 1; i >= 0; i--) {
		int x = n % 2;
		str.at(i) = '0' + x;
		n /= 2;
	}
	string output = "[";
	output += "a";
	output += str.at(0);
	output += " ";
	output += "a";
	output += str.at(1);
	output += " ";
	output += "a";
	output += str.at(2);
	output += " ";
	int i, j;

	output += "b";
	output += str.at(3);
	output += str.at(len - 1);
	output += " ";

	for (i = 4, j = len - 2; i < j; i++, j--) {
		output += "c";
		output += str.at(i);
		output += str.at(j);
		output += " ";
	}
	output += "a";
	output += str.at(len - 1);

	output += "]";
	return output;
}

bool cond1 (int i, int j, int n) {
	double logi = log10(i) / log10(2);
	double logj = log10(j) / log10(2);
	double logn = log10(n) / log10(2);
	int leni = logi + 1;
	int lenj = logj + 1;
	int lenn = logn + 1;
	if (n==160)
		cout << leni<<" "<<lenj<<" "<<lenn<<endl;
	if ((lenj == lenn) && (leni == (lenn - 3)))
		return true;
	return false;
}

int main() {
	// cout<<printInt(756);
	vector<bool> flags(1000);
	vector<int> v1 = {0, 1, 3, 5, 7, 9, 15, 17, 21, 27, 31, 33, 45, 51, 63, 65, 73, 85, 93, 99, 107, 119, 127, 129, 153, 165, 189, 195, 219, 231, 255, 257, 273, 297, 313, 325, 341, 365, 381, 387, 403, 427, 443, 455, 471, 495, 511, 513, 561, 585, 633, 645, 693, 717, 765, 771, 819, 843};
	for (int n= 65; n < 1000; n++) {
		if ((int)(log10(n) / log10(2)) % 2 != 1)
			continue;
		for (int i = 0; i < v1.size(); i++) {
			for (int j = i+1; j < v1.size(); j++) {
				if ((v1.at(i) + v1.at(j)) == n) {
					if (cond1(v1.at(i),v1.at(j),n))
						flags.at(n) = true;
				}
			}
		}
	}
	for (int n= 66; n < 1000; n+=2) {
		if ((int)(log10(n) / log10(2)) % 2 != 1)
			continue;
		if (flags.at(n) == false)
			cout << "assert(!accepts(finalAut, "<<printInt(n)<<"));\n";
		else
			cout << "assert(accepts(finalAut, "<<printInt(n)<<"));\n";
	}
}
