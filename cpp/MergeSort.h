#include "Std.h"

template <typename T>
void merge(vector<T>& a, vector<T>& b, vector<T>& v) {
	auto it1 = a.begin();
	auto it2 = b.begin();
	auto it = v.begin();
	while (it != v.end()) {
		if (it2 == b.end() || (it1 != a.end() && *it1 <= *it2))
			*(it++) = *(it1++);
		else
			*(it++) = *(it2++);
	}
}

template <typename T>
void merge_sort(vector<T>& v)
{
	if (v.size() <= 1) return;
	vector<T> a(v.begin(), v.begin() + v.size() / 2);
	vector<T> b(v.begin() + v.size() / 2, v.end());
	merge_sort(a);
	merge_sort(b);
	merge(a, b, v);
}