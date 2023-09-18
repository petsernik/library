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
#include <chrono>
#define INCLUDE

using namespace std;
using ll = long long;
using ld = long double;
template <class T> using vec = vector<T>;
template <class T, size_t k> using arr = array<T, k>;

#define lmd(a, b, expr) [&](auto a, auto b) { return expr; }
#define all(a) (a).begin(), (a).end()
#define myset(T, a, b, cmp) multiset<T, function<bool(T, T)>> s([&](T a, T b) { return cmp; })
#define print(ans) cout << ans << "\n"
#define prret(ans) cout << ans << "\n"; return
#define ifret(stat, ans) if (stat) { prret(ans); }
#define ynret(stat) if (stat) { prret("YES"); } else { prret("NO"); }
#define fore(a) for (auto &e : (a))
#define bit(a, i) (((a) >> (i)) & 1LL)
#define mask(a, x) ((a) & (x))
#define twice(x) ((x)<<1LL)
#define half(x) ((x)>>1LL)
#define dty(a) decltype(a)
#define tmp1 template <class T>
#define tmp2 template <class T, class N>
#define tmp3 template <class T, class N, class M>
#define tmpk template <class T, size_t k>

tmp1 auto sort(T &a) { sort(all(a)); }
tmp2 auto sort(T &a, N pr) { sort(all(a), pr); }
tmp1 auto rsort(T &a) { sort(all(a), lmd(b, c, b > c)); }
tmp1 auto rsort(T f, T l) { sort(f, l, lmd(b, c, b > c)); }
tmp2 auto low(T &a, const N &x) { return lower_bound(all(a), x); }
tmp2 auto low(T f, T l, const N &x) { return lower_bound(f, l, x); }
tmp3 auto low(T &a, const N &x, M pr) { return lower_bound(all(a), x, pr); }
tmp3 auto low(T f, T l, const N &x, M pr) { return lower_bound(f, l, x, pr); }
tmp2 auto upp(T &a, const N &x) { return upper_bound(all(a), x); }
tmp2 auto upp(T f, T l, const N &x) { return upper_bound(f, l, x); }
tmp3 auto upp(T &a, const N &x, M pr) { return upper_bound(all(a), x, pr); }
tmp3 auto upp(T f, T l, const N &x, M pr) { return upper_bound(f, l, x, pr); }
tmp1 auto rev(T &a) { reverse(all(a)); }
tmp1 auto rev(T f, T l) { reverse(f, l); }
tmp1 auto mne(T &a) { return min_element(all(a)); }
tmp1 auto mne(T f, T l) { return min_element(f, l); }
tmp2 auto mne(T &a, N pr) { return min_element(all(a), pr); }
tmp2 auto mne(T f, T l, N pr) { return min_element(f, l, pr); }
tmp1 auto mxe(T &a) { return max_element(all(a)); }
tmp1 auto mxe(T f, T l) { return max_element(f, l); }
tmp2 auto mxe(T &a, N pr) { return max_element(all(a), pr); }
tmp2 auto mxe(T f, T l, N pr) { return max_element(f, l, pr); }
tmp2 auto min(T a, N b) { return sizeof(a) > sizeof(b) ? min(a, (T)b) : min((N)a, b); }
tmp2 auto max(T a, N b) { return sizeof(a) > sizeof(b) ? max(a, (T)b) : max((N)a, b); }

#ifdef __GNUC__
__extension__ typedef __int128 int128;
__extension__ typedef __float128 float128;
auto &operator>>(istream &is, int128 &x) { ll e; is >> e; x = e; return is; }
auto &operator>>(istream &is, float128 &x) { long double e; is >> e; x = e; return is; }
auto &operator<<(ostream &os, int128 &x) { return os << (long long)x; }
auto &operator<<(ostream &os, float128 &x) { return os << (long double)x; }
#else
using int128 = long long;
using float128 = long double;
#endif

tmp1 auto &operator>>(istream &is, vec<T> &x) { fore(x) is >> e; return is; }
tmp1 auto &operator>>(istream &is, vec<vec<T>> &x) { fore(x) is >> e; return is; }
tmpk auto &operator>>(istream &is, arr<T, k> &x) { fore(x) is >> e; return is; }
tmpk auto &operator>>(istream &is, vec<arr<T, k>> &x) { fore(x) is >> e; return is; }
tmp1 auto &operator<<(ostream &os, vec<T> &x) { fore(x) os << e << " "; return os; }
tmp1 auto &operator<<(ostream &os, vec<vec<T>> &x) { fore(x) os << e << "\n"; return os; }
tmpk auto &operator<<(ostream &os, arr<T, k> &x) { fore(x) os << e << " "; return os; }
tmpk auto &operator<<(ostream &os, vec<arr<T, k>> &x) { fore(x) os << e << "\n"; return os; }

// get i-th bit from a:                #DEFINE bit(a,i) (((a)>>(i))&1LL)
// x is a group like indicator:        bit(x,i) == 1  iff  i in x
// intersection group a and group x:   #DEFINE mask(a,x) ((a)&(x))

auto start_time = chrono::steady_clock::now();
auto finish_time = chrono::steady_clock::now();
random_device rd;
mt19937 mt(rd());
ll divup(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); }     // dividing a by b rounded up
ll divdown(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }   // dividing a by b rounded down
ll truemod(ll a, ll mod) { return a = a % mod, a + (a < 0) * mod; }
ll gcd(ll x, ll y) { while (y) { x %= y; swap(x, y); } return abs(x); }
ll lcm(ll x, ll y) { return abs(x * y) / gcd(x, y); }
const ll inf = (ll)1e18;
ll mod = 998244353;
const ll N = 2e5 + 1;
