#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


long long n, k;
vector<long long> prefix;
long long arr[500000];

int main() {
	// prefix sum + binary search + clever counting
	cin >> n >> k;	
	long long s = 0;
	prefix.resize(n);
	long long zeroes = 0;
	for (long long i = 0; i < n; i++) {
		cin >> arr[i];	
		s += arr[i];
		prefix[i] = s;	
	}

	int ans = 0;
	for (long long i = 0; i < n; i++) {
		int prefix_remove = prefix[i] - k;
		auto cut_left_iter = lower_bound(prefix.begin(), prefix.end(), prefix_remove);
		int cut_left_idx = (distance(cut_left_iter, prefix.begin() + i) < 0) ? distance(prefix.begin(), cut_left_iter) : -1;

		int range_sum = (cut_left_idx > 0 ? prefix[i] - prefix[cut_left_idx - 1] : prefix[i]);

		if (range_sum == k) {
			ans++;	
			// account for zeroes
			auto first_in_range_after_cut_thats_not_zero = upper_bound(prefix.begin(), prefix.end(), prefix_remove);

			if (distance(prefix.begin() + i, first_in_range_after_cut_thats_not_zero) > 0) { // if my upper bound actually skips my current right (this will happen when k = 0)
				ans += distance(first_cut_in_left, prefix.begin() + i);
			} else {
				ans += distance(first_cut_in_left, first_in_range_after_cut);
			}
		} else if (range_sum < k) {
			continue;	
		} else if (range_sum > k) {
			if (arr[i] > k) {
				continue;
			} else {
				int prefix_remove = prefix[i] - k;
				// account for zeroes
				auto first_cut_in_left = lower_bound(prefix.begin(), prefix.end(), prefix_remove);
				auto first_in_range_after_cut = upper_bound(prefix.begin(), prefix.end(), prefix_remove);
				if (prefix[i] - *next(first_cut_in_left) == k) {
					ans++;
					ans += distance(first_cut_in_left, first_in_range_after_cut);
				} else {
					continue;	
				}
			}
		}
	}


	cout << ans << endl;

	return 0;
}
