#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int WIDTH = 99;
const int HEIGHT = 99;

int main() {
	ifstream in;
	in.open("data/dec08");
	string line;
	int lineNum = 0;

	char trees[HEIGHT][WIDTH];

	while (getline(in, line)) { // write tree values to array
		for (int i = 0; i < WIDTH; i++)
			trees[lineNum][i] = line.at(i) - 48;
		lineNum++;
	}

	//for (int i = 0; i < HEIGHT; i++){
	//	for (int j = 0; j < WIDTH; j++)
	//		cout << (int) trees[i][j];
	//	cout << endl;
	//}

	char tallestAbove[HEIGHT][WIDTH];
	char tallestBelow[HEIGHT][WIDTH];
	char tallestRight[HEIGHT][WIDTH];
	char tallestLeft[HEIGHT][WIDTH];

	for (int i = 0; i < HEIGHT; i++) // clear arrays
		for (int j = 0; j < WIDTH; j++) {
			tallestAbove[i][j] = -1;
			tallestBelow[i][j] = -1;
			tallestRight[i][j] = -1;
			tallestLeft[i][j] = -1;
		}

	for (int i = 0; i < HEIGHT; i++) { // left right arrays
		for (int j = 0; j < WIDTH; j++) {
			if (trees[i][j] > tallestLeft[i][j])
				for (int k = j+1; k < WIDTH; k++)
					tallestLeft[i][k] = trees[i][j];
		}
		for (int j = WIDTH - 1; j >= 0; j--) {
			if (trees[i][j] > tallestRight[i][j])
				for (int k = j-1; k>=0; k--)
					tallestRight[i][k] = trees[i][j];
		}
	}

	//for (int i = 0; i < HEIGHT; i++) {
	//	for (int j = 0; j < WIDTH; j++)
	//		cout << (int) tallestRight[i][j];
	//	cout << endl;
	//}

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (trees[j][i] > tallestAbove[j][i])
				for (int k = j+1; k < HEIGHT; k++)
					tallestAbove[k][i] = trees[j][i];
		}
		for (int j = HEIGHT - 1; j >= 0; j--) {
			if (trees[j][i] > tallestBelow[j][i])
				for (int k = j-1; k >= 0; k--)
					tallestBelow[k][i] = trees[j][i];
		}
	}

	unsigned int count = 0;

	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			if (trees[i][j] > tallestAbove[i][j] || trees[i][j] > tallestBelow[i][j] || trees[i][j] > tallestRight[i][j] || trees[i][j] > tallestLeft[i][j])
				count++;

	cout << count << endl;

	int highScore = -1;
	int up, down, left, right;

	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++) {
			up = 0;
			down = 0;
			left = 0;
			right = 0;

			for (int k = j+1; k < WIDTH; k++) {
				right += 1;
				if (trees[i][k] >= trees[i][j])
					break;
			}
			for (int k = j-1; k >= 0; k--) {
				left += 1;
				if (trees[i][k] >= trees[i][j])
					break;
			}
			for (int k = i+1; k < HEIGHT; k++) {
				down += 1;
				if (trees[k][j] >= trees[i][j])
					break;
			}
			for (int k = i-1; k >= 0; k--) {
				up += 1;
				if (trees[k][j] >= trees[i][j])
					break;
			}
			if (up*down*left*right > highScore)
				highScore = up*down*left*right;
		}

	cout << highScore << endl;

	in.close();
	return 0;
}

