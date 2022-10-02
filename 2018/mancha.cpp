#include <iostream>
using namespace std;
int main() {
	int a = 0;
	for (int i = 0; i < 1000000000; i++) {
		a += 1;
	}
	cout << a << endl;
	return 0;
}
