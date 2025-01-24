#include "FenwickTree.cpp"

template<num mc = 1>
struct FenwickSet : FenwickTree {
    num count(int x) { return sum(x, x + 1); }
    void insert(int x, num z = 1) { add(x, min(z, mc - count(x))); }
    void erase(int x, num z = 1) { add(x, -min(z, count(x))); }
    int lower_bound(int x) { return search(sum(x) + 1); } // Smallest y >= x.
    int prev(int x) { return search(sum(x)); } // Largest y < x.
    int find_by_order(num i) { return search(i + 1); } // i-th smallest element (0-indexed)
    num order_of_key(int x) { return sum(x); } // Number of y < x.
};
