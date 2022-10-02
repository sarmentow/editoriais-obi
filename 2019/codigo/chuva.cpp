#include <iostream>

using namespace std;

int rows, cols;
char grid[500][500];
bool visited[500][500];


void flood (int row, int col) {
	if (row < 0 || row >= rows || col < 0 || col >= cols) return;
	if (grid[row][col] == '#') return;
	if (visited[row][col]) return;

	visited[row][col] = true;
	
	if (row + 1 < rows && grid[row + 1][col] == '.') flood(row + 1, col);
	else if (row + 1 < rows && grid[row + 1][col] == '#') {
		flood(row, col + 1);
		flood(row, col - 1);
	}
}

int main() {
	cin >> rows >> cols;
	pair<int, int> flood_start;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			char c;
			cin >> c;
			if (c == 'o') flood_start = {i, j};
			grid[i][j] = c;
		}
	}

	flood(flood_start.first, flood_start.second);

	cout << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << (visited[i][j] == true ? 'o' : grid[i][j]);
		}
		cout << endl;
	}

	return 0;
}
