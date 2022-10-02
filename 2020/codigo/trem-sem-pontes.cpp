#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define MAX_N 10001

// Entrada
int nodes, edges;
int consultas;
int entry, length;
//

// mais legível que pair<int, int>
struct edge {
	int cost;
	int sink;
};

vector<vector<edge>> adj;
vector<int> dist; // guarda as distâncias calculadas pelo dijkstra
vector<bool> visited; // guarda se um node já foi visitado ou não na dfs e no dijkstra

#define INF 100000000

void dijkstra (int origin) {
	dist[origin] = 0;
	priority_queue<pair<int, int>> q;
	q.push({0, origin});
	while (!q.empty()) {
		int cost = -q.top().first, node = q.top().second; 
		q.pop();

		if (visited[node]) continue;

		visited[node] = true;
		for (auto e : adj[node]) {
			if (!visited[e.sink] && cost + e.cost < dist[e.sink]) {
				dist[e.sink] = cost + e.cost;
				q.push({-(cost + e.cost), e.sink});			
			}
		}
	}
}

int ans = INF; // guarda a resposta que será descoberta na dfs
vector<int> dfs_dist; // guarda as distancias calculadas ao longo da dfs

void dfs (int node, int cost = 0, int parent = 0) {
	visited[node] = true;

	dfs_dist[node] = cost;

	for (auto e : adj[node]) {
		if (e.sink == parent) continue;
		if (!visited[e.sink]) {
			dfs(e.sink, cost + e.cost, node);
		} else { // achou ciclo
			int tamanho_ciclo = cost + e.cost - dfs_dist[e.sink];	
			if (tamanho_ciclo >= length) {
				ans = min(ans, 2*dist[e.sink] + tamanho_ciclo);
			}
		}
	}
}


int main() {
	// fazer dijkstra da origem
	// fazer dfs da origem e guardar custo para chegar no vertice atual
	// detectar ciclo checando se o node que está prestes a ser visitado ja foi
	// caso sim, dist = min(dist, dist[atual] + edge_cost - dist[node_ja_visitado] (evitar contar 2 vezes)
	
	// TODO remember why dijkstra has this complexity
	// O(K * ((N + E Log V) + (N + E)))
	cin >> nodes >> edges;	
	
	adj.resize(nodes + 1);
	for (int i = 0; i < edges; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].push_back({c, b});
		adj[b].push_back({c, a});
	}
	
	cin >> consultas;
	
	for (int k = 0; k < consultas; k++) {
		cin >> entry >> length;

		ans = INF;
		dist.assign(nodes + 1, INF);
		visited.assign(nodes + 1, false);
		dijkstra(entry);

		dfs_dist.assign(nodes + 1, INF);
		visited.assign(nodes + 1, false);
		dfs(entry);
		if (ans == INF) {
			cout << -1 << endl;
		} else {
			cout << ans << endl;
		}
	}

	return 0;
}
