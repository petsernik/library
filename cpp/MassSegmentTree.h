#pragma once
#include "Std.h"

struct MassSegmentTree {
private:
	struct Node {
		ll sum, inheritance, type;
		Node(ll x = 0) : sum(x), inheritance(0), type(0) {}
		// merge nodes
		friend Node operator+(const Node& a, const Node& b) {
			return Node{ a.sum + b.sum };
		}
		// operation "+" in node
		void add(ll x, ll l, ll r) {
			sum += (r - l) * x;
			inheritance += x;
		}
		// operation "=" in node
		void change(ll x, ll l, ll r) {
			sum = (r - l) * x;
			inheritance = x;
			type = 1; // indicator
		}
		// get changes from parent
		void get(const Node& a, ll l, ll r) {
			if (a.type == 0) add(a.inheritance, l, r);
			else change(a.inheritance, l, r);
		}
	};
	vector<Node> tree;
	ll n;
public:
	// initialization
	template<typename T>
	MassSegmentTree(const vector<T>& a) {
		n = (ll)a.size();
		tree.resize(4 * n + 1);
		build(1, 0, n, a);
	}
	// operation "+" on [l,r]
	template<typename T>
	void add(ll l, ll r, T x) {
		add(1, 0, n, l, r + 1, x);
	}
	// operation "=" on [l,r]
	template<typename T>
	void change(ll l, ll r, T x) {
		change(1, 0, n, l, r + 1, x);
	}
	// get sum on [l,r]
	Node query(ll l, ll r) {
		return query(1, 0, n, l, r + 1);
	}
private:
	template<typename T>
	void build(ll v, ll l, ll r, const vector<T>& a) {
		if (l == r - 1) {
			tree[v] = Node(a[l]);
			return;
		}
		ll m = (l + r) / 2;
		build(2 * v + 0, l, m, a);
		build(2 * v + 1, m, r, a);
		tree[v] = tree[2 * v] + tree[2 * v + 1];
	}
	void push(ll v, ll l, ll r) {
		ll m = (l + r) / 2;
		tree[2 * v + 0].get(tree[v], l, m);
		tree[2 * v + 1].get(tree[v], m, r);
	}
	template<typename T>
	void add(ll v, ll l, ll r, ll ql, ll qr, T x) {
		if (qr <= l || r <= ql) return;
		if (ql <= l && r <= qr) {
			tree[v].add(x, l, r);
			return;
		}
		ll m = (l + r) / 2;
		push(v, l, r);
		add(2 * v + 0, l, m, ql, qr, x);
		add(2 * v + 1, m, r, ql, qr, x);
		tree[v] = tree[2 * v] + tree[2 * v + 1];
	}
	template<typename T>
	void change(ll v, ll l, ll r, ll ql, ll qr, T x) {
		if (qr <= l || r <= ql) return;
		if (ql <= l && r <= qr) {
			tree[v].change(x, l, r);
			return;
		}
		ll m = (l + r) / 2;
		push(v, l, r);
		change(2 * v + 0, l, m, ql, qr, x);
		change(2 * v + 1, m, r, ql, qr, x);
		tree[v] = tree[2 * v] + tree[2 * v + 1];
	}
	Node query(ll v, ll l, ll r, ll ql, ll qr) {
		if (qr <= l || r <= ql) return Node();
		if (ql <= l && r <= qr) return tree[v];
		ll m = (l + r) / 2;
		push(v, l, r);
		return query(2 * v, l, m, ql, qr) + query(2 * v + 1, m, r, ql, qr);
	}
};