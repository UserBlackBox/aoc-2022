#include <iostream>
#include <fstream>
#include <unordered_set>
#include <utility>
#include <cmath>

using namespace std;

struct hashFunction {
	size_t operator() (const pair<int, int> &x) const {
		return x.first ^ x.second;
	}
};

int main() {
	ifstream in;
	//in.open("data/dec09.test");
	in.open("data/dec09");
	string line;

	int head_x = 0;
	int head_y = 0;
	int tail_x = 0;
	int tail_y = 0;

	unordered_set<pair<int, int>, hashFunction> tail_visited;
	tail_visited.clear();

	char direction;
	int magnitude;

	while (getline(in, line)) {
		direction = line.at(0);
		magnitude = stoi(line.substr(line.find_first_of(" ")));
		tail_visited.insert(pair<int, int>(tail_x, tail_y));

		for (int i = 0; i < magnitude; i++) {
			if (direction == 'U')
				head_y++;
			else if (direction == 'D')
				head_y--;
			else if (direction == 'R')
				head_x++;
			else if (direction == 'L')
				head_x--;

			if (abs(head_x-tail_x)==2 || abs(head_y-tail_y)==2) {
				if (abs(head_x - tail_x) == 2)
					tail_x = (head_x + tail_x)/2.0;
				else
					tail_x = head_x;

				if (abs(head_y - tail_y) == 2)
					tail_y = (head_y + tail_y)/2.0;
				else
					tail_y = head_y;
			}
			//cout << head_x << "," << head_y << " " << tail_x << "," << tail_y << endl;
			tail_visited.insert(pair<int, int>(tail_x, tail_y));
		}
	}

	cout << tail_visited.size() << endl;
	in.close();

	head_x = 0;
	head_y = 0;
	pair<int, int> knots[9];
	for (int i = 0; i < 9; i++) {
		knots[i].first = 0;
		knots[i].second = 0;
	}
	in.open("data/dec09");
	tail_visited.clear();

	while(getline(in, line)) {
		direction = line.at(0);
		magnitude = stoi(line.substr(line.find_first_of(' ')));
		tail_visited.insert(pair<int, int>(knots[8].first, knots[8].second));

		for (int i = 0; i < magnitude; i++) {
			if (direction == 'U')
				head_y++;
			else if (direction == 'D')
				head_y--;
			else if (direction == 'R')
				head_x++;
			else if (direction == 'L')
				head_x--;

			int *prev_x = &head_x;
			int *prev_y = &head_y;

			for (int knot = 0; knot < 9; knot++) {
				if (abs(*prev_x - knots[knot].first)==2 || abs(*prev_y-knots[knot].second)==2) {
					if (abs(*prev_x - knots[knot].first)==2)
						knots[knot].first = (knots[knot].first + *prev_x)/2.0;
					else
						knots[knot].first = *prev_x;

					if (abs(*prev_y - knots[knot].second) == 2)
						knots[knot].second = (knots[knot].second + *prev_y)/2.0;
					else
						knots[knot].second = *prev_y;
				}
				prev_x = &knots[knot].first;
				prev_y = &knots[knot].second;
			}
			tail_visited.insert(pair<int, int>(knots[8].first, knots[8].second));
		}
	}
	cout << tail_visited.size() << endl;
	in.close();

	return 0;
}
