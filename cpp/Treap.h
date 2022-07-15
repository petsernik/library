#pragma once
#include "Std.h"
struct Treap {
    struct Node {
        ll key, prior, size;
        // for all k1 from left, k2 from right: k1<k<=k2; 
        // for all p1 from left or right:       p1<=p; 
        Node
            *left = nullptr,
            *right = nullptr;

        // first keys less than k, second keys at least k
        pair<Node *, Node *> split(Node *node, const ll &k) {
            if (!node) return { nullptr, nullptr };
            if (node->key < k) {
                pair<Node *, Node *> p = split(node->right, k);
                node->right = p.first;
                upd_size(node);
                return { node, p.second };
            }
            else {
                pair<Node *, Node *> p = split(node->left, k);
                node->left = p.second;
                upd_size(node);
                return { p.first, node };
            }
        }

        // second tree has k vertices
        pair<Node *, Node *> split_size(Node *node, const ll &k) {
            if (!node) return { nullptr, nullptr };
            if (node->right_size() >= k) {
                pair<Node *, Node *> p = split_size(node->right, k);
                node->right = p.first;
                upd_size(node);
                return { node, p.second };
            }
            else {
                pair<Node *, Node *> p = split_size(node->left, k - 1 - node->right_size());
                node->left = p.second;
                upd_size(node);
                return { p.first, node };
            }
        }

        // first keys must be less than second keys
        Node *merge(Node *t1, Node *t2) {
            if (!t1 || !t2) return t1 ? t1 : t2;
            if (t1->prior >= t2->prior) {
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
            Node *t = this;
            while (t->left)
                t = t->left;
            return t->key;
        }

        //t->max();
        ll max() {
            Node *t = this;
            while (t->right)
                t = t->right;
            return t->key;
        }

        int left_size() {
            return left ? left->size : 0;
        }

        int right_size() {
            return right ? right->size : 0;
        }

        void upd_size(Node *t) {
            if (t)
                t->size = 1 +
                t->left_size() +
                t->right_size();
        }


        // t = t->insert(x);
        template <typename T>
        Node *insert(T x) {
            Node *k = new Node{ x, mt() };
            pair<Node *, Node *> p = split(this, k->key);
            p.first = merge(p.first, k);
            return merge(p.first, p.second);
        }

        // t = t->erase(x);
        // erase first >= x
        template <typename T>
        Node *erase(const T &x) {
            pair<Node *, Node *> p = split(this, x);
            Node *cur = p.second;
            if (cur) {
                if (!cur->left) {
                    Node *t = cur->right;
                    delete cur;
                    return merge(p.first, t);
                }
                while (cur->left->left) {
                    --cur->size;
                    cur = cur->left;
                }
                --cur->size;
                Node *new_left = cur->left->right;
                delete cur->left;
                cur->left = new_left;
            }
            return merge(p.first, p.second);
        }

        // t->find(k);
        // find first >= k
        ll find(int k) {
            pair<Node *, Node *> p = split(this, k);
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
    Node *head = {};
    ll min() { return head->min(); }
    ll max() { return head->max(); }
    void insert(ll x) { head = head->insert(x); }
    void erase(ll x) { head = head->erase(x); }
    ll find(ll x) { return head->find(x); }
    ~Treap() {
        head->clear();
    }
};

ostream &operator <<(ostream &os, const Treap::Node *node) {
    if (node) {
        os << node->left;
        os << "(" << node->key << ", " << node->prior << ")\n";
        os << node->right;
    }
    return os;
}

ostream &operator <<(ostream &os, const Treap &treap) {
    return os << treap.head;
}