#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<int> caixas;
int main() {
	int n;
	cin >> n;
	caixas.push_back(0);
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		caixas.push_back(k);
	}

	sort(caixas.begin(), caixas.end());
	for (int i = 1; i <= n; i++) {
		bool possible = false;
		for (int j = 0; j < i; j++) {
			if (caixas[i] - caixas[j] <= 8) {
				possible = true;
				break;
			}
		}
		
		if (!possible) {
			cout << 'N' << endl;
			return 0;
		}
	}

	cout << 'S' << endl;
	

	return 0;
}
