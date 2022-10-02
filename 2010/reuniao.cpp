// FLOYD WARSHALL
// APSP

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define INF 100000000

vector<pair<int, int>> adj[100];
int dist[100][100];
int main() {
	int n, edges;
	cin >> n >> edges;

	for (int i = 0; i < edges; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].push_back({b, c});
		adj[b].push_back({a, c});
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dist[i][j] = INF;
		}

		dist[i][i] = 0;
		for (auto sink : adj[i]) {
			dist[i][sink.first] = min(dist[i][sink.first], sink.second);
		}
	}

	for (int mid = 0; mid < n; mid++) {
		for (int from = 0; from < n; from++) {
			for (int to = 0; to < n; to++) {
				dist[from][to] = min(dist[from][to], dist[from][mid] + dist[mid][to]);
				dist[to][from] = min(dist[from][to], dist[to][from]);
			}
		}
	}

	int ans = INF;
	for (int dest = 0; dest < n; dest++) {
		int max_dist = 0;
		for (int from = 0; from < n; from++) {
			max_dist = max(max_dist, dist[from][dest]);	
		}
		ans = min(max_dist, ans);
	}

	cout << ans << endl;

	return 0;
}
