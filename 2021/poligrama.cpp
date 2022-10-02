#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int len;
string s;
int base_freq[26];
int curr_freq[26];

vector<int> factors;

int main() {
	cin >> len;
	for (int i = 0; i < len; i++) {
		char c;
		cin >> c;
		s.push_back(c);
	}

	if (len > 1) factors.push_back(1);
	for (int i = 2; i * i <= len; i++) {
		if (len % i == 0) {
			factors.push_back(i);
			factors.push_back(len / i);
		}
	}

	sort(factors.begin(), factors.end());

	int base_anagram_len = -1;	
	for (auto div : factors) {
		for (int i = 0; i < div; i++) { // will do i < div rather than i < len / div so that the first hit I get is the smallest possible anagram
			// count freq of each letter	
			base_freq[s[i] - 'a']++;
		}
		// check if the rest of the word obeys the frequencies of the base anagram
		int start = div;
		bool is_poligram = true;
		while (start < len) {
			// count letter occurences
			for (int i = start; i < start + div; i++) {
				curr_freq[s[i] - 'a']++;				
			}

			for (int i = 0; i < 26; i++) {
				if (curr_freq[i] != base_freq[i]) {
					is_poligram = false;
				}

				curr_freq[i] = 0;
			}
			if (!is_poligram) break;


			start = start + div;
		}
		// clean up
		for (int i = 0; i < 26; i++) {
			base_freq[i] = 0;	
		}

		if (is_poligram) {
			base_anagram_len = div;	
			break;
		}
	}

	if (base_anagram_len == -1) {
		cout << '*' << endl;
	} else {
		for (int i = 0; i < base_anagram_len; i++) {
			cout << s[i];
		}

		cout << endl;
	}
}
