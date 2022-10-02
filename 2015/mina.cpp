// Transformar a grade em um grafo no qual
//
// se um dos quadrados do par tiver uma pedra,
// o peso da edge é 1, caso ambos os quadrados
// não sejam uma pedra, o peso é 0
//
// fazer dijkstra do node que for o do canto 
// superior esquerdo para o inferior direito
//
// Complexidade será um pouco pior que O(nˆ2)
// (a prova matemática é simples, basta calcular o 
// numero de arestas em uma grade nxn e lembrar que
// dijkstra é O(n + mlogm) utilizando priority_queue
// no cpp ou qualquer estrutura de dados equivalente
// que permita inserir um número numa lista e ordená-lá
// em log(M) e pegar o maior ou menor número em O(1))

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/* Exemplo de grade:
 * 
 * 00
 * 10
 *
 * Index de cada quadrado quando transformados em node:
 * 01
 * 23
 */

#define MAX_N 10001
#define MAX_GRADE 100

// peso, index do node
vector<pair<int, int>> adj[MAX_N];
int n;
bool grid[MAX_GRADE][MAX_GRADE];

// dijkstra
#define INF 10000
int dist[MAX_N];
bool done[MAX_N];

int idx (int i, int j) {
	return n * i + j;
}

int cost (int i, int j) {
	if (grid[i][j]) return 1;
	return 0;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	int k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i - 1 >= 0) {
				adj[k].push_back({cost(i - 1, j), idx(i - 1, j)});
			}

			if (i + 1 < n) {
				adj[k].push_back({cost(i + 1, j), idx(i + 1, j)});
			}

			if (j - 1 >= 0) {
				adj[k].push_back({cost(i, j - 1), idx(i, j - 1)});
			}

			if (j + 1 < n) {
				adj[k].push_back({cost(i, j + 1), idx(i, j + 1)});
			}

			k++;
		}
	}

	int total = n * n;

	for (int i = 0; i < total; i++) {
		dist[i] = INF;
	}
	dist[0] = 0;
	// dist, node
	priority_queue<pair<int, int>> q;
	q.push({dist[0], 0});

	while (!q.empty()) {
		int c = -q.top().first;
		int node = q.top().second;
		q.pop();

		if (done[node]) continue;

		done[node] = true;
		for (auto [weight, sink] : adj[node]) {
			if (weight + dist[node] < dist[sink]) {
				dist[sink] = weight + dist[node];
				q.push({-dist[sink], sink});
			}
		}
	}

	cout << dist[n*n - 1] << endl;

	return 0;
}
