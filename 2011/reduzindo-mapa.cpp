// MST
// Kruskal ou Prim
// nesse caso Kruskal

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define MAX_NODES 501

vector<pair<int, pair<int, int>>> edges;

// union find
int parent[MAX_NODES];
int component_size[MAX_NODES];

int find_root(int a) {
	int final_p = parent[a];
	while (final_p != parent[final_p]) {
		final_p = parent[final_p];
	}

	int p = parent[a];
	int temp;
	while (p != final_p) {
		temp = parent[p];
		parent[p] = final_p;
		p = temp;
	}

	return final_p;
}

bool connected (int root_a, int root_b) {
	if (root_a == root_b) return true;
	return false;
}

void connect (int a, int b) {
	int pb = find_root(b);
	int pa = find_root(a);
	if (connected(pa, pb)) return;
	if (component_size[a] > component_size[b]) {
		parent[pb] = pa;	
	} else {
		parent[pa] = pb;
	}
}

int main() {
	int n, m;
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		parent[i] = i;
		component_size[i] = 1;
	}

	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		edges.push_back({c, {a, b}});
	}

	sort(edges.begin(), edges.end());
	int total_cost = 0;
	for (auto e : edges) {
		int cost = e.first, a = e.second.first, b = e.second.second;	
		int pa = find_root(a), pb = find_root(b);
		if (connected(pa, pb)) {
			continue;
		} else {
			total_cost += cost;
			connect(a, b);
		}
	}

	cout << total_cost << endl;

	return 0;
}
