#pragma once
#include "Std.h"
// T(n) = n + o(1)
template <typename T>
int partition(int a, int b, vector<T>& x) {
	int p = mt() % (b - a) + a; // [a, b)
	T y = x[p];
	swap(x[p], x[b - 1]);
	int i = a, j = b - 1;
	while (i < j) {
		if (x[i] < y) ++i;
		else if (x[j] >= y) --j;
		else swap(x[i], x[j]);
	}
	swap(x[i], x[b - 1]);
	return i;
}

// E(T(n)) = nlogn + o(logn)
template <typename T>
void quicksort(int a, int b, vector<T>& x) {
	if (b - a >= 2) { // [a, b)
		int i = partition(a, b, x);
		quicksort(a, i, x);
		quicksort(i + 1, b, x);
	}
}

// K-th element from the begin after sorting
// E(T(n)) = 2n + o(logn)
template <typename T>
T quickselect(int a, int b, int k, vector<T>& x) {
	int p = partition(a, b, x);
	if (p == k) return x[k];
	else if (p > k) return quickselect(a, p, k, x);
	else return quickselect(p + 1, b, k, x);
}

// T(n) = 3n + o(1)
template <typename T>
auto partition(T y, vector<T>& x) {
	int a = 0, b = (int)x.size(), p;
	for (int i = a; i < b; ++i)
		if (x[i] == y) {
			p = i;
			break;
		}
	swap(x[p], x[b - 1]);
	int i = a, j = b - 1;
	while (i < j) {
		if (x[i] < y) ++i;
		else if (x[j] >= y) --j;
		else swap(x[i], x[j]);
	}
	int k = i;
	j = b - 1;
	while (i < j) {
		if (x[i] == y) ++i;
		else if (x[j] != y) --j;
		else swap(x[i], x[j]);
	}
	if (x[i] != y) --i;
	return vector<int>{k, i};
}

// K-th element from the begin after sorting
// O(n), but very-very long
template <typename T>
T select(int k, vector<T>& x) {
	int n = (int)x.size();
	int C = 101;
	if (n <= C) {
		sort(x.begin(), x.end());
		return x[k];
	}
	vector<T> y;
	for (auto it = x.begin(); it != x.end(); ) {
		vector<T> z;
		int i = C;
		while (i-- && it != x.end()) {
			z.push_back(*it);
			++it;
		}
		sort(z.begin(), z.end());
		y.push_back(*(z.begin() + (z.size() >> 1)));
	}
	int s = (int)y.size();
	T ym = select(s >> 1, y);
	auto p = partition(ym, x);
	if (p[0] <= k && k <= p[1]) return ym;
	else if (p[0] > k) {
		vector<T> v;
		for (int i = 0; i < p[0]; ++i)
			v.push_back(x[i]);
		return select(k, v);
	}
	else {
		vector<T> v;
		for (int i = p[1]; i < x.size(); ++i)
			v.push_back(x[i]);
		return select(k - p[1], v);
	}
}