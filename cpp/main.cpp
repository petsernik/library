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
#include "MassSegmentTree.h"
#include "TchOperations.h"
#include "Header.h"
#include "Treap.h"
#include "QuickSort_and_KthElement.h"
#include <cassert> // assert

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
// probability(false-positive)=1/4
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

void Test_SegmentTree() {
	vector<ll> a{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	SegmentTree st(a);
	cout << st.query(0, 15).x << "\n";
	st.update(3, 0);
	cout << st.query(15, 15).x << "\n";
}

void Test_MassSegmentTree() {
	//cout << "test massive segment tree\n";
	vector<ll> a{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	MassSegmentTree st(a);
	cout << st.query(0, 15).sum << "\n";
	st.change(0, 15, 1);
	cout << st.query(0, 15).sum << "\n";
	st.change(2, 5, 0);
	cout << st.query(0, 15).sum << "\n";
	st.add(3, 6, 2);
	cout << st.query(15, 15).sum << "\n";
	//cout << "\n";
}

void Test_Treap() {
	Treap* tr = {};
	tr = tr->insert(2);
	cout << *tr;
}

void Test_Kth() {
	//cout << "test k-th element selecting\n";
	vector<ll> a((int)1e6);
	for (int i = 0; i < 1e6; ++i) {
		a[i] = mt() % (int)23;
	}
	cout << quickselect(0, (int)a.size(), 27, a) << "\n";
	//cout << "\n";
}

int main()
{
	Test_Kth();
	Test_MassSegmentTree();
}
