// O(NM) para N <= 10000
// O(M) para N > 10000
// Máximo de 5 * 10ˆ8 operações
#include <iostream>

using namespace std;

int divisor[5000];
int adds[5000];
int times[5000];
int last[5000];

int main() {
	int turnos, n;
	cin >> n;
	cin >> turnos;
	for (int i = 0; i < turnos; i++) {
		cin >> divisor[i];
	}

	int final_n = n;
	for (int i = 0; i < turnos; i++) {
		final_n -= final_n/divisor[i];	
	}

	int count = 1;
	for (int i = 1; i <= final_n && count <= 10000; i++) {
		int original_i = i;
		for (int j = turnos - 1; j >= 0; j--) {
			if (last[j] != i - 1) {
				int visited_between_now_and_then = i - last[j] - 1;
				int increases = (times[j] + visited_between_now_and_then) / (divisor[j] - 1);
				adds[j] += increases;
				times[j] = (times[j] + visited_between_now_and_then) % (divisor[j] - 1);
			}
			last[j] = i;
			times[j]++;	
			i += adds[j];
			if (times[j] == divisor[j] - 1) {
				times[j] = 0;
				adds[j]++;
			}
		}
		cout << i << endl;
		i = original_i;
		count++;
	}

	return 0;
}
