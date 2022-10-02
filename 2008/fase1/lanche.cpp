// Igual ao problema Reunião de 2010
// Floyd warshall (All pairs shortest path)
// depois só checar qual das salas tem a menor maior distância

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define MAX_N 251
#define INF 100000000

// cost, to
vector<pair<int, int>> adj[MAX_N];
int n, m;
int dist[MAX_N][MAX_N];

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].push_back({c, b});
		adj[b].push_back({c, a});
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dist[i][j] = INF;
		}
		dist[i][i] = 0;
		for (auto [c, sink] : adj[i]) {
			dist[i][sink] = c;
		}
	}

	for (int mid = 1; mid <= n; mid++) {
		for (int from = 1; from <= n; from++) {
			for (int to = 1; to <= n; to++) {
				dist[from][to] = min(dist[from][to], dist[from][mid] + dist[mid][to]);
			}
		}
	}


	int sala = 0, menor_maior = INF;
	for (int i = 1; i <= n; i++) {
		int max_dist = 0;
		for (int j = 1; j <= n; j++) {
			max_dist = max(max_dist, dist[i][j]);
		}

		if (menor_maior > max_dist) {
			menor_maior = max_dist;
			sala = i;
		}
	}

	cout << menor_maior << endl;


	return 0;
}
