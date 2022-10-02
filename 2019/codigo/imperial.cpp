#include <iostream>

using namespace std;

int calcada[500];
int n;
int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> calcada[i];
	}

	int ans = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (calcada[i] == calcada[j]) continue;
			bool valid = true;
			int prev = 0;
			int len = 0;
			for (int k = 0; k < n; k++) {
				if (calcada[k] == calcada[i] || calcada[k] == calcada[j]) {
					if (prev == calcada[k]) {
						 valid = false;
					} else {
						prev = calcada[k];
						len++;
					}
				}
			}
			ans = max(ans, len);
		}
	}

	cout << ans << endl;
}
