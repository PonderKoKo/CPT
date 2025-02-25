#define PROBLEM "https://judge.yosupo.jp/problem/min_cost_b_flow"

#include "../utils/graph/NetworkSimplex.cpp"

namespace std {
    ostream& operator<<(ostream& os, __int128 x) {
        const num M = 1e18;
        if (x < 0) {
            os << '-' << (-x);
        } else if (x < M) {
            os << (num) x;
        } else {
            os << x / M << setfill('0') << setw(18) << (num)(x % M) << setw(0);
        }
        return os;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    seq sup(n);
    cin >> sup;
    NetworkSimplex NS(sup);
    if (n == 0) { cout << 0 << endl; return 0; }
    vector<int> lo(m);
    __int128 ans = 0;
    for (int i = 0; i < m; ++i) {
        num a, b, l, u, k; cin >> a >> b >> l >> u >> k;
        ans += l * k;
        NS.supply[a] -= l, NS.supply[b] += l;
        NS.add_edge(a, b, u - l, k);
        lo[i] = l;
    }
    auto [fail, extra] = NS.solve();
    if (fail)
        cout << "infeasible\n";
    else {
        cout << ans + extra << '\n';
        for (int i = 0; i < n; ++i)
            cout << NS.dual[i] - NS.dual[0] << '\n';
        for (int i = 0; i < m; ++i)
            cout << NS.r[2 * i + 1] + lo[i] << '\n';
    }
    return 0;
}
