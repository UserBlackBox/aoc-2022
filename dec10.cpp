#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
	ifstream in;
	in.open("data/dec10");
	string line;
	stringstream ss;
	string command;

	int reg = 1;
	int cycle = 1;
	int strengths = 0;
	int increment = 0;

	while (getline(in, line)) {
		stringstream().swap(ss);
		increment = 0;
		ss << line;
		ss >> command;
		if (command == "addx") {
			ss >> increment;
		}

		if ((cycle-1)%40 == 0)
			cout << endl;
		if (reg-1 <= (cycle-1)%40 && reg+1 >= (cycle-1)%40) {
			cout << "#";
		} else {
			cout << ".";
		}

		if ((cycle-20)%40 == 0) {
			strengths += cycle * reg;
			//cout << cycle << " " << reg << " " << strengths << endl;
		}
		cycle ++;

		if (command == "addx") {
			if ((cycle-20)%40 == 0) {
				strengths += cycle * reg;
				//cout << cycle << " " << reg << " " << strengths << endl;
			}

			if ((cycle-1)%40 == 0)
				cout << endl;
			if (reg-1 <= (cycle-1)%40 && reg+1 >= (cycle-1)%40) {
				cout << "#";
			} else {
				cout << ".";
			}

			reg += increment;
			cycle ++;
		}
	}
	in.close();
	cout << endl << strengths << endl;

	return 0;
}
