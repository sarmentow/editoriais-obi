#include <iostream>

using namespace std;

int main () {
	int m, a, b;
	cin >> m >> a >> b;
	int c = m - a - b;
	cout << max(a, max(b, c)) << endl;
	return 0;
}
