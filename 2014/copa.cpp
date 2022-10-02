// Kruskal
// (MST)

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define MAX_N 101

int parent[MAX_N];
int component_size[MAX_N];

int find_parent(int a) {
	int pa = parent[a];
	while (pa != parent[pa]) pa = parent[pa];
	return pa;
}

void unite (int a, int b) {
	int pa = find_parent(a);	
	int pb = find_parent(b);	
	if (pa == pb) return;

	if (component_size[pa] > component_size[pb]) {
		parent[pb] = pa;	
		component_size[pa] += component_size[pb];
	} else {
		parent[pa] = pb;
		component_size[pb] += component_size[pa];
	}
}

// tentar fazer uma mst usando somente ferrovias
// daí, fazer o resto da mst usando rodovias
//{cost, {a, b}}
vector<pair<int, pair<int, int>>> ferrovias;
vector<pair<int, pair<int, int>>> rodovias;

int main() {
	int n, f, r;
	cin >> n >> f >> r;

	for (int i = 1; i <= n; i++) {
		component_size[i] = 1;
		parent[i] = i;
	}

	for (int i = 0; i < f; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		ferrovias.push_back({c, {a, b}});
	}

	for (int i = 0; i < r; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		rodovias.push_back({c, {a, b}});
	}

	sort(ferrovias.begin(), ferrovias.end());
	sort(rodovias.begin(), rodovias.end());

	int ans = 0;
	for (auto e : ferrovias) {
		int c = e.first, a = e.second.first, b = e.second.second;
		if (find_parent(a) != find_parent(b) ) {
			unite(a, b);
			ans += c;
		}
	}

	for (auto e : rodovias) {
		int c = e.first, a = e.second.first, b = e.second.second;
		if (find_parent(a) != find_parent(b) ) {
			unite(a, b);
			ans += c;
		}
	}

	cout << ans << endl;

	return 0;
}
