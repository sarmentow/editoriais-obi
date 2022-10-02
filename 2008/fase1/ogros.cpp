#include <iostream>
// O(M*log N)

using namespace std;

#define MAX_N 10001

int faixa[MAX_N];
int prize[MAX_N];

int faixas, ogros;

int main() {
	cin >> faixas >> ogros;

	faixa[0] = 0;
	for (int i = 1; i <= faixas - 1; i++) {
		cin >> faixa[i];
	}

	for (int i = 0; i < faixas; i++) {
		cin >> prize[i];
	}

	for (int o = 0; o < ogros; o++) {
		int force;
		cin >> force;
		// binary serach;
		// if force < faixa[m] -> ans = prize[m - 1]
		int l = 0;
		int r = faixas - 1;
		int ans = 0;
		while (l <= r) {
			int m = l + (r - l) / 2;	
			if (force < faixa[m]) {
				ans = prize[m - 1];
				r = m - 1;
			} else { // force >= faixa[m]
				ans = prize[m];
				l = m + 1;
			}
		}

		cout << ans << ' ';
	}

	return 0;
}
