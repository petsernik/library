#include <vector>

template <typename T>
void merge(vector<T>& a, vector<T>& b, vector<T>& v) {
	auto it1 = a.begin(), it2 = b.begin(), it = v.begin();
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

template <typename T>
void merge(vector<T>& v, ll l, ll r) {
	ll m = (l + r) / 2;
	vector<T> a(v.begin() + l, v.begin() + m);
	vector<T> b(v.begin() + m, v.begin() + r);
	ll i = 0, j = 0, k = l;
	while (k < r) {
		if (j == b.size() || (i < a.size() && a[i] <= b[j]))
			v[k++] = a[i++];
		else
			v[k++] = b[j++];
	}
}

template <typename T>
void merge_sort(vector<T>& v, ll l, ll r)
{
	if (r - l <= 1) return;
	ll m = (l + r) / 2;
	merge_sort(v, l, m);
	merge_sort(v, m, r);
	merge(v, l, r);
}