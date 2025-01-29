#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../utils/graph/LCA.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    Table<int> adj(n);
    rep(i, n - 1) {
        int p;
        cin >> p;
        adj[p].push_back(i + 1);
    }
    LCA lca(adj);
    {
        // I should be able to construct a single-vertex LCA (this fails for some SparseTable implementations)
        LCA single(Table<int>(1));

        // Check idempotence
        assert(single.query(0, 0) == 0);
        rep(i, n) assert(lca.query(i, i) == i);

        // Check whether -1 works as neutral element
        for (int i = -1; i < n; i++) assert(lca.query(i, -1) == i && lca.query(-1, i) == i);
        for (int i : {0, -1}) assert(single.query(i, -1) == i && single.query(-1, i) == i);
    }
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca.query(u, v) << '\n';
    }
}
