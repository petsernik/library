#include <iostream>
#include <set>
#include <map>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// precedence and associativity
// upper then earlier
// 
// ::
// .  ->   []   ()  a++ a-- typeid const_cast dynamic_cast reinterpret_cast static_cast
// sizeof ++a  --a  ~a  !a  -a  +a  &a  *a  new  delete  (cast)a
// .*  ->*
// *  /  %
// + -
// << >>
// < > <= >=
// == !=
// &
// ^
// |
// &&
// ||
// a?b:c  =  *= /= %= += -= <<= >>= &= |= ^= throw 
// ,

//cstdlib,time
void init_rand() {
	srand((unsigned int)time(0));
}

long long randint(long long x, long long y) {
	return (rand() + (INT_MAX + 1LL) * rand()) % (y - x + 1) + x;
}

int randint(int x, int y) {
	return rand() % (y - x + 1) + x;
}

// power
// complexity: O(log(n))
long long Pow(long long base, long long exp) {
	long long result = 1;
	while (exp) {
		if (exp & 1) result *= base;
		base *= base;
		exp >>= 1;
	}
	return result;
}

// power with module
// complexity: O(log(n))
long long powmod(long long base, long long exp, long long modulus) {
	base %= modulus;
	long long result = 1;
	while (exp) {
		if (exp & 1) result = (result * base) % modulus;
		base = (base * base) % modulus;
		exp >>= 1;
	}
	return result;
}

// checking for prime
// p(fp)=1/4
// complexity: O(log(n))
bool miller_rabin(long long n)
{
	if (n <= 1)
		return false;
	if (n <= 3)
		return true;
	if (n % 2 == 0)
		return false;
	long long u = n - 1;
	int t = 0;
	while (u % 2 == 0)
	{
		u /= 2;
		++t;
	}
	long long a = randint(2LL, n - 2);
	long long x = powmod(a, u, n);
	if (x == n - 1 || x == 1)
		return true;
	for (int i = 0; i < t - 1; ++i)
	{
		x = (x * x) % n;
		if (x == n - 1)
			return true;
		if (x == 1)
			return false;
	}
	return false;
}

// greatest common divisor
// complexity: O(log(n)), n = min(x,y)
int gcd(int x, int y)
{
	while (y)
	{
		x %= y;
		swap(x, y);
	}
	return x;
}

// greatest common divisor
// complexity: O(log(n)), n = min(x,y)
long long gcd(long long x, long long y)
{
	while (y)
	{
		x %= y;
		swap(x, y);
	}
	return x;
}

// largest common denominator
// complexity: O(log(n)), n = min(x,y)
long long lcd(long long x, long long y)
{
	return x || y ? x / gcd(x, y) * y : 0;
}

// comporator
// lexicographical_compare
struct map_comp {
	bool operator() (const string& lhs, const string& rhs) const
	{
		return lhs.length() < rhs.length() || (lhs.length() == rhs.length() && lhs < rhs);
	}
};

bool comp(int& lhs, int& rhs)
{
	return lhs > rhs;
}

typedef int seg_t;
enum class Operation { Add, Mul, Min, Max, Gcd, Lcd };
seg_t operate(seg_t x, seg_t y, Operation op) {

	switch (op)
	{
	case Operation::Add: return x + y;
	case Operation::Mul: return x * y;
	case Operation::Min: return min(x, y);
	case Operation::Max: return max(x, y);
		//case Operation::Gcd: return gcd(x, y);
		//case Operation::Lcd: return lcd(x, y);
	default: return 0;
	}
}

const int MAXN = (int)1e6;
seg_t t[4 * MAXN];
//Segment tree
//Build: O(n)
//Get value, update: O(log(n))
// main call: v=1, tl=0, tr=n-1
void build(vector<seg_t>& a, int v, int tl, int tr, Operation op = Operation::Add) {
	if (tl == tr)
		t[v] = a[tl];
	else {
		int tm = (tl + tr) / 2;
		build(a, 2 * v, tl, tm, op);
		build(a, 2 * v + 1, tm + 1, tr, op);
		t[v] = operate(t[2 * v], t[2 * v + 1], op);
	}
}

// main call: v=1, tl=0, tr=n-1
// l<=r
seg_t get(int v, int tl, int tr, int l, int r, Operation op = Operation::Add) {
	if (l == tl && r == tr)
		return t[v];
	int tm = (tl + tr) / 2;
	if (l > tm)
		return get(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, op);
	if (tm + 1 > r)
		return get(2 * v, tl, tm, l, min(r, tm), op);
	seg_t x = get(2 * v, tl, tm, l, min(r, tm), op),
		y = get(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, op);
	return operate(x, y, op);
}

