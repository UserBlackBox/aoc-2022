#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

const int STACKS = 9;

int main() {
	ifstream in;
	in.open("data/dec05");
	string line;

	stack<char> crates[STACKS];
	stack<char> crates2[STACKS];

	while (getline(in, line) && line.find('[') != string::npos) {
		for (int i = 0; i < STACKS; i++) {
			if (line.at(1+4*i) != ' ')
				crates[i].push(line.at(1+4*i));
		}
	}

	for (int i = 0; i < STACKS; i++) {
		stack<char> temp = stack<char>(crates[i]);
		while (!crates[i].empty())
			crates[i].pop();
		while (!temp.empty()) {
			crates[i].push(temp.top());
			crates2[i].push(temp.top());
			temp.pop();
		}
	}

	getline(in, line);

	stringstream ss;
	int numMoved, dest, source;
	string word;
	vector<string> words;
	vector<char> moveStack;

	while (getline(in, line)) {
		stringstream().swap(ss);
		ss << line;
		words.clear();
		moveStack.clear();
		while(!ss.eof()) {
			ss >> word;
			words.push_back(word);
		}
		numMoved = stoi(words[1]);
		dest = stoi(words[5]);
		source = stoi(words[3]);

		for (int i = 0; i < numMoved; i++){
			crates[dest-1].push(crates[source-1].top());
			crates[source-1].pop();

			moveStack.push_back(crates2[source-1].top());
			crates2[source-1].pop();
		}
		for (int i = moveStack.size()-1; i >= 0; i--)
			crates2[dest-1].push(moveStack[i]);
	}
	for (int i = 0; i < STACKS; i++)
		cout << crates[i].top();
	cout << endl;
	for (int i = 0; i < STACKS; i++)
		cout << crates2[i].top();
	cout << endl;

	return 0;
}
