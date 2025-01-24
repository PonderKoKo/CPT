#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "../utils/data structures/LSTree.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;
    vector<mint> a(n);
    cin >> a;
    LSTree st(a);
    while (q--) {
        int t, l, r;
        pair<mint,mint> u;
        cin >> t >> l >> r;
        if (t)
            cout << st.query(l, r) << '\n';
        else
            cin >> u, st.update(l, r, u);
    }
}
