// Segment tree
// Fenwick tree também funcionaria 

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

// O (q * Log n)
using namespace std;

#define MAX_ANDARES 100001

int andares, eventos;
int pessoas[MAX_ANDARES];
int seg[MAX_ANDARES*4 + 1];

void build (int node, int l, int r) {
	if (l > r) return;
	if (l == r) {
		seg[node] = pessoas[l];
		return;
	}

	int mid = (l + r) / 2;
	build(2*node, l, mid);
	build(2*node + 1, mid + 1, r);
	seg[node] = seg[2*node] + seg[2*node + 1];
}

void update(int node, int l, int r, int ql, int qr, int p) {
	if (l > qr || l > r || r < ql) return;
	// isso daqui só funciona porque as updates sao 
	// point; Se nao fossem, teria que ser
	// l >= ql && r <= qr
	if (l >= ql && r <= qr) {
		seg[node] = p;
		return;
	}

	int mid = (l + r) / 2;
	update(2*node, l, mid, ql, qr, p);
	update(2*node + 1, mid + 1, r, ql, qr, p);
	// isso daqui é o merge
	seg[node] = seg[2*node] + seg[2*node + 1];
}

int query(int node, int l, int r, int ql, int qr) {
	if (l > r || l > qr) return 0;
	if (l >= ql && r <= qr) {
		return seg[node];
	}
	
	int mid = (l + r) / 2;
	return query(2*node, l, mid, ql, qr) + query(2*node + 1, mid + 1, r, ql, qr);
}

int main() {
	cin >> andares >> eventos;
	for (int i = 1; i <= andares; i++) {
		cin >> pessoas[i];
	}

	build(1, 1, andares);

	for (int q = 0; q < eventos; q++) {
		int op;
		cin >> op;
		if (op == 0) {
			// mudança
			int andar, p;
			cin >> andar >> p;
			update(1, 1, andares, andar, andar, p);
		} else {
			int andar;
			cin >> andar;
			cout << query(1, 1, andares, 1, andar) << endl;
		}
	}


	return 0;
}
