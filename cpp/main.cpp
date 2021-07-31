#include <iostream>
#include <set>
#include <map>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = (int)1e6;

//cstdlib,time
void init_rand() {
	srand((unsigned int)time(0));
}

long long randint(long long x, long long y) {
	return rand() % (y - x + 1) + x;
}

// power
// complexity: O(log(n))
long long Pow(long long base, long long exp) {
	long long result = 1;
	while (exp > 0) {
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
	while (exp > 0) {
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
	if (!(n & 1)) // n%2 == 0
		return false;
	long long u = n - 1;
	int t = 0;
	while (!(u & 1)) // u%2 == 0 
	{
		u >>= 1;
		++t;
	}
	long long a = randint(2, n - 2);
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

int lcd(int x, int y)
{
	return x||y ? x / gcd(x,y) * y : 0;
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

enum Operation
{
	Add, Gcd, Lcd, Min, Max
};

int operate(int x, int y, Operation op) {
	switch (op)
	{
	case Add: return x + y;
	case Gcd: return gcd(x, y);
	case Lcd: return lcd(x, y);
	case Min: return min(x, y);
	case Max: return max(x, y);
	default: return 0;
	}
}

//Segment tree
//Build: O(n)
//Get value, update: O(log(n))
int t[4 * MAXN];
// main call: v=1, tl=0, tr=n-1
void build(vector<int> a, int v, int tl, int tr, Operation op = Add) {
	if (tl == tr)
		t[v] = a[tl];
	else {
		int tm = (tl + tr) >> 1;
		build(a, v << 1, tl, tm, op);
		build(a, (v << 1) + 1, tm + 1, tr, op);
		t[v] = operate(t[v << 1], t[(v << 1) + 1], op);
	}
}

// main call: v=1, tl=0, tr=n-1
// l<=r
int get(int v, int tl, int tr, int l, int r, Operation op = Add) {
	if (l == tl && r == tr)
		return t[v];
	int tm = (tl + tr) >> 1;
	if (l > tm) 
		return get((v << 1) + 1, tm + 1, tr, max(l, tm + 1), r, op);
	if (tm + 1 > r) 
		return get(v << 1, tl, tm, l, min(r, tm), op);
	int x = get(v << 1, tl, tm, l, min(r, tm), op),
		y = get((v << 1) + 1, tm + 1, tr, max(l, tm + 1), r, op);
	return operate(x, y, op);
}

// main call: v=1, tl=0, tr=n-1
void update(int v, int tl, int tr, int pos, int new_val, Operation op = Add) {
	while (tl != tr)
	{
		int tm = (tl + tr) >> 1;
		if (pos <= tm) { v <<= 1; tr = tm; }
		else { v = (v << 1) + 1; tl = tm + 1; }
	}
	t[v] = new_val;
	while (v > 1)
	{
		v >>= 1;
		t[v] = operate(t[v << 1], t[(v << 1) + 1], op);
	}
}

//void update(int v, int tl, int tr, int pos, int new_val, Operation op = Add) {
//	if (tl == tr)
//		t[v] = new_val;
//	else {
//		int tm = (tl + tr) >> 1;
//		if (pos <= tm)
//			update(v << 1, tl, tm, pos, new_val, op);
//		else
//			update((v << 1) + 1, tm + 1, tr, pos, new_val, op);
//		t[v] = operate(t[v << 1], t[(v << 1) + 1], op);
//	}
//}

int main()
{
	int n = 4;
	int v = 1, tl = 0, tr = n - 1;
	vector<int> a{ 1,6,4,2 };
	Operation op = Max;
	build(a, v, tl, tr, op);
	cout << get(v, tl, tr, 1, 3, op) << '\n';
	update(v, tl, tr, 3, 12, op);
	cout << get(v, tl, tr, 0, 3, op) << '\n';
}
