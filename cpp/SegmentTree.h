#include "Std.h"
// SegmentTree st(v); v is a vector;
struct SegmentTree {
private:
	struct Node {
		ll x;
	};
	Node merge(const Node& a, const Node& b) {
		return Node{ a.x + b.x };
	}
	vector<Node> tree;
	size_t n;
public:
	template<typename T>
	SegmentTree(const vector<T>& a) {
		n = a.size();
		tree.resize(4 * n + 1);
		build(1, 0, n, a);
	}
	Node query(size_t l, size_t r) {
		return query(1, 0, n, l, r+1);
	}
	template <typename T>
	void update(size_t pos, T new_val) {
		update(1, 0, n, pos, new_val);
	}
private:
	template<typename T>
	void build(size_t v, size_t tl, size_t tr, const vector<T>& a) {
		if (tl == tr-1)
			tree[v] = Node{ a[tl] };
		else {
			size_t tm = (tl + tr) / 2;
			build(2 * v, tl, tm, a);
			build(2 * v + 1, tm, tr, a);
			tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
		}
	}

	Node query(size_t v, size_t tl, size_t tr, size_t l, size_t r) {
		if (l == tl && r == tr) return tree[v];
		size_t tm = (tl + tr) / 2;
		if (l >= tm) return query(2 * v + 1, tm, tr, l, r);
		if (tm >= r) return query(2 * v, tl, tm, l, r);
		return merge(
			query(2 * v, tl, tm, l, tm),
			query(2 * v + 1, tm, tr, tm, r)
		);
	}

	template <typename T>
	void update(size_t v, size_t tl, size_t tr, size_t pos, const T& new_val) {
		if (tl == tr-1)
			tree[v] = Node{ new_val };
		else {
			size_t tm = (tl + tr) / 2;
			if (pos < tm)
				update(2 * v, tl, tm, pos, new_val);
			else
				update(2 * v + 1, tm, tr, pos, new_val);
			tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
		}
	}
};