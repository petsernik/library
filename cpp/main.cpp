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
#include "Std.h"
#include "LCS.h"
#include "MergeSort.h"
#include "SegmentTree.h"
#include "TchOperations.h"

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


// checking for prime
// p(fp)=1/4
// complexity: O(log(n))
bool miller_rabin(int n)
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

template <typename T>
void quicksort(int a, int b, vector<T>& x) {
	if (b - a >= 2) {
		int i = partition(a, b, x);
		quicksort(a, i, x);
		quicksort(i + 1, b, x);
	}
}

template <typename T>
int partition(int a, int b, vector<T>& x) {
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
	vector<seg_t> a{ 1,6,4,2 };
	build(a, v, tl, tr);
	cout << get(v, tl, tr, 1, 3) << '\n';
	update(v, tl, tr, 3, 12);
	cout << get(v, tl, tr, 0, 3) << '\n';
}

int main()
{
	cout << Pow(2, 3);
	for (char c = 'a'; c <= 'z'; ++c)
		cout << c;
	test_st();
	cout << lcs("abd", "bcd") << endl;
	vector<int> v{ 1,5,4,3,7,10,1 };
	merge_sort(v);
	for (auto e : v)
		cout << e << " ";
}
