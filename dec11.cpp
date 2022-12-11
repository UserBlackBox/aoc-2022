#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Monkey {
	vector<unsigned long long int> items;
	int addition = 0;
	int multiplication = 1;
	bool square = false;
	int t_throw;
	int f_throw;
	int test = 1;
	unsigned long long int inspects = 0;
};

unsigned long long int process(int relief, int rounds) {
	ifstream in;
	in.open("data/dec11");
	string line;
	vector<string> lines;

	while (getline(in, line)) {
		if (line.length() != 0)
			lines.push_back(line);
	}

	vector<Monkey> monkeys;
	stringstream l;
	string s;

	for (int i = 0; i < lines.size(); i+=6) {
		monkeys.push_back(Monkey());
		Monkey *monkey = &monkeys[monkeys.size()-1];

		stringstream().swap(l);
		l << lines[i+1];
		l >> s;
		l >> s;
		while (!l.eof()) {
			l >> s;
			if (s.find_last_of(',') != string::npos)
				s = s.substr(0, s.size()-1);
			monkey->items.push_back(stoi(s));
			//cout << monkey->items[monkey->items.size()-1] << " ";
		}
		//cout << endl;

		s = lines[i+2];
		if (s.find_last_of('*') != string::npos) {
			if (s.substr(s.find_last_of(' ')+1) != "old")
				monkey->multiplication = stoi(s.substr(s.find_last_of(' ')));
			else
				monkey->square = true;
		}
		else
			monkey->addition = stoi(s.substr(s.find_last_of(' ')));
		s = lines[i+3];
		monkey->test = stoi(s.substr(s.find_last_of(' ')));
		s = lines[i+4];
		monkey->t_throw = stoi(s.substr(s.find_last_of(' ')));
		s = lines[i+5];
		monkey->f_throw = stoi(s.substr(s.find_last_of(' ')));
	}

	unsigned long long int prod = 1;
	for (Monkey m: monkeys)
		prod *= m.test;

	for (int i = 0; i < rounds; i++) {
		for (int m = 0; m < monkeys.size(); m++) {
			while (monkeys[m].items.size() > 0) {
				unsigned long long int item = monkeys[m].items[0];
				item *= monkeys[m].multiplication;
				item += monkeys[m].addition;
				if (monkeys[m].square)
					item *= item;
				item /= relief;
				if (!(item % monkeys[m].test))
					monkeys[monkeys[m].t_throw].items.push_back(item%prod);
				else
					monkeys[monkeys[m].f_throw].items.push_back(item%prod);
				monkeys[m].items.erase(monkeys[m].items.begin());
				monkeys[m].inspects ++;
			}
		}
	}

	unsigned long long int big1=0;
	unsigned long long int big2=0;

	for (Monkey m : monkeys) {
		//cout << m.inspects << endl;
		if (m.inspects > big1) {
			big2 = big1;
			big1 = m.inspects;
		}
		else if (m.inspects > big2) {
			big2 = m.inspects;
		}
	}
	in.close();

	return big1*big2;
}

int main() {
	cout << process(3, 20) << endl;
	cout << process(1, 10000) << endl;
}
