#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../utils/data structures/FenwickTree.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;
    seq a(n);
    cin >> a;
    FenwickTree ft(a);
    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;
        if (x)
            cout << ft.sum(y, z) << '\n';
        else
            ft.add(y, z);
    }
}
