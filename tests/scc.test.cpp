#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "../utils/graph/scc.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    Table<int> adj(n);
    rep(i, m) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    auto c = scc(adj);
    Table<int> comps(ranges::max(c) + 1);
    rep(i, n) comps[c[i]].push_back(i);
    cout << size(comps) << '\n';
    for (const auto& x : comps | views::reverse)
        cout << size(x) << ' ' << x << '\n';
}