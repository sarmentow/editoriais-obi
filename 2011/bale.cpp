// numero de inversoes
// numa segment tree
//
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define left(x) (2*x + 1)
#define right(x) (2*x + 2)

struct segtree {
	int size;
	vector<int> sums;
	void init (int n) {
		size = 1;
		while (size < n) size *= 2;
		sums.assign(size * 3, 0);
	}

	void merge (int n) {
		sums[n] = sums[left(n)] + sums[right(n)];
	}

	void set (int i, int n, int l, int r) {
		if (l > i || r < i) return;
		if (l == r && l == i) {
			sums[n] = 1;
			return;
		}

		int mid = (l + r) / 2;
		set(i, left(n), l, mid);
		set(i, right(n), mid + 1, r);
		merge(n);
	}

	int get (int ql, int qr, int n, int l, int r) {
		if (l > qr || r < ql) return 0;
		if (l >= ql && r <= qr) {
			return sums[n];
		}

		int mid = (l + r) / 2;
		return get(ql, qr, left(n), l, mid) + get(ql, qr, right(n), mid + 1, r);
	}
};

// habilidade, idx entrada
vector<pair<int, int>> bailarinas;

int main() {
	int n;
	segtree st;
	cin >> n;
	st.init(n);
	for (int i = 0; i < n; i++) {
		int hab;
		cin >> hab;
		bailarinas.push_back({hab, n - 1 - i});
	}

	sort(bailarinas.begin(), bailarinas.end());
	int ans = 0;
	for (auto [h, i] : bailarinas) {
		ans += st.get(0, i, 0, 0, n - 1);	
		st.set(i, 0, 0, n - 1);
	}

	cout << ans << endl;
	

	return 0;
}
