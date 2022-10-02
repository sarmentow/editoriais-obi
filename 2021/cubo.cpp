#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef long long ll;
map<int, bool> seen;

int sieve[22];
int ans;
int a, b;
ll prod = 1;

void squarecubes(vector<int> primitive_square_cubes) {
	if (prod > b || prod < 0) {
		return;
	} else if (prod >= a && not seen[prod]){
		ans++;
		seen[prod] = true;
	}
	for (auto p : primitive_square_cubes) {
		prod *= p;
		squarecubes(primitive_square_cubes);
		prod /= p;
	}
}


int main() {
	vector<int> primitive_square_cubes;
	ans = 0;
	cin >> a >> b;
	
	for (int i = 2; i < 22; i++) {
		int curr_square_cube = i * i * i * i * i * i;
		if (curr_square_cube <= b) {
			primitive_square_cubes.push_back(curr_square_cube);
		}
	}
	
	squarecubes(primitive_square_cubes);

	cout << ans << endl;

	return 0;
}
