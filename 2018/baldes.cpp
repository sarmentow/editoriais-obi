#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define left(x) (2*x + 1)
#define right(x) (2*x + 2)

struct node {
	int max;
	int min;
	int ans;
};

int n, m;

struct segtree {
	int size;
	vector<node> nodes;
	void init (int n) {
		size = 1;
		while (size < n) size *= 2;
		nodes.assign(size * 3, {0, 1000000000, 0});
	}

	void merge (int n) {
		nodes[n].max = max(nodes[left(n)].max, nodes[right(n)].max);
		nodes[n].min = min(nodes[left(n)].min, nodes[right(n)].min);
		nodes[n].ans = max({
				abs(nodes[left(n)].max - nodes[right(n)].min),
				abs(nodes[right(n)].max - nodes[left(n)].min),
				nodes[left(n)].ans,
				nodes[right(n)].ans
				});
	}

	void add_ball (int b, int i, int node, int l, int r) {
		if (l > i || r < i) return;
		if (l == r && l == i) {
			nodes[node].max = max(nodes[node].max, b);
			nodes[node].min = min(nodes[node].min, b);
			return;
		};

		int mid = (l + r) / 2;
		add_ball(b, i, left(node), l, mid);
		add_ball(b, i, right(node), mid + 1, r);
		merge(node);

	}

	node combine (node a, node b) {
		int mx = max(a.max, b.max);
		int mn = min(a.min, b.min); 
		int ans = max({a.ans, b.ans, a.max - b.min, b.max - a.min});
		return {mx, mn, ans};
	}

	node biggest_diff (int ql, int qr, int node, int l, int r) {
		if (l > qr || r < ql) return {0, 100000000, 0};
		if (l >= ql && r <= qr) {
			return nodes[node];
		}

		int mid = (l + r) / 2;
		return combine(biggest_diff(ql, qr, left(node), l, mid), biggest_diff(ql, qr, right(node), mid + 1, r));

	}

	int get_biggest_diff (int ql, int qr) {
		return biggest_diff(ql, qr, 0, 0, n - 1).ans;
	}
};

int main() {
	ifstream inp("debug.in");
	inp >> n >> m;
	segtree st;
	st.init(n);
	for (int i = 0; i < n; i++) {
		int ball;
		inp >> ball;
		st.add_ball(ball, i, 0, 0, n - 1);
	}	

	for (int i = 0; i < m; i++) {
		int op, a, b;
		inp >> op >> a >> b;
		if (op == 1) {
			b--;
			st.add_ball(a, b, 0, 0, n - 1);
		} else {
			a--;
			b--;
			cout << st.get_biggest_diff(a, b) << endl;
		}
	}


	return 0;
}
