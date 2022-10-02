#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int nodes;
vector<pair<int, int>> adj[50001];
bool visited[50001];
int max_out[2][50001];

void root_tree(int current) {
	// is leaf?
	if (adj[current].size() == 0) return;
	if (adj[current].size() == 1 && visited[adj[current][0].first]) {
		max_out[0][current] = 0;
		max_out[1][current] = 0;
		return;
	}
	if (visited[current]) return;

	visited[current] = true;

	for (auto edge : adj[current]) {
		int neighbor, companhia;
		neighbor = edge.first; companhia = edge.second;
		root_tree(neighbor);
		if (companhia == 0) {
			max_out[0][current] = max(max_out[0][current], 1 + max_out[1][neighbor]);
		} else {
			max_out[1][current] = max(max_out[1][current], 1 + max_out[0][neighbor]);
		}
	}
	
}

int main() {
	cin >> nodes;
	for (int i = 0; i < nodes - 1; i++) {
		int a, b, tp;
		cin >> a >> b >> tp;
		adj[a].push_back({b, tp});
		adj[b].push_back({a, tp});
	}

	root_tree(1);
	int ans = 0;
	for (int i = 1; i <= nodes; i++) {
		ans = max(ans, max_out[0][i] + max_out[1][i] + 1);		
	}

	cout << ans << endl;
	return 0;
}
