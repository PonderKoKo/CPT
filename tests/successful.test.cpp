#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<ll, ll>;
using vi = vector<ll>;
using vvi = vector<vi>;
#define rep(i, a, b) for(ll i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

vi scc(const vvi& adj) {
    int n = sz(adj), t = 0, c = 0;
    vi a(n), b(n), z(n);
    function<void(int)> f = [&] (int u) {
        if (b[u]) return;
        z[t] = u;
        b[u] = ++t;
        for (ll v : adj[u])
            f(v), b[u] = min(b[u], b[v]);
        if (u == z[b[u] - 1] && --c) while (b[u] <= t)
                a[z[--t]] = ~c, b[z[t]] = 1e9;
    };
    rep(u, 0, n) f(u);
    return a;
}

auto solve() {
    int n, m;
    cin >> n >> m;
    vvi adj(n);
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    auto c = scc(adj);
    vvi comps(ranges::max(c) + 1);
    rep(i, 0, n) comps[c[i]].push_back(i);
    cout << ssize(comps) << '\n';
    for (const auto& x : comps | views::reverse) {
        cout << sz(x) << ' ';
        for (auto z : x)
            cout << z << ' ';
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t--)
        cout, solve(), '\n';
}