// main call: v=1, tl=0, tr=n-1
void update(int v, int tl, int tr, int pos, seg_t new_val, Operation op = Operation::Add) {
	while (tl != tr)
	{
		int tm = (tl + tr) / 2;
		if (pos <= tm) { v *= 2; tr = tm; }
		else { v = 2 * v + 1; tl = tm + 1; }
	}
	t[v] = new_val;
	while (v > 1)
	{
		v /= 2;
		t[v] = operate(t[2 * v], t[2 * v + 1], op);
	}
}

// main call: v=1, tl=0, tr=n-1
//void update(int v, int tl, int tr, int pos, seg_t new_val, Operation op = Add) {
//	if (tl == tr)
//		t[v] = new_val;
//	else {
//		int tm = (tl + tr) / 2;
//		if (pos <= tm)
//			update(2 * v, tl, tm, pos, new_val, op);
//		else
//			update(2 * v + 1, tm + 1, tr, pos, new_val, op);
//		t[v] = operate(t[2 * v], t[2 * v + 1], op);
//	}
//}

template <typename T = int>
void quicksort(int a, int b, vector<T> x) {
	if (b - a >= 2) {
		int i = partition(a, b, x);
		quicksort(a, i, x);
		quicksort(i + 1, b, x);
	}
}

template <typename T = int>
int partition(int a, int b, vector<T> x) {
	int p = randint(a, b - 1);
	T y = x[p];
	swap(x[p], x[b - 1]);
	int i = a, j = b - 1;
	while (i < j) {
		if (x[i] < y)
			++i;
		else if (x[j] >= y)
			--j;
		else
			swap(x[i], x[j]);
	}
	swap(x[i], x[b - 1]);
	return i;
}

template <typename T = int>
void Merge(vector<T>& a, vector<T>& b, vector<T>& v) {
	auto it1 = a.begin();
	auto it2 = b.begin();
	auto it = v.begin();
	while (it!=v.end()) {
		if (it2 == b.end() || (it1 != a.end() && *it1 <= *it2))
			*(it++) = *(it1++);
		else
			*(it++) = *(it2++);
	}
}

template <typename T = int>
void merge_sort(vector<T>& v)
{
	if (v.size() <= 1) return;
	vector<T> a(v.begin(), v.begin() + v.size()/2);
	vector<T> b(v.begin() + v.size() / 2, v.end());
	merge_sort(a);
	merge_sort(b);
	Merge(a, b, v);
}

void ans_gcs(string a, string b, vector<vector<int>>& ans) {
	ans = vector<vector<int>>(a.size() + 1, vector<int>(b.size() + 1));
	for (size_t i = 1; i <= a.size(); ++i)
		for (size_t j = 1; j <= b.size(); ++j)
			if (a[i - 1] == b[j - 1])
				ans[i][j] = ans[i - 1][j - 1] + 1;
			else
				ans[i][j] = max(ans[i - 1][j], ans[i][j - 1]);
}

string gcs(string a, string b) {
	size_t n = a.size(), m = b.size();
	vector<vector<int>> ans; 
	ans_gcs(a, b, ans);
	int x = ans[n][m];
	string s = "";
	while (x) {
		if (a[n - 1] == b[m - 1]) {
			s = a[n - 1] + s;
			--n; --m; --x;
		}
		else if (ans[n - 1][m] == x) --n;
		else --m;
	}
	return s;
}

#include <ctime>
void time_of_work() {
	for (int i = 0; i < 9; ++i)
	{
		clock_t t0 = clock();
		// code
		clock_t t1 = clock();
		cout << "time: " << (t1 - t0) / CLOCKS_PER_SEC << endl;
	}
}

void test_st() {
	int n = 4;
	int v = 1, tl = 0, tr = n - 1;
	vector<int> a{ 1,6,4,2 };
	Operation op = Operation::Max;
	build(a, v, tl, tr, op);
	cout << get(v, tl, tr, 1, 3, op) << '\n';
	update(v, tl, tr, 3, 12, op);
	cout << get(v, tl, tr, 0, 3, op) << '\n';
}

int main()
{
	cout << gcs("abd", "bcd") << endl;
	vector<int> v{ 1,5,4,3,7,10,1 };
	merge_sort(v);
	for (auto e : v)
		cout << e << " ";
}
