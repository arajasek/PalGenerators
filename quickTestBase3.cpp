#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

string printInt(int n) {
	double p = log10(n) / log10(3);
	int len = p + 1;
	string str(len, 'f');
	for(int i = str.length() - 1; i >= 0; i--) {
		int x = n % 3;
		str.at(i) = '0' + x;
		n /= 3;
	}
	string output = "[";
	output += "a";
	output += str.at(0);
	output += " ";
	output += "b";
	output += str.at(1);
	output += " ";
	output += "c";
	output += str.at(2);
	output += str.at(len - 1);
	output += " ";
	int i, j;
	for (i = 3, j = len - 2; i < j; i++, j--) {
		output += "d";
		output += str.at(i);
		output += str.at(j);
		output += " ";
	}
	if (i == j) {
		output += "e";
		output += str.at(i);
		output += " ";
	}

	output.at(output.length() - 1) =  ']';
	return output;
}

bool cond1 (int i, int j, int k, int n) {
	double logi = log10(i) / log10(3);
	double logj = log10(j) / log10(3);
	double logk = log10(k) / log10(3);	
	double logn = log10(n) / log10(3);
	int leni = logi + 1;
	int lenj = logj + 1;
	int lenk = logk + 1;
	int lenn = logn + 1;
	// cout << leni<<" "<<lenj<<" "<<lenk<<" "<<lenn<<endl;
	if ((lenk == lenn) && (lenj == (lenn -2)) && (leni == (lenn - 3)))
		return true;
	if ((lenk == (lenn -1)) && (lenj == (lenn -2)) && (leni == (lenn - 3)))
		return true;
	if ((lenk == lenn) && (lenj == (lenn -1)) && (leni == (lenn - 2)))
		return true;
	return false;
}

int main() {
	vector<bool> flags(1000);
	vector<int> v1 = {1, 2, 4, 8, 10, 13, 16, 20, 23, 26, 28, 40, 52, 56, 68, 80, 82, 91, 100, 112, 121, 130, 142, 151, 160, 164, 173, 182, 194, 203, 212, 224, 233, 242, 244, 280, 316, 328, 364, 400, 412, 448, 484, 488, 524, 560, 572, 608, 644, 656, 692, 728, 730, 757};
	for (int n= 243; n < 1000; n++) {
		for (int i = 0; i < v1.size(); i++) {
			for (int j = 0; j < v1.size(); j++) {
				for (int k = 0; k < v1.size(); k++) {
					if ((v1.at(i) + v1.at(j) + v1.at(k)) == n) {
						if (cond1(v1.at(i),v1.at(j),v1.at(k),n)) {
							if (n==735)
								cout <<"// " <<i<<" "<<j<<" "<<k<<endl;
							flags.at(n) = true;
						}
					}
				}
			}
		}
	}
	for (int n= 243; n < 1000; n++) {
		if (flags.at(n) == false)
			cout << "assert(!accepts(finalAut, "<<printInt(n)<<"));\n";
		else
			cout << "assert(accepts(finalAut, "<<printInt(n)<<"));\n";
	}
}
