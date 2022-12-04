#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main() {
	ifstream in;
	in.open("data/dec02");
	string line;
	char opponent;
	char yourhand;
	char yourhand2;
	int score = 0;
	int score2 = 0;
	while (getline(in, line)) {
		if (line.substr(0, 1) == "A") {
			opponent = 1;
		} else if (line.substr(0, 1) == "B") {
			opponent = 2;
		} else {
			opponent = 3;
		}

		if (line.substr(2, 1) == "X") {
			yourhand = 1;
			yourhand2 = (opponent + 2) % 3;
		} else if (line.substr(2, 1) == "Y") {
			yourhand = 2;
			yourhand2 = opponent;
			score2 += 3;
		} else {
			yourhand = 3;
			yourhand2 = (opponent + 1) % 3;
			score2 += 6;
		}

		if (yourhand2 == 0) yourhand2 += 3;

		if (yourhand == opponent + 1 || (yourhand == 1 && opponent == 3)) {
			score += 6;
		} else if (yourhand == opponent) {
			score += 3;
		}
		score += yourhand;
		score2 += yourhand2;

	}

	cout << score << endl;
	cout << score2 << endl;

	in.close();
	return 0;
}
