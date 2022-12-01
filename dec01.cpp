#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

const int DATAFILE_LENGTH = 2253;

int main() {
	ifstream in;
	in.open("data/dec01");
	int largest = 0 ;
	int current = 0;
	string line;
	vector<int> elves;

	while (getline(in, line)) {
		if (line.length() != 0) {
			current += stoi(line);
		} else {
			if (current > largest) {
				largest = current;
			}
			elves.push_back(current);
			current = 0;
		}
	}
	if (current > largest) {
		largest = current;
	}
	elves.push_back(current);
	sort(elves.begin(), elves.end(), greater<int>());

	cout << largest << endl;
	cout << elves[0] + elves[1] + elves[2] << endl;
	return 0;
}
