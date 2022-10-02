#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define MAX_N 100000

vector<pair<int, int>> colunas;
int prefix_max[MAX_N];
int sufix_max[MAX_N];

int main() {
	int n;
	cin >> n;
	for (int i = 0; i< n; i++) {
		int h;
		cin >> h;
		colunas.push_back({h, i});
	}
	prefix_max[0] = colunas[0].first;

	for (auto [h, idx] : colunas) {
		if (idx == 0) continue;
		prefix_max[idx] = max(prefix_max[idx], colunas[idx].first);
	}

	reverse(colunas.begin(), colunas.end());
	sufix_max[n - 1] = colunas[n - 1].first;
	for (auto [h, idx] : colunas) {
		if (idx == n - 1) continue;
		sufix_max[idx] = max(colunas[idx].first, sufix_max[idx + 1]);
	}

	sort(colunas.begin(), colunas.end());


	int curr_height = 0;
	int ans = 0;
	if (colunas[0].second > 0) curr_height++;
	int leftmost_idx = 0;
	int rightmost_idx = 0;
	for (int i = 1; i < colunas.size(); i++) {
		auto [h, idx] = colunas[i];
		auto [prev_h, prev_idx] = colunas[i - 1];
		if (h == prev_h) {
			rightmost_idx = idx;
			if (idx > prev_idx + 1) ans = max(ans, ++curr_height);
		} else {
			if (sufix_max[prev_idx] > prev_h) ans = max(ans, ++curr_height);
			leftmost_idx = idx;
			rightmost_idx = idx;
			if (prefix_max[idx] == h) curr_height--;
			if (sufix_max[idx] == h) curr_height--;
		}
		// preciso coletar todas as colunas de mesmo tamanho, e guardar
		// a que for mais para a esquerda e mais para a direita 
		// 
		// enquanto conto tambem os picos formados enquanto percorro 
		// essas colunas
		//
		// prefix max com a mais da esquerda me dirá se tem pico para a esquerda
		// sufix max com a mais da direita me dirá se tem pico para a direita
	}

	// theres some post processing left to be done...
	//
	// compliquei?

	cout << (n == 1 ? 2 : ans + 1) << endl;


	return 0;
}
