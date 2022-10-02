// adhoc
// prefixos e sufixos de strings

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <unordered_set>

using namespace std;

unordered_set<string> pref_exists, suf_exists;

int main() {
	

	ifstream fin("debug.in");
	int cadeias;
	cin >> cadeias;
	
	for (int i = 0; i < cadeias; i++) {
		string c;
		cin >> c;
		
		string desired_pref, desired_suf;	
		desired_pref = c;
		for (int j = 0; j < 10; j++) {
			int tem_o_comeco = pref_exists.count(desired_pref);
			int tem_o_final = suf_exists.count(desired_suf);
			if (tem_o_comeco == 1 && (desired_suf == "" || tem_o_final == 1)) {
				cout << c << endl;
				return 0;
			}	
			desired_suf.insert(0, 1, desired_pref[desired_pref.size() - 1]);
			desired_pref.pop_back();

		}

		string pref, suf;
		pref.clear();
		suf = c;
		for (int j = 0; j < 10; j++) {
			pref_exists.insert(suf);
			suf_exists.insert(pref);
			pref.push_back(*suf.begin());
			suf.erase(0, 1);
		}

	}
	cout << "ok" << endl;

	return 0;
}
