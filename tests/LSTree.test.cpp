#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "../utils/data structures/LSTree.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    { // Test search
        num n = 100;
        vector<mint> a(n);
        for (auto& x : a) x = rng() % 100;

        LSTree st(a);
        rep(l, n) {
            num z = 0;
            for (num r = l; r < n; r++) {
                z += a[r].a;
                for (num thresh : {z - 100, z - 10, z - 1, z, z + 1, z + 10, z + 100}) {
                    auto p = [&] (mint x) { return x.a >= thresh; };
                    auto pst = [&] (mint x, int _) { return p(x); };
                    rep(_, 10) {
                        mint init = rng() % 100;
                        num ans = st.search(l, init, pst);
                        if (!ans) assert(p(accumulate(l + all(a), init)));
                        else assert(!p(accumulate(begin(a) + l, begin(a) + ans, init)) && (l + 1 == ans || p(accumulate(begin(a) + l, begin(a) + ans - 1, init))));
                    }
                }
            }
        }
    }
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
