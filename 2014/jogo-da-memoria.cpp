// Least Common Denominator (esse tipo exato de problema é descrito
// no Competitive Programming Handbook) 
//  
// O (N * log N)
// N/2 pares de cartas
// log N para achar o LCA e calcular a distancia entre as cartas

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<vector<int>> parent;
vector<vector<int>> adj;
vector<int> depth;
vector<pair<int, int>> ids; // ids[i] guarda as cartas {a, b} que contém o número i
vector<int> cartas;
int max_log;

void precalc_depth_parent (int node, int prev = 0) {
	depth[node] = depth[prev] + 1;
	parent[node][0] = prev;

	for (int i = 1; i <= max_log; i++) {
		parent[node][i] = parent[parent[node][i - 1]][i - 1];
	}

	for (auto n : adj[node]) {
		if (n == prev) continue;
		precalc_depth_parent(n, node);
	}
}

int kth_ancestor (int a, int k) {
	for (int i = max_log; i >= 0; i--) {
		if (k & (1 << i)) {
			a = parent[a][i];
		}
	}

	return a;
}

int lca (int a, int b) {
	if (depth[a] < depth[b]) {
		int temp = a;
		a = b;
		b = temp;
	}

	// depth[a] >= depth[b]
	a = kth_ancestor(a, depth[a] - depth[b]); // coloca 'a' e 'b' na mesma profundidade
	if (a == b) return a; // se b for um ancestral de a, o lca entre a e b é b

	for (int i = max_log; i >= 0; i--) {
		if (parent[a][i] != parent[b][i]) {
			a = parent[a][i];
			b = parent[b][i];
		}
	}

	return parent[a][0];
}

int main() {
	int n;
	cin >> n;

	parent.resize(n + 1);
	cartas.resize(n + 1);
	adj.resize(n + 1);
	depth.resize(n + 1);
	ids.resize((n + 2) / 2);

	for (int i = 1; i <= n; i++) {
		cin >> cartas[i];
	}

	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	for (int i = 1; i <= n; i++) {
		if (ids[cartas[i]].first != 0) {
			ids[cartas[i]].second = i;
		} else {
			ids[cartas[i]].first = i; 
		}
	}

	max_log = 1;
	while ((1 << max_log) < n) max_log++;

	for (int i = 0; i <= n; i++) {
		parent[i].resize(max_log + 1);
	}

	depth[0] = -1;
	precalc_depth_parent(1);

	long long ans = 0;
	for (auto p : ids) {
		if (p.first == 0) continue; // skip ids[0]
		int l = lca(p.first, p.second);
		ans += depth[p.first] + depth[p.second] - 2*depth[l];
	}

	cout << ans << endl;

	return 0;
}
