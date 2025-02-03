#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../utils/data structures/FenwickTree.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    seq a(n);
    cin >> a;
    FenwickTree ft(a);
    { // Check push_back
        FenwickTree ft2(0);
        for (auto x : a) ft2.push_back(x);
        assert(ft.a == ft2.a);
    }
    { // Check search
        seq p(n + 1);
        partial_sum(all(a), begin(p) + 1);
        for (auto z : p) for (auto offset : {1, -1, 0, 2, -2, -1000, 1000})
            assert(ft.search(z) == lower_bound(all(p), z) - begin(p) - 1);
    }
    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;
        if (x)
            cout << ft.sum(y, z) << '\n';
        else
            ft.add(y, z);
    }
}
