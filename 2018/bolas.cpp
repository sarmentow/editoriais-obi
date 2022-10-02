#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

unordered_map<int, int> arr_count;
int main() {
	// is it this easy?
	vector<int> arr;
	for (int i = 0; i < 8; i++) {
		int x;
		cin >> x;
		arr.push_back(x);
		arr_count[x]++;
	}

	for (auto i : arr) {
		if (arr_count[i] >= 5) {
			cout << "N" << endl;
			return 0;
		}
	}

	cout << "S" << endl;

	return 0;
}
