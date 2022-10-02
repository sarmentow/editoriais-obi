#include <iostream>

using namespace std;

#define MAX_N 1000000

int arr[MAX_N];
int main() {
	// greedy?
	
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	int l = 0, r = n - 1;
	int ans = 0;
	int left_side = 0;
	int right_side = 0;
	bool left_change = true, right_change = true;
	while (r > l) {
		if (left_change) left_side += arr[l];	
		if (right_change) right_side += arr[r];
		left_change = false;
		right_change = false;
		if (left_side == right_side) {
			l++;
			r--;
			left_change = true;
			right_change = true;
		} else if (left_side < right_side) {
			l++;
			left_change = true;
			ans++;
		} else {
			r--;
			right_change = true;
			ans++;
		}

	}

	cout << ans << endl;

	return 0;
}
