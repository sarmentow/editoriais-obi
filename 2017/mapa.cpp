#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define MAX_N 100

char grid[MAX_N][MAX_N];

// up down left right
int rd[] = {-1, 1, 0, 0};
int cd[] = {0, 0, -1, 1};

bool visited[MAX_N][MAX_N];

pair<int, int> last_visited;
int l, c;
void flood_fill (int i, int j) {
	if (i < 0 || i >= l || j < 0 || j >= c) return;
	if (visited[i][j]) return;
	if (grid[i][j] == '.') return;

	visited[i][j] = true;
	last_visited = {i, j};

	for (int d = 0; d < 4; d++) {
		flood_fill(i + rd[d], j + cd[d]);
	}
}
int main() {
	cin >> l >> c;
	int start_row, start_col;
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < c; j++) {
			cin >> grid[i][j];	
			if (grid[i][j] == 'o') {
				start_row = i;
				start_col = j;
			}
		}
	}

	flood_fill(start_row, start_col);

	cout << last_visited.first + 1 << " " << last_visited.second + 1 << endl;

	return 0;
}
