// divide and conquer
// with some caveats
// O(Nˆ3) (since in a given range you'll do at most N-1 cuts
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define MAX_N 200
#define INF 1000000
#define prev(x) ((x + terrenos - 1) % terrenos)

int prefix_sum[MAX_N + 1];
int terreno[MAX_N];
int dp[MAX_N][MAX_N];
int terrenos;
double taxa;

int get_sum(int i, int j) { 
	if (i > j) return get_sum(i, terrenos - 1) + get_sum(0, j);
	return prefix_sum[j + 1] - prefix_sum[i];
}

// refazer esse daqui;
// min tax to be payed for if i..j
// is undivided
int minimum_tax(int i, int j) {
	if (dp[i][j] != 0) return dp[i][j];

	int ans = INF;
	if (i == j) return dp[i][j] = 0;

	for (int k = j; k != i; k = prev(k)) {
		int left = minimum_tax(i, prev(k));
		int right = minimum_tax(k, j);
		int taxa_da_div = max(get_sum(i, prev(k)), get_sum(k, j));
		ans = min(ans,
				left + right +  taxa_da_div);
	}

	return dp[i][j] = ans;
}

int main() {
	ifstream inp("debug.in");
	cin >> terrenos >> taxa;
	for (int i = 0; i < terrenos; i++) {
		cin >> terreno[i];	
		prefix_sum[i + 1] = terreno[i] + prefix_sum[i];
	}

	// why does it work suddenly?
	int ans = INF;
	for (int i = 0; i < terrenos; i++) {
		ans = min(ans, minimum_tax(i, prev(i)));
	}
	cout << fixed << setprecision(2);
	cout << taxa * (double) ans << endl;
	
	return 0;
}
