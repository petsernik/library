// precedence and associativity
// upper then earlier
// 
// ::                                                                                         LR
// .  ->   []   ()  a++ a-- typeid const_cast dynamic_cast reinterpret_cast static_cast       LR
// sizeof ++a  --a  ~a  !a  -a  +a  &a  *a  new  delete  (cast)a                              RL
// .*  ->*                                                                                    LR
// *  /  %                                                                                    LR
// + -                                                                                        LR
// << >>                                                                                      LR
// < > <= >=                                                                                  LR
// == !=                                                                                      LR
// &                                                                                          LR
// ^                                                                                          LR
// |                                                                                          LR
// &&                                                                                         LR
// ||                                                                                         LR
// a?b:c  =  *= /= %= += -= <<= >>= &= |= ^= throw                                            RL
// ,                                                                                          LR
#include "Std.h"
#include "LCS.h"
#include "MergeSort.h"
#include "SegmentTree.h"
#include "NumberTheory.h"
#include "Treap.h"
#include "QuickSort_and_KthElement.h"
#include "MillerRabin.h"
#include <cassert> // assert

#include <ctime>
void time_of_work() {
    for (int i = 0; i < 9; ++i)
    {
        clock_t t0 = clock();
        // code
        clock_t t1 = clock();
        cout << "time: " << (t1 - t0) / CLOCKS_PER_SEC << endl;
    }
}

void st_correct_add(ll i, ll j, ll x, vec<ll> &a) {
    for (ll m = i; m <= min(j, a.size() - 1); ++m)
        a[m] += x;
}

ll st_correct_query(ll i, ll j, vec<ll> &a) {
    ll sum{};
    for (ll m = i; m <= j; ++m)
        sum += a[m];
    return sum;
}

void mst_correct_change(ll i, ll j, ll x, vec<ll> &a) {
    for (ll m = i; m <= j; ++m)
        a[m] = x;
}

void Test_SegmentTree() {
    //cout << "test segment tree\n";
    vector<ll> a{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    ll_segtree st(a);
    st.add(0, 2, 3);
    st_correct_add(0, 2, 3, a);
    bool ok = true;
    for (ll i = 0; i < 16; ++i)
        for (ll j = i; j < 16; ++j) {
            st.add(i >> 1, 20, 5);
            st.add(i >> 1, 20, 5);
            st_correct_add(i >> 1, 20, 5, a);
            st_correct_add(i >> 1, 20, 5, a);
            ok &= st.query(i, j) == st_correct_query(i, j, a);
            ok &= st.query(i, j) == st_correct_query(i, j, a);
        }

    if (ok) print("OK!");
    else print("Failure!");
}

void Test_Treap() {
    for (int i = 0; i < 1; ++i) {
        Treap<ll> t;
        t.insert(2);
        for (int j = 0; j < 50; ++j)
            t.insert(j);
        cout << t << "\n";
        for (int j = 0; j < 21; ++j)
            t.erase(j);
        cout << t << "\n";
        t.insert(1);
        cout << " find " << t.find(1) << "\n";
        cout << " find " << t.find(21) << "\n";
    }
}

void Test_Kth() {
    //cout << "test k-th element selecting\n";
    vector<ll> a((int)1e6);
    for (int i = 0; i < 1e6; ++i) {
        a[i] = mt() % (int)23;
    }
    cout << quickselect(0, (int)a.size(), 27, a) << "\n";
    //cout << "\n";
}

int main()
{
    setlocale(LC_ALL, "Russian");
    //int k = 0;
    //cout << k << "\n", ++k;
    //Test_Treap();
    Test_SegmentTree();
}
