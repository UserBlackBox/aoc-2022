#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
	ifstream in;
	in.open("data/dec04");
	string line;
	int elf1begin, elf1end, elf2begin, elf2end;
	int enclose = 0;
	int overlap = 0;

	while (getline(in, line)) {
		elf1begin = stoi(line.substr(
					0,
					line.find_first_of('-')
					));
		elf1end = stoi(line.substr(
					line.find_first_of('-')+1,
					line.find_first_of(',')-1-line.find_first_of('-')
					));
		elf2begin = stoi(line.substr(
					line.find_first_of(',')+1,
					line.find_last_of('-')-1-line.find_first_of(',')
					));
		elf2end = stoi(line.substr(line.find_last_of('-')+1));

		if (elf1end <= elf2end && elf1begin >= elf2begin) {
			enclose += 1;
			overlap += 1;
		}
		else if (elf2end <= elf1end && elf2begin >= elf1begin) {
			enclose += 1;
			overlap += 1;
		}
		else if (elf1begin <= elf2begin && elf1end >= elf2begin)
			overlap += 1;
		else if (elf2begin <= elf1begin && elf2end >= elf1begin)
			overlap += 1;
	}

	cout << enclose << endl;
	cout << overlap << endl;
	return 0;
}
