#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


pair<int, int> tents[2001];
int dists[2001][2001];
int memo[2001][2001];
int n;
vector<pair<int, pair<int, int>>> sorted_dists;
int max_out_of[2001];


int main() {
	cin >> n;
	tents[0] = {0, 0};
	for (int i = 1; i <= n; i++) {
		int a, b;
		cin >> a >> b;
		tents[i] = {a, b};
	}

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			if (i == j) continue;
			int a_sqr = (tents[i].first - tents[j].first)*(tents[i].first - tents[j].first);
			int b_sqr = (tents[i].second - tents[j].second)*(tents[i].second - tents[j].second);
			int dist = a_sqr + b_sqr;
			dists[i][j] = dist;
			sorted_dists.push_back({dist, {i, j}});
		}

		sort(sorted_dists.begin(), sorted_dists.end());
	}

	for (auto t : sorted_dists) {
		if (t.second.second != 0) {
			max_out_of[t.second.first] = max(max_out_of[t.second.first], 1 + max_out_of[t.second.second]);
		}
	}

	int max_candy = 0;
	for (int i = 1; i <= n; i++) {
		max_candy = max(max_candy, max_out_of[i]);
	}

	cout << max_candy << endl;
		

	return 0;
}

/*
 * I never really understood the solution of this problem
 * I didnt quite understand why I couldnt solve it before with my memo dp table
 *
 * The thing was that I had O(N(max_dist)) Memory complexity but I had O(N) transitions
 * This obviously tle'd.
 *
 * I don't quite know how to encode the distance thing in my state;
 * My state is clearly (current tent, last distance)
 *
 */
