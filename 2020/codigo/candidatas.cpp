#include <iostream>

using namespace std;

#define MAX_N 100000

// seg tree
// why 4*MAX_N?
int nodegcd[4*MAX_N + 1];
int arr[MAX_N + 1];

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

void build_segtree(int i, int l, int r) {
	// last node
	if (l == r) {
		nodegcd[i] = arr[l]; 
		return;
	}

	if (l > r || r < l) {
 		return;
	}

	// base case
	int mid = (l + r) / 2;
	build_segtree(2*i, l, mid);
	build_segtree(2*i + 1, mid + 1, r);
	nodegcd[i] = gcd(nodegcd[2*i], nodegcd[2*i + 1]);
}

int get_interval(int ql, int qr, int i, int l, int r) {
	// options

	// isn't in range
	if (r < ql || l > qr) {
		return 0;
	} 

	// falls completely in range
	if (l >= ql && r <= qr) {
		return nodegcd[i];
	}

	int mid = (l + r) / 2;
	// falls completely into one of the children
	if (qr <= mid && ql >= l) {
		return get_interval(ql, qr, 2*i, l, mid);
	}

	if (ql > mid && qr <= r) {
		return get_interval(ql, qr, 2*i + 1, mid + 1, r);
	}


	// is outside of range
	return gcd(get_interval(ql, qr, 2*i, l, mid), get_interval(ql, qr, 2*i + 1, mid + 1, r));

	

	
}

int main() {
	int n, ops;	
	cin >> n >> ops;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	build_segtree(1, 0, n - 1);
	for (int o = 0; o < ops; o++) {
		int t, a, b;
		cin >> t >> a >> b;
		if (t == 2) {
			cout << get_interval(a - 1, b - 1, 1, 0, n - 1) << endl;
		}
	}
	return 0;
}
