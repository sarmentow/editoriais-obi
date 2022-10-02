#include <iostream>

using namespace std;

#define MAX_EMPRESAS 10001

int pessoas, empresas;
int pao[MAX_EMPRESAS];

int main() {
	 cin >> pessoas >> empresas;

	 for (int i = 0; i < empresas; i++) {
		cin >> pao[i];
	 }

	 int l = 1; 
	 int r = 10000;
	 int ans = 0;
	 while (l <= r) {
		int new_ans = 0;
		int m = l + (r - l) / 2;
		for (int i = 0; i < empresas; i++) {
			new_ans += pao[i] / m;
		}

		if (new_ans >= pessoas) { // tamanho bom, pode aumentar
			ans = m;	
			l = m + 1;
		} else {
			r = m - 1;
		}
	 }

	cout << ans << endl;
	return 0;
}
