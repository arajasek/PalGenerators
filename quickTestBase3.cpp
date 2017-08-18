#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

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
	// cout << cond1(8, 23, 182, 213);
	vector<int> v1 = {1, 2, 4, 8, 10, 13, 16, 20, 23, 26, 28, 40, 52, 56, 68, 80, 82, 91, 100, 112, 121, 130, 142, 151, 160, 164, 173, 182, 194, 203, 212, 224, 233, 242, 244, 280, 316, 328, 364, 400, 412, 448, 484, 488, 524, 560, 572, 608, 644, 656, 692, 728, 730, 757};
	// cout <<endl<<v1.at(v1.size()-1)<<endl;
	for (int n= 100; n < 1000; n++) {
		for (int i = 0; i < v1.size(); i++) {
			for (int j = 0; j < v1.size(); j++) {
				for (int k = 0; k < v1.size(); k++) {
					if ((v1.at(i) + v1.at(j) + v1.at(k)) == n) {
						if (cond1(v1.at(i),v1.at(j),v1.at(k),n)) {
							if (n==216)
								cout<<v1.at(i)<<" "<<v1.at(j)<<" "<<v1.at(k)<<" "<<n<<endl;
							flags.at(n) = true;
						}
					}
				}
			}
		}
	}
	for (int n= 95; n < 1000; n++) {
		if (flags.at(n) == false)
			cout << n <<endl;
	}
}
