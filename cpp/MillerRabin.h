#pragma once
#include "Std.h"
#include "NumberTheory.h"

ll randll(ll x, ll y) {
    return (mt() + (INT_MAX + 1LL) * mt()) % (y - x + 1) + x;
}

int randint(int x, int y) {
    return mt() % (y - x + 1) + x;
}

// checking for prime
// probability(false-positive)=1/4
// complexity: O(log(n))
bool miller_rabin(ll n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0)
        return false;
    ll u = n - 1;
    ll t = 0;
    while (u % 2 == 0) {
        u /= 2;
        ++t;
    }
    ll a = randll(2, n - 2);
    ll x = powmod(a, u, n);
    if (x == n - 1 || x == 1)
        return true;
    for (ll i = 0; i < t - 1; ++i) {
        x = (x * x) % n;
        if (x == n - 1)
            return true;
        if (x == 1)
            return false;
    }
    return false;
}