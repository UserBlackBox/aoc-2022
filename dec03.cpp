#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

int calc_priority(char c) {
	if (c >= 97 && c <= 122)
		return c - 96;
	else
		return c - 64 + 26;
}

int main() {
	ifstream in;
	in.open("data/dec03");
	string line;
	int priorities = 0;
	int badge_priorities = 0;
	unordered_set<char> pocket1;
	unordered_set<char> pocket2;
	char item;
	unordered_set<char> elf1;
	unordered_set<char> elf2;
	unordered_set<char> elf3;
	int elf_counter = 0;

	while (getline(in, line)) {
		pocket1.clear();
		pocket2.clear();

		for (int i = 0; i < line.length()/2; i++) {
			item = line.at(i);
			pocket1.insert(item);
		}
		for (int i = 0; i < line.length()/2; i++) {
			item = line.at(i + line.size()/2);
			pocket2.insert(item);
		}
		for (int i = 0; i < line.length(); i++) {
			item = line.at(i);
			if (elf_counter == 0)
				elf1.insert(item);
			else if (elf_counter == 1)
				elf2.insert(item);
			else
				elf3.insert(item);
		}

		for (char item : pocket2) {
			if (pocket1.find(item) != pocket1.end()) {
				priorities += calc_priority(item);
			}
		}

		elf_counter += 1;
		elf_counter %= 3;
		if (elf_counter == 0) {
			for (char item : elf1) {
				if (elf2.find(item) != elf2.end() && elf3.find(item) != elf3.end())
					badge_priorities += calc_priority(item);
			}
			elf1.clear();
			elf2.clear();
			elf3.clear();
		}
	}
	cout << priorities << endl;
	cout << badge_priorities << endl;

	return 0;
}
