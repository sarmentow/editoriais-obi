#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// sieve


vector<int> primes;
bool is_prime[1000000001];

int main() {
	int n;
	cin >> n;
	int k;
	cin >> k;
	int min_prime = 1000000000;
	for (int i = 0; i < k; i++) {
		int x;
		cin >> x;
		min_prime = min(min_prime, x);
		primes.push_back(x);
	}

	for (int i = 2; i <= n; i++) {
		is_prime[i] = true;
	}

	// quantos numeros na lista sao coprimos com todos os
	// primos da lista


	sort(primes.begin(), primes.end());
	int non_prime = 0;
	for (int k = 0; k < primes.size(); k++) {
		int p = primes[k];
		if (k == 0) {
			for (long long i = p+p; i <= n; i += p) {
				if (is_prime[i]) {
					non_prime++;
				}

				is_prime[i] = false;
			}
		} else {
			for (long long i = p * primes[k - 1] + p; i <= n; i+= p) {
				if (is_prime[i]) {
					non_prime++;
				}

				is_prime[i] = false;

			}
		}
	}
	cout << n - non_prime - k << endl;

	return 0;
}
