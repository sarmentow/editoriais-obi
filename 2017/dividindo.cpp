// Assunto: centroides
//
// achar o centroide (node que se retirado da árvore deixa a menor diferença possivel entre componentes),
// calcular a diferença entre o componente maior e o menor deixada

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define MAX_N 100001

int n;

vector<int> adj[MAX_N];
int subtree_sizes[MAX_N];

void calc_subtree_sizes(int current, int parent) {
	int subtree_size = 1;
	for (auto node : adj[current]) {
		if (node == parent) continue;

		calc_subtree_sizes(node, current);
		subtree_size += subtree_sizes[node];
	}

	subtree_sizes[current] = subtree_size;
}

int main() {
	cin >> n;

	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	// root at 1 to calculate subtree sizes
	calc_subtree_sizes(1, 0);

	int centroid = 0;
	int min_max_rem_component = 100000000;
	for (int node = 1; node <= n; node++) {
		int max_remaining_component = max(subtree_sizes[node], abs(n - subtree_sizes[node]));
		if (max_remaining_component < min_max_rem_component) {
			centroid = node;
			min_max_rem_component = max_remaining_component;
		}

	}

	cout << abs((n - min_max_rem_component) - min_max_rem_component) << endl;

	return 0;
}
