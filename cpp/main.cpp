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

void Test_SegmentTree() {
    //cout << "test massive segment tree\n";
    vector<ll> a{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    SegmentTree st(a);
    cout << st.query(0, 15).sum << "\n";
    st.change(0, 15, 1);
    cout << st.query(0, 15).sum << "\n";
    st.change(2, 5, 0);
    cout << st.query(0, 15).sum << "\n";
    st.add(3, 6, 2);
    cout << st.query(15, 15).sum << "\n";
    //cout << "\n";
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
    Test_Treap();
}
