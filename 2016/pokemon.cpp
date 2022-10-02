#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int doces;
int necessario[3];

int max_evo (int poke, int sobrando) {
	if (poke == 3) return 0;
	if (sobrando < necessario[poke]) {
		return max_evo(poke + 1, sobrando);
	}
	
	return max(max_evo(poke + 1, sobrando), 1 + max_evo(poke + 1, sobrando - necessario[poke]));
}


int main() {
	cin >> doces;
	cin >> necessario[0];
	cin >> necessario[1];
	cin >> necessario[2];
	
	
	cout << max_evo(0, doces) << endl;

	return 0;
}
