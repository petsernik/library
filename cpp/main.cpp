#include <iostream>
#include <cstdlib> // rand, srand
#include <ctime> //  time
#include <algorithm> // swap

void init_rand() {
	std::srand((unsigned int)time(0));
}

long long randint(long long x, long long y) {
	return std::rand() % (y - x + 1) + x;
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
	if (x == n-1 || x == 1)
		return true;
	for (int i = 0; i < t - 1; ++i)
	{
		x = (x * x) % n;
		if (x == n-1)
			return true;
		if (x == 1)
			return false;
	}
	return false;
}

// greatest common divisor
// complexity: O(log(n)), n = min(x,y)
long long gcd(long long x, long long y)
{
	while (y)
	{
		x %= y;
		std::swap(x, y);
	}
	return x;
}

int main()
{
	std::cout << gcd(18,(long long)243);
}