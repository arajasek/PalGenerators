#include <iostream>
#include <vector>
using namespace std;

int main() {

	vector<int> v1 = {0, 1, 3, 5, 7, 9, 15, 17, 21, 27, 31, 33, 45, 51, 63, 65, 73, 85, 93, 99, 107, 119, 127, 129};


	for (int i = 0; i < v1.size(); i++) {
		for (int j = i+1; j < v1.size(); j++) {
			for (int k = j+1; k < v1.size(); k++) {
				if (v1.at(i) + v1.at(j) + v1.at(k) == 235) {
					cout<<v1.at(i)<<" "<<v1.at(j)<<" "<<v1.at(k)<<endl;
				}
			}
		}
	}
}
