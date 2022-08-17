#pragma once

// power
// complexity: O(log(exp))
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
// complexity: O(log(exp))
long long powmod(long long base, long long exp, long long modulus) {
    base %= modulus;
    long long result = 1 % modulus;
    while (exp) {
        if (exp & 1) result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}

// greatest common divisor
// complexity: O(log(min(x,y)))
template <typename T>
T gcd(T x, T y)
{
    while (y) {
        x %= y;
        swap(x, y);
    }
    return x;
}

// largest common denominator
// complexity: O(log(min(x,y)))
template <typename T>
T lcd(T x, T y)
{
    return x || y ? x / gcd(x, y) * y : 0;
}

long long prime_divisor(long long x)
{
    for (long long i = 2; i * i <= x; ++i)
        if (x % i == 0)
            return i;
    return x;
}
