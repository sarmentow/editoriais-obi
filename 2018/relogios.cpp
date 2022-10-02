// IDEIA: traduzir grafo implícito e calcular
// o "peso" de uma edge na hora que eu for analisar
// um node que é um relógio funcional

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>

using namespace std;

#define MAX_DIM 100
#define MAX_N 10001
#define INF 1000000000

int grid[MAX_DIM][MAX_DIM];
vector<int> adj[MAX_N];
int lin, col, period;
bool seen[MAX_N];
int linear_grid[MAX_N];
int dist[MAX_N];

int idx (int i, int j) {
	return i * col + j;
}

bool allowed(int i, int j, int a, int b) {
	if (grid[i][j] == -1 || grid[i][j] == grid[a][b] + 1 || (grid[i][j] == 0 && grid[a][b] == period - 1)) return true;
	return false;
}

int main() {
	// DEBUG
	ifstream inp("debug.in");
	//

	cin >> lin >> col >> period;
	for (int i = 0; i < lin; i++) {
		for (int j = 0; j < col; j++) {
			cin >> grid[i][j];
		}
	}

	int k = 0;
	for (int i = 0; i < lin; i++) {
		for (int j = 0; j < col; j++) {
			// relogio funcionando
			if (grid[i][j] == -1) {
				if (i - 1 >= 0) {
					adj[k].push_back(idx(i - 1, j));
				}

				if (i + 1 < lin) {
					adj[k].push_back(idx(i + 1, j));
				}

				if (j - 1 >= 0) {
					adj[k].push_back(idx(i, j - 1));
				}

				if (j + 1 < col) {
					adj[k].push_back(idx(i, j + 1));
				}
			} else {
				if (i - 1 >= 0 && allowed(i - 1, j, i, j)) {
					adj[k].push_back(idx(i - 1, j));
				}

				if (i + 1 < lin && allowed(i + 1, j, i, j)) {
					adj[k].push_back(idx(i + 1, j));
				}

				if (j - 1 >= 0 && allowed(i, j - 1, i, j)) {
					adj[k].push_back(idx(i, j - 1));
				}

				if (j + 1 < col && allowed(i, j + 1, i, j)) {
					adj[k].push_back(idx(i, j + 1));
				}
			}

			linear_grid[k] = grid[i][j];

			k++;
		}
	}

	for (int i = 0; i < k; i++) {
		dist[i] = INF;
	}
	dist[0] = 0;
	
	priority_queue<pair<int, int>> q;
	q.push({0, 0});
	while (!q.empty()) {
		int paths_inserted = 0;
		int curr_dist = -q.top().first;
		int node = q.top().second;
		//cout << "Looking at " << node << " with dist " << curr_dist << endl;
		q.pop();
		if (seen[node]) {
			//cout << "already saw " << node << endl;
			continue;
		} 
		seen[node] = true;

		for (auto sink : adj[node]) {
			if (linear_grid[node] == -1) {
				if (linear_grid[sink] == -1) {
					if (curr_dist + 1 < dist[sink]) {
						dist[sink] = curr_dist + 1;
						paths_inserted++;
						q.push({-dist[sink], sink});
					}
				} else if (linear_grid[sink] <= curr_dist % period) {
					if (curr_dist + period - (curr_dist % period) + linear_grid[sink] < dist[sink]) {
						dist[sink] = curr_dist + period - (curr_dist % period) + linear_grid[sink];
						paths_inserted++;
						q.push({-dist[sink], sink});
					}
				} else if (linear_grid[sink] > curr_dist % period) {
					if (curr_dist + linear_grid[sink] - (curr_dist % period) < dist[sink]) {
						dist[sink] = curr_dist + linear_grid[sink] - (curr_dist % period);
						paths_inserted++;
						q.push({-dist[sink], sink});
					}
				}
			} else {
				if (curr_dist + 1 < dist[sink]) {
					dist[sink] = curr_dist + 1;
					paths_inserted++;
					q.push({-dist[sink], sink});
				}
			}
		}

	//	if (paths_inserted == 0) cout << "Didn't insert path: " << node / col << ", " << node % col << endl;
	}

	cout << (dist[lin*col-1] == INF ? -1 : dist[lin*col-1]) << endl;

	return 0;
}
