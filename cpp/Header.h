#pragma once
#include <iostream>
#include <set>
#include <map>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <cmath>
#include <ctime>
#include <random>
using namespace std;

void codeforces_solution() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T; cin >> T;
	while (T--) {
		int n; cin >> n;

	}
}

ull gcd(ull x, ull y) {
	while (y) {
		x %= y;
		swap(x, y);
	}
	return x;
}

ull powmod(ull base, ull exp, int modulus) {
	base %= modulus;
	ull result = 1 % modulus;
	while (exp) {
		if (exp & 1) result = (result * base) % modulus;
		base = (base * base) % modulus;
		exp >>= 1;
	}
	return result;
}