#include <iostream>
#include <cstdlib> // rand(), srand()
#include <ctime> //  time()

void init_rand() {
	srand((unsigned int)time(0));
}

long long randint(long long x, long long y) {
	return rand() % (y - x + 1) + x;
}

// power
// complexity: O(log(n))
long long Pow(long long a, long long n)
{
	if (n == 0)
		return 1;
	if (n == 1)
		return a;
	long long x = Pow(a, n >> 1);
	long long y = n & 1 ? a : 1;
	return x * x * y;
}

// power with module
// complexity: O(log(n))
long long powmod(long long a, long long n, long long m)
{
	if (n == 0)
		return 1 % m;
	if (n == 1)
		return a % m;
	long long x = powmod(a, n >> 1, m);
	long long y = n & 1 ? a % m : 1;
	return (((x * x) % m) * y) % m;
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
	if (!(n & 1))
		return false;
	auto u = n - 1;
	int t = 0;
	while (!(u & 1))
	{
		u >>= 1;
		++t;
	}
	auto a = randint(2, n - 2);
	auto x = powmod(a, u, n);
	for (int i = 0; i < t; ++i)
	{
		auto y = (x * x) % n;
		if (y == 1)
			return x == 1 || x == n - 1;
		x = y;
	}
	return false;
}

template <typename t>
void swap(t& x, t& y)
{
	t z = y;
	y = x;
	x = z;
}

// greatest common divisor
// complexity: O(log(n)), n = min(x,y)
template <typename t>
t gcd(t x, t y)
{
	while (y)
	{
		x %= y;
		swap(x, y);
	}
	return x;
}


int main()
{
	std::cout << gcd(18,243);
}