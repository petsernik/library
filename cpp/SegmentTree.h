#pragma once
#include "Std.h"

struct ll_segtree {
private:
    struct node;
    ll n;
    vec<node> tree;
public:
    ll_segtree(vec<ll> &a) {
        n = a.size();
        tree.resize(4 * n + 1);
        build(0, n, 1, a);
    }
    // add x on close segment [ql, qr]
    void add(ll ql, ll qr, ll x) {
        add(0, n, ql, qr + 1, x);
    }

    // get sum on close segment [ql, qr]
    ll query(ll ql, ll qr) {
        return query(0, n, ql, qr + 1);
    }
private:

    struct node {
        ll sum{}, err{};

        node() {};
        node(ll x) : sum(x) {};
        node(ll x, ll err) : sum(x), err(err) {};

        friend node operator+(node &a, node &b) { return node(a.sum + b.sum); };
    };


    ll left(ll v) { return v << 1; }
    ll right(ll v) { return (v << 1) + 1; }

    void build(ll l, ll r, ll v, vec<ll> &a) {
        if (r - l == 1) {
            tree[v] = a[l];
            return;
        }
        ll m = half(l + r);
        build(l, m, left(v), a);
        build(m, r, right(v), a);
        tree[v] = tree[left(v)] + tree[right(v)];
    }

    void destroy(ll v, ll err) {
        tree[v].err += err;
    }

    void push(ll l, ll r, ll v) {
        destroy(left(v), tree[v].err);
        destroy(right(v), tree[v].err);
    }

    void lazy_repair(ll l, ll r, ll v) {
        if (r - l > 1)
            push(l, r, v);
        tree[v].sum += (r - l) * tree[v].err;
        tree[v].err = 0;
    }

    // add x on segment [l, r)
    void add(ll l, ll r, ll ql, ll qr, ll x, ll v = 1) {
        lazy_repair(l, r, v);
        if (ql >= r || qr <= l)
            return;
        if (ql <= l && r <= qr) {
            destroy(v, x);
            lazy_repair(l, r, v);
            return;
        }
        ll m = half(l + r);
        add(l, m, ql, qr, x, left(v));
        add(m, r, ql, qr, x, right(v));

        tree[v] = tree[left(v)] + tree[right(v)];
    }

    // get sum on segment [l, r)
    ll query(ll l, ll r, ll ql, ll qr, ll v = 1) {
        lazy_repair(l, r, v);

        if (ql >= r || qr <= l)
            return 0;
        if (ql <= l && r <= qr)
            return tree[v].sum;

        ll m = half(l + r);
        ll x = query(l, m, ql, qr, left(v));
        ll y = query(m, r, ql, qr, right(v));

        tree[v] = tree[left(v)] + tree[right(v)];
        return x + y;
    }
};

// do not use it !!! It's a DRAFT !!!
struct ll_msegtree {
private:
    struct node;
    ll n;
    vec<node> tree;
public:
    ll_msegtree(vec<ll> &a) {
        n = a.size();
        tree.resize(4 * n + 1);
        build(0, n, 1, a);
    }
    // add x on close segment [ql, qr]
    void add(ll ql, ll qr, ll x) {
        add(0, n, ql, qr + 1, x);
    }

    // get sum on close segment [ql, qr]
    ll query(ll ql, ll qr) {
        return query(0, n, ql, qr + 1);
    }
private:

    struct node {
        ll sum{}, err{}, chg{};

        node() {};
        node(ll x) : sum(x) {};
        node(ll x, ll err) : sum(x), err(err) {};
        node(ll x, ll err, ll chg) : sum(x), err(err), chg(chg) {};

        friend node operator+(node &a, node &b) { return node(a.sum + b.sum); };
    };


    ll left(ll v) { return v << 1; }
    ll right(ll v) { return (v << 1) + 1; }

    void build(ll l, ll r, ll v, vec<ll> &a) {
        if (r - l == 1) {
            tree[v] = a[l];
            return;
        }
        ll m = half(l + r);
        build(l, m, left(v), a);
        build(m, r, right(v), a);
        tree[v] = tree[left(v)] + tree[right(v)];
    }

    void destroy(ll v, ll parent) {
        if (tree[parent].chg)
            tree[v].err = tree[parent].err;
        else
            tree[v].err += tree[parent].err;
        tree[v].chg = tree[parent].chg;
    }

    void push(ll l, ll r, ll v) {
        destroy(left(v), v);
        destroy(right(v), v);
    }

    void lazy_repair(ll l, ll r, ll v) {
        if (r - l > 1)
            push(l, r, v);
        
        if (tree[v].chg)
            tree[v].sum = (r - l) * tree[v].err;
        else 
            tree[v].sum += (r - l) * tree[v].err;
        
        tree[v] = tree[v].sum;
    }

    // add x on segment [l, r)
    void add(ll l, ll r, ll ql, ll qr, ll x, ll v = 1) {
        lazy_repair(l, r, v);
        if (ql >= r || qr <= l)
            return;
        if (ql <= l && r <= qr) {
            destroy(v, x);
            lazy_repair(l, r, v);
            return;
        }
        ll m = half(l + r);
        add(l, m, ql, qr, x, left(v));
        add(m, r, ql, qr, x, right(v));

        tree[v] = tree[left(v)] + tree[right(v)];
    }

    // get sum on segment [l, r)
    ll query(ll l, ll r, ll ql, ll qr, ll v = 1) {
        lazy_repair(l, r, v);

        if (ql >= r || qr <= l)
            return 0;
        if (ql <= l && r <= qr)
            return tree[v].sum;

        ll m = half(l + r);
        ll x = query(l, m, ql, qr, left(v));
        ll y = query(m, r, ql, qr, right(v));

        tree[v] = tree[left(v)] + tree[right(v)];
        return x + y;
    }
};