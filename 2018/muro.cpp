// DP

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

// CSES has a problem just like this
// it's all very simple to do in a 
// bottom-up fashion

using namespace std;

#define MAX_N 10001
#define MOD 1000000007

//
long long dp[MAX_N];

int main() {
	int n;
	cin >> n;

	dp[0] = 1;

	for (int i = 1; i <= n; i++) {
		if (i - 3  >= 0) {
			dp[i] += dp[i - 3] * 2;	
			dp[i] %= MOD;
		}
		if (i - 2 >= 0) { 
			dp[i] += dp[i - 2] * 4;
			dp[i] %= MOD;
		}
		if (i - 1 >= 0) { 
			dp[i] += dp[i - 1];
			dp[i] %= MOD;
		}
	}

	cout << dp[n] << endl;

	return 0;
}
