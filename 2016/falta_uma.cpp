#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

using namespace std;

// gerar permutacoes
// criar um dict de strings

bool in[9];
int n;
vector<int> permute;
unordered_map<string, bool> found;
vector<int> ans;

void generate_permutation() {
	if (permute.size() == n) {
		// add to dict	
		string s;
		for (auto i : permute) {
			s.push_back(i + '0');
		}

		if (!found[s]) {
			for (auto i : permute) {
				ans.push_back(i);
			}
		}

		s.clear();
		return;
	}
	
	for (int i = 1; i <= n; i++) {
		if (!in[i]) {
			in[i] = true;
			permute.push_back(i);
			generate_permutation();
			in[i] = false;
			permute.pop_back();
		}
	}
}

int fact (int i) {
	if (i == 1) return 1;
	return i * fact(i - 1);
}

int main() {
	cin >> n;
	for (int i = 0; i < fact(n) - 1; i++) {
		string k;
		for (int j = 0; j < n; j++) {
			int a;
			cin >> a;
			k.push_back(a + '0');
		}

		found[k] = true;
		k.clear();
	}

	generate_permutation();

	for (auto i : ans) {
		cout << i << " ";
	}

	cout << endl;

	return 0;
}
