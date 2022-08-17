#pragma once
#include "Std.h"
template <typename T>
struct Treap {
    struct Node {
        // for all k1 from left, k2 from right: k1<k<=k2; 
        // for all p1 from left or right:       p1<=p; 
        T key; ll prior;
        T sum; ll size;
        Node
            *left = nullptr,
            *right = nullptr;

        operator T() const { return key; }

        Node(T x) : key(x), prior(mt()), size(1), sum(x) {}

        static void update(Node *t) {
            if (t) {
                t->size = 1 + t->left_size() + t->right_size();

                //t->sum =
                //    t->key +
                //    (t->left ? t->left->sum : 0) +
                //    (t->right ? t->right->sum : 0);
            }
        }

        // first keys less than k, second keys at least x
        static pair<Node *, Node *> split(Node *node, const T &x) {
            if (!node) return { nullptr, nullptr };
            if (node->key < x) {
                auto p = split(node->right, x);
                node->right = p.first;
                update(node);
                return { node, p.second };
            }
            else {
                auto p = split(node->left, x);
                node->left = p.second;
                update(node);
                return { p.first, node };
            }
        }

        // second tree has k vertices
        static pair<Node *, Node *> split_size(Node *node, const ll &k) {
            if (!node) return { nullptr, nullptr };
            if (node->right_size() >= k) {
                auto p = split_size(node->right, k);
                node->right = p.first;
                update(node);
                return { node, p.second };
            }
            else {
                auto p = split_size(node->left, k - 1 - node->right_size());
                node->left = p.second;
                update(node);
                return { p.first, node };
            }
        }

        // first keys must be less than second keys
        static Node *merge(Node *t1, Node *t2) {
            if (!t1 || !t2) return t1 ? t1 : t2;
            if (t1->prior >= t2->prior) {
                t1->right = merge(t1->right, t2);
                update(t1);
                return t1;
            }
            else {
                t2->left = merge(t1, t2->left);
                update(t2);
                return t2;
            }
        }

        Node *min() {
            Node *t = this;
            while (t->left)
                t = t->left;
            return t;
        }

        Node *max() {
            Node *t = this;
            while (t->right)
                t = t->right;
            return t;
        }

        ll left_size() {
            return left ? left->size : 0;
        }

        ll right_size() {
            return right ? right->size : 0;
        }

        Node *insert(const T &x) {
            Node *k = new Node(x);
            auto p = split(this, x);
            p.first = merge(p.first, k);
            return merge(p.first, p.second);
        }

        Node *erase(const T &x) {
            if (key < x)
                right = right ? right->erase(x) : nullptr;
            else if (key > x)
                left = left ? left->erase(x) : nullptr;
            else {
                Node *res = merge(left, right);
                delete this;
                return res;
            }
            update(this);
            return this;
        }

        Node *find(const T &x) {
            Node *cur = this;
            while (cur)
                if (cur->key < x)
                    cur = cur->right;
                else if (cur->key > x)
                    cur = cur->left;
                else
                    return cur;
            return nullptr;
        }

        Node *lower_bound(const T &x) {
            Node *cur = this, *res = nullptr;
            while (cur)
                if (cur->key < x)
                    cur = cur->right;
                else {
                    res = cur;
                    cur = cur->left;
                }
            return res;
        }

        Node *upper_bound(const T &x) {
            Node *cur = this, *res = nullptr;
            while (cur)
                if (cur->key <= x)
                    cur = cur->right;
                else {
                    res = cur;
                    cur = cur->left;
                }
            return res;
        }

        void clear() {
            if (left) left->clear();
            if (right) right->clear();
            delete this;
        }
    };
    Node *head = nullptr;
    Node *min() { return head ? head->min() : nullptr; }
    Node *max() { return head ? head->max() : nullptr; }
    ll size() { return head ? head->size : 0; }
    void insert(const T &x) { head = head ? head->insert(x) : new Node(x); }
    void erase(const T &x) { head = head ? head->erase(x) : nullptr; }
    Node *find(const T &x) { return head ? head->find(x) : nullptr; }
    Node *lower_bound(const T &x) { return head ? head->lower_bound(x) : nullptr; }

    pair<Node *, Node *> split(const T &x) { return Node::split(head, x); }
    pair<Node *, Node *> split_size(const ll &k) { return Node::split_size(head, k); }
    void merge(Node *a, Node *b) { head = Node::merge(a, b); }

    ~Treap() { if (head) head->clear(); }
};


template<class T>
ostream &operator <<(ostream &os, const struct Treap<T>::Node *node) {
    if (node) {
        os << node->left;
        os << "(" << node->key << ", " << node->prior << ")\n";
        os << node->right;
    }
    return os;
}

template <typename T>
ostream &operator <<(ostream &os, const Treap<T> &treap) {
    return os << treap.head;
}