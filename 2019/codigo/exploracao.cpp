/* Problema de inversões que pode ser feito tanto
 *
 * cout << ans << endl;
/ com segtrees como com fenwick trees
*/


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
	vector<long long> visited;
	void init (int n) {
		size = 1;
		while (size < n) size *= 2;
		visited.assign(size * 3, 0LL);
	}

	void merge (int n ) {
		visited[n] = visited[left(n)] + visited[right(n)];
	}

	void set (int i, int n, int l, int r) {
		if (l > i || r < i) return;
		if (l == r && l == i) {
			visited[n] = 1;
			return;
		}

		int mid = (l + r) / 2;
		set (i, left(n), l, mid);
		set (i, right(n), mid + 1, r);
		merge(n);
	}

	long long get (int ql, int qr, int n, int l, int r) {
		if (l > qr || r < ql) return 0;	
		if (l >= ql && r <= qr) {
			return visited[n];
		}

		int mid = (l + r) / 2;
		return get(ql, qr, left(n), l, mid) + get(ql, qr, right(n), mid + 1, r);
	}
};

int main() {
	long long n, p, q;
	cin >> n >> p >> q;
	if (q < 0) { // evitar problemas no sinal (>= ou <=) da desigualdade
		q = -q;
		p = -p;
	}

	vector<pair<long long, long long>> points;
	for (int i = 0; i < n; i++) {
		long long x, y;
		cin >> x >> y;
		points.push_back({x, y});
	}

	// ordenar por x para que delta X na equação não seja negativo
	// e haja problemas no sinal (>= ou <=) da desigualdade
	sort(points.begin(), points.end()); 
	vector<pair<long long, long long>> eq_result;  
	int i = 0;
	for (auto [x, y] : points) {
		long long res = q * y - p * x;
		eq_result.push_back({res, i});
		i++;
	}


	// a partir daqui vira um simples problema de inversão:
	// para todo i, quantos valores j que vêm antes de i são <= i
	sort(eq_result.begin(), eq_result.end());
	segtree st;
	st.init(n);
	long long ans = 0;
	for (auto [val, idx] : eq_result) {
		ans += st.get(0, idx, 0, 0, n - 1);	
		st.set(idx, 0, 0, n - 1);
	}

	cout << ans << endl;


	return 0;
}
