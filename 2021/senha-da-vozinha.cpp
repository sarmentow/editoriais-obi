#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int caracteres, borradas, comprimento;
string senha_preset;
char converted_digit[500][26];
int base10_num;
vector<int> filled_blank;

// convert number from base 10 to base k
// by pushing the respective digit number (represented in a base 10 int)
// into result
//
// push zeroes while result.size() < borradas
void convert_to_base(int number, int k, vector<int>* result) {
	while (number >= k) {
		int digit_of_current_power = number % k;
		result->push_back(digit_of_current_power);
		number = number / k;
	}

	if (number > 0) {
		result->push_back(number);
	}

	while (result->size() < borradas) {
		result->push_back(0);
	}

	reverse(result->begin(), result->end());
}

int main() {
	cin >> caracteres >> borradas >> comprimento;
	cin >> senha_preset;
	string sorted_digits;
	for (int i = 0; i < borradas; i++) {
		for (int k = 0; k < comprimento; k++) {
			char c;
			cin >> c;
			sorted_digits.push_back(c);	
		}
		sort(sorted_digits.begin(), sorted_digits.end());
		for (int k = 0; k < comprimento; k++) {
			converted_digit[i][k] = sorted_digits[k];
		}
		sorted_digits.clear();
	}

	cin >> base10_num;
	convert_to_base(base10_num - 1, comprimento, &filled_blank);

	for (int main_pointer = 0, ans_pointer = 0; main_pointer < caracteres; main_pointer++) {
		if (senha_preset[main_pointer] == '#') {
			cout << converted_digit[ans_pointer][filled_blank[ans_pointer]];
			ans_pointer++;	
		} else {
			cout << senha_preset[main_pointer];
		}
	}

	cout << endl;

	return 0;
}
