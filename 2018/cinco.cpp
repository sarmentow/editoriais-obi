#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int number[1000];

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> number[i];
	}

	bool possible = false;
	if (number[n - 1] > 5) {
		// find largest zero
		for (int i = 0; i < n; i++) {
			if (number[i] == 0 || number[i] == 5) {
				possible = true;
				int temp = number[i];
				number[i] = number[n - 1];
				number[n - 1] = temp;
				break;
			}
		}
		
	} else {
		// find largest zero
		for (int i = 0; i < n; i++) {
			if (number[i] == 0) {
				possible = true;
				number[i] = number[n - 1];
				number[n - 1] = 0;
				break;
			}
		}
		if (!possible) {
			// else, find lowest 5
			for (int i = n - 2; i >= 0; i--) {
				if (number[i] == 5) {
					possible = true;
					number[i] = number[n - 1];
					number[n - 1] = 5;
					break;
				}
			}
		}
	}

	if (possible) {
		for (int i = 0; i < n; i++) {
			cout << number[i] << (i == n - 1 ? "" : " ");
		}
		cout << endl;
	} else {
		cout << -1 << endl;
	}

	return 0;
}
