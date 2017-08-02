#include <iostream>
#include <vector>
using namespace std;

int main() {

	vector<int> v1 = {257, 273, 297, 313, 325, 341, 365, 381, 387, 403, 427, 443, 455, 471, 495, 511};

	for (int i = 0; i < v1.size(); i++) {
		for (int j = 0; j < v1.size(); j++) {
			for (int k = 0; k < v1.size(); k++) {
				for (int l = 0; l < v1.size(); l++) {
					for (int m = 0; m < v1.size(); m++) {
						for (int n = 0; n < v1.size(); n++) {
							for (int o = 0; o < v1.size(); o++) {
								if (v1.at(i) + v1.at(j) + v1.at(k) + v1.at(l) + v1.at(m) + v1.at(n) + v1.at(o) == 2189)
									cout<<v1.at(i)<<" "<<v1.at(j)<<" "<<v1.at(k)<<" "<<v1.at(l)<<" "<<v1.at(m)<<" "<<v1.at(n)<<" "<<v1.at(o)<<endl;
							}
						}
					}
				}
			}
		}
	}
}