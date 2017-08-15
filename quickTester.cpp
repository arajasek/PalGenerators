#include <iostream>
#include <vector>
using namespace std;

int main() {

	vector<int> v1 = {0, 1, 3, 5, 7, 9, 15, 17, 21, 27, 31, 33, 45, 51, 63, 65, 73, 85, 93, 99, 107, 119, 127, 129};


	for (int i = 0; i < v1.size(); i++) {
		for (int j = 0; j < v1.size(); j++) {
			for (int k = 0; k < v1.size(); k++) {
				for (int l = 0; l < v1.size(); l++) {
					for (int m = 0; m < v1.size(); m++) {
						for (int n = 0; n < v1.size(); n++) {
							for (int o = 0; o < v1.size(); o++) {
								if (v1.at(i) + v1.at(j) + v1.at(k) + v1.at(l) + v1.at(m) + v1.at(n) + v1.at(o) == 235)
									cout<<v1.at(i)<<" "<<v1.at(j)<<" "<<v1.at(k)<<" "<<v1.at(l)<<" "<<v1.at(m)<<" "<<v1.at(n)<<" "<<v1.at(o)<<endl;
							}
						}
					}
				}
			}
		}
	}
}