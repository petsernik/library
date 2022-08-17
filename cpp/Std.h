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
#include <random>
#include <functional>
#define all(x) (x).begin(), (x).end()
#define rsort(x) sort(x,[&](auto a, auto b){ return a>b; })
#define myset(T, cmp) multiset<T, function<bool(T,T)>> mset([&](T a, T b){return cmp;});
#define print(ans) cout << ans << "\n"
using namespace std;

typedef long long ll;
const ll inf = (ll)1e18;
const ll mod = 998244353;

random_device rd;
mt19937 mt(rd());
