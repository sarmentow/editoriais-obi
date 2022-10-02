#include <iostream>

#define MAX_N 500

using namespace std;

char grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

int n;
char force;

// up down left right
int row_moves[] = {-1, 1, 0, 0};
int col_moves[] = {0, 0, -1, 1};

void flood (int row, int col) {
	if (row < 0 || col < 0 || row >= n || col >= n) return;
	if (visited[row][col]) return;
	if (force < grid[row][col]) return;

	visited[row][col] = true;

	for (int m = 0; m < 4; m++) {
		flood(row + row_moves[m], col + col_moves[m]);
	}
}

int main() {
	// flood fill with some conditions
		
	cin >> n >> force;
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			cin >> grid[row][col];
		}
	}

	flood(0, 0);
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			cout << (visited[row][col] ? '*' : grid[row][col]);
		}
		cout << endl;
	}


	return 0;
}
