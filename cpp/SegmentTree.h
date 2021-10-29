#include "Std.h"

//typedef int seg_t;
const int MAXN = (int)1e6+1;
seg_t t[4 * MAXN];

//Segment tree

// main call: v=1, tl=0, tr=n-1
// complexity: O(n)
void build(const vector<seg_t>& a, int v, int tl, int tr) {
	if (tl == tr)
		t[v] = a[tl];
	else {
		int tm = (tl + tr) / 2;
		build(a, 2 * v, tl, tm);
		build(a, 2 * v + 1, tm + 1, tr);
		t[v] = t[2 * v] + t[2 * v + 1]; // operation::add
	}
}

// main call: v=1, tl=0, tr=n-1, l<=r
// complexity: O(log(n))
int get(int v, int tl, int tr, int l, int r) {
	if (l == tl && r == tr) return t[v];
	int tm = (tl + tr) / 2;
	if (l > tm) return get(2 * v + 1, tm + 1, tr, max(l, tm + 1), r);
	if (tm + 1 > r) return get(2 * v, tl, tm, l, min(r, tm));
	return get(2 * v, tl, tm, l, min(r, tm)) 
		+ get(2 * v + 1, tm + 1, tr, max(l, tm + 1), r); // operation::add
}

// main call: v=1, tl=0, tr=n-1
// complexity: O(log(n))
void update(int v, int tl, int tr, int pos, seg_t new_val) {
	if (tl == tr)
		t[v] = new_val;
	else {
		int tm = (tl + tr) / 2;
		if (pos <= tm)
			update(2 * v, tl, tm, pos, new_val);
		else
			update(2 * v + 1, tm + 1, tr, pos, new_val);
		t[v] = t[2 * v] + t[2 * v + 1]; // operation::add
	}
}