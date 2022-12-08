#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Node {
	public:
		Node(string name, unsigned int fileSize) {
			size = fileSize;
			fileName = name;
		}
		Node(string name, bool dir) {
			isDirectory = dir;
			fileName = name;
		}

		void insertFile(Node file) {
			files.push_back(file);
		}

		unsigned int calcFileSize() {
			if (!isDirectory)
				return size;
			else {
				size = 0;
				for (Node i : files)
					size += i.calcFileSize();
				//cout << size << endl;
				return size;
			}
		}

		unsigned int getSize() const {
			return size;
		}

		vector<Node*> grabDirs() {
			vector<Node*> dirs;
			for (Node n : files) {
				if (n.isDirectory) {
					dirs.push_back(&n);
					for (Node* n1 : n.grabDirs())
						dirs.push_back(n1);
				}
			}
			return dirs;
		}

		vector<Node> files;
		string fileName;
		bool isDirectory = false;
	private:
		unsigned int size = 0;
};

int main() {
	ifstream in;
	in.open("data/dec07");
	string line;
	vector<string> path;
	path.clear();
	char mode;
	string word;
	vector<string> words;
	stringstream ss;
	vector<Node> root;
	Node *dir;
	vector <string> *subPath;

	while (getline(in, line)) {
		stringstream().swap(ss);
		ss << line;
		words.clear();
		while (!ss.eof()) {
			ss >> word;
			words.push_back(word);
		}

		if (line.at(0) == '$') {
			if(words[1] == "cd"){
				mode = 'c';
				if (words[2] != ".." && words[2] != "/")
					path.push_back(words[2]);
				else if (words[2] == "/")
					path.clear();
				else
					path.pop_back();

				if (!path.empty()) {
					for (Node n: root)
						if (n.fileName == path[0]) {
							dir = &n;
							break;
						}
					subPath = new vector<string>(path.begin()+1, path.end());
					for (string directory : *subPath) {
						for (Node n : dir->files) {
							if (n.fileName == directory && n.isDirectory) {
								dir = &n;
								break;
							}
						}
					}
				}
			}
			else if (words[1] == "ls") {
				mode = 'l';
			}
		}
		else if (mode == 'l') {
			if (path.empty()) {
				if (words[0] == "dir") {
					root.push_back(Node(words[1], true));
					cout << "/" << words[1] << "/" << endl;
				}
				else {
					root.push_back(Node(words[1], (unsigned int) stoul(words[0])));
					cout << "/" << words[1] << " " << stoul(words[0]) << endl;
				}
			}
			else {
				if (words[0] == "dir"){
					dir->insertFile(Node(words[1], true));
					//cout << dir->files.size() << endl;
					cout << "/";
					for (string f: path)
						cout << f << "/";
					cout << words[1] << "/" << endl;
				}
				else {
					dir->insertFile(Node(words[1], (unsigned int) stoul(words[0])));
					//cout << dir->files.size() << endl;
					cout << "/";
					for (string f: path)
						cout << f << "/";
					cout << words[1] << " " << stoul(words[0]) << endl;
				}
			}
		}
	}

	vector<Node*> dirs;
	for (Node n : root) {
		n.calcFileSize();
		if (n.isDirectory)
			for (Node* n1 : n.grabDirs())
				dirs.push_back(n1);
	}
	unsigned int sum = 0;
	for (Node* n: dirs) {
		if(n->getSize() <= 100000)
			sum += n->getSize();
	}

	cout << dirs.size() << endl;
	cout << sum << endl;

	in.close();

	return 0;
}
