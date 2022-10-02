#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

struct point {
	int x;
	int y;
};

point p[8];

point sub (point a, point b) {
	return {a.x - b.x, a.y - b.y};
}

int sqr_dist(point a, point b) {
	int cateto_a = (a.x - b.x) * (a.x - b.x);
	int cateto_b = (a.y - b.y) * (a.y - b.y);

	return cateto_a + cateto_b;
}

int coef_angular(point a, point b) { 
	// TODO for when A and B are parallel to the Y axis
	// i.e. b.x - a.x = 0
	// CROSS product?
	return (b.y - a.y) / (b.x - a.x);	
}

int coef_linear(int coef_a, point a) {
	// coef_a * a.x + c = a.y
	// c = a.y - coef_a * a.x;

	return a.y - coef_a * a.x;
}

bool belongs (int coef_a, int coef_l, point a) {
	return coef_a * a.x + coef_l == a.y;
}

bool eq(point a, point b) {
	return (a.x == b.x) && (a.y == b.y);
}

point medio(point a, point b) {
	return {(a.x + b.x)/2, (a.y+b.y)/2};
}

int cross_prod(point a, point b) {
	return a.x*b.y - b.x*a.y;
}

point find_intersection(int m1, int n1, int m2, int n2) {
	int x = (n2 - n1) / (m1 - m2);
	int y = m1 * x + n1;
	return {x, y};
}

bool opposite_sides (int cross_a, int cross_b) {
	if (cross_a > 0 && cross_b < 0) return true;
	if (cross_b > 0 && cross_a < 0) return true;
	return false;
}

using namespace std;

int main() {
	for (int i = 1; i <= 7; i++) {
		cin >> p[i].x >> p[i].y;
	}

	bool cond1 = false;
	//1
	if (sqr_dist(p[1], p[2]) + sqr_dist(p[1], p[3]) > sqr_dist(p[2], p[3])) {
		cond1 = true;
	}

	bool cond2 = false;
	if (sqr_dist(p[1], p[2]) == sqr_dist(p[1], p[3])) {
		cond2 = true;
	}
	
	bool cond3 = false;
	if (p[2].x != p[3].x) {
		/*
		int m = coef_angular(p[2], p[3]);		
		int n = coef_linear(m, p[2]);
		if (belongs(m, n, p[2]) && belongs(m, n, p[3]) && belongs(m, n, p[4]) && belongs(m, n, p[5])) {
			cond3 = true;
		}
		*/
		int c1 = cross_prod(p[2], p[3]);
		int c2 = cross_prod(p[2], p[4]);
		int c3 = cross_prod(p[2], p[5]);
		if (c1 == c2 == c3 == 0) cond3 = true;
		
	} else {
		cond3 = (p[2].x == p[3].x == p[4].x == p[5].x);
	}

	bool cond4 = false;
	if (p[2].x + p[3].x == p[4].x + p[5].x && p[2].y + p[3].y == p[4].y + p[5].y) {
		cond4 = true;
	}

	bool cond5 = false;
	if (sqr_dist(p[2], p[3]) > sqr_dist(p[4], p[5])) {
		cond5 = true;
	}

	bool cond6 = false;
	if (sqr_dist(p[2], p[4]) + sqr_dist(p[4], p[6]) == sqr_dist(p[2], p[6]) &&
			sqr_dist(p[3], p[5]) + sqr_dist(p[5], p[7]) == sqr_dist(p[7], p[3])) {
		cond6 = true;
	}

	bool cond7 = false;
	if (sqr_dist(p[4], p[6]) == sqr_dist(p[5], p[7])) {
		cond7 = true;
	}

	// find a way of doing this with cross products
	bool cond8 = false;

	// just need to check 2 cases:
	// either the intersection is one of the segments' extremity
	if ((eq(p[1], p[3]) && !eq(p[2], p[6])) ||
		(eq(p[1], p[2]) && !eq(p[3], p[6])) ||
		(eq(p[6], p[3]) && !eq(p[2], p[1])) ||
		(eq(p[6], p[2]) && !eq(p[3], p[1]))) {
			cond8 = true;
		} else {
			// 2 and 3 on different sides
			// p - s1 x p - s2
			int crossp1p2p3 = cross_prod(sub(p[1], p[2]), sub(p[1], p[3]));
			int crossp6p2p3 = cross_prod(sub(p[6], p[2]), sub(p[6], p[3]));
			int crossp2p1p6 = cross_prod(sub(p[2], p[1]), sub(p[2], p[6]));
			int crossp3p1p6 = cross_prod(sub(p[3], p[1]), sub(p[3], p[6]));
			
			if (opposite_sides(crossp1p2p3, crossp6p2p3) &&
				opposite_sides(crossp2p1p6, crossp3p1p6)) {
				cond8 = true;
			}
		}


	cout << (cond1 && cond2 && cond3 && cond4 && cond5 && cond6 && cond7 && cond8 ? 'S' : 'N') << endl;

	return 0;
}
