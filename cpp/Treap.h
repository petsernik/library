#pragma once
#include "Std.h"

struct Treap {
    // Treap* t = new Treap{x, mt()};
    // Treap* t = {};
    // x is key, y is priority
    ll x, y;
    int size = 1;
    // for all x1 from left, x2 from right: x1<x<=x2; 
    // for all y1 from left or right:       y1<=y; 
    Treap
        *left = nullptr,
        *right = nullptr;

    // pair of trees: first keys < k, second keys >= k
    pair<Treap *, Treap *> split(Treap *t, const ll &k) {
        if (!t) return { nullptr, nullptr };
        if (t->x < k) {
            pair<Treap *, Treap *> p = split(t->right, k);
            t->right = p.first;
            upd_size(t);
            return { t, p.second };
        }
        else {
            pair<Treap *, Treap *> p = split(t->left, k);
            t->left = p.second;
            upd_size(t);
            return { p.first, t };
        }
    }

    // pair of trees: second tree has k vertices
    pair<Treap *, Treap *> split_size(Treap *t, const ll &k) {
        if (!t) return { nullptr, nullptr };
        if (t->right_size() >= k) {
            pair<Treap *, Treap *> p = split_size(t->right, k);
            t->right = p.first;
            upd_size(t);
            return { t, p.second };
        }
        else {
            pair<Treap *, Treap *> p = split_size(t->left, k - 1 - t->right_size());
            t->left = p.second;
            upd_size(t);
            return { p.first, t };
        }
    }

    // first keys must be <= than second keys
    Treap *merge(Treap *t1, Treap *t2) {
        if (!t1 || !t2) return t1 ? t1 : t2;
        if (t1->y >= t2->y) {
            t1->right = merge(t1->right, t2);
            upd_size(t1);
            return t1;
        }
        else {
            t2->left = merge(t1, t2->left);
            upd_size(t2);
            return t2;
        }
    }

    // t->min();
    ll min() {
        Treap *t = this;
        while (t->left)
            t = t->left;
        return t->x;
    }

    //t->max();
    ll max() {
        Treap *t = this;
        while (t->right)
            t = t->right;
        return t->x;
    }

    int left_size() {
        return left ? left->size : 0;
    }

    int right_size() {
        return right ? right->size : 0;
    }

    void upd_size(Treap *t) {
        if (t)
            t->size = 1 +
            t->left_size() +
            t->right_size();
    }


    // t = t->insert(x);
    template <typename T>
    Treap *insert(T x) {
        Treap *k = new Treap{ x, mt() };
        pair<Treap *, Treap *> p = split(this, k->x);
        p.first = merge(p.first, k);
        return merge(p.first, p.second);
    }

    // t = t->erase(x);
    // erase first >= x
    template <typename T>
    Treap *erase(const T &x) {
        pair<Treap *, Treap *> p = split(this, x);
        Treap *treap = p.second;
        if (treap) {
            if (!treap->left) {
                Treap *t = treap->right;
                delete treap;
                return merge(p.first, t);
            }
            while (treap->left->left) {
                --treap->size;
                treap = treap->left;
            }
            --treap->size;
            Treap *new_left = treap->left->right;
            delete treap->left;
            treap->left = new_left;
        }
        return merge(p.first, p.second);
    }

    // t->find(k);
    // find first >= x
    ll find(int k) {
        pair<Treap *, Treap *> p = split(this, k);
        ll x = p.second ? p.second->min() : -inf;
        merge(p.first, p.second);
        return x;
    }

    void clear() {
        if (left) left->clear();
        if (right) right->clear();
        delete this;
    }
};

ostream &operator <<(ostream &os, const Treap *treap) {
    if (treap) {
        os << treap->left;
        os << "(" << treap->x << ", " << treap->y << ")\n";
        os << treap->right;
    }
    return os;
}