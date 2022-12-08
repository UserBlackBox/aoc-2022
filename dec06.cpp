#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>

using namespace std;

int main() {
	ifstream in;
	in.open("data/dec06");
	string line;
	getline(in, line);
	string ss;
	int pos = 0;
	unordered_set<char> letters;
	for (int i = 0; i < line.length()-4; i++) {
		letters.clear();
		ss = line.substr(i, 4);
		for (char c : ss)
			letters.insert(c);
		if (letters.size() == 4) {
			pos = i + 4;
			break;
		}
	}
	cout << pos << endl;
	pos = 0;
	for (int i = 0; i < line.length()-14; i++) {
		letters.clear();
		ss = line.substr(i, 14);
		for (char c: ss)
			letters.insert(c);
		if (letters.size() == 14) {
			pos = i + 14;
			break;
		}
	}
	cout << pos << endl;

	return 0;
}
