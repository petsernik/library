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
#define all(x) (x).begin(), (x).end()
#define vcin(a) for (auto& e : a) cin >> e;
#define vcout(a) for (auto& e : a) cout << e << " ";
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
const ll inf = (ll)1e18;
const ll mod = 998244353;

void solution() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll T; cin >> T;
	while (T--) {

	}
}

ll gcd(ll x, ll y)
{
	while (y)
	{
		x %= y;
		swap(x, y);
	}
	return x;
}