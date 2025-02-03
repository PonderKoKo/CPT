#include "../macros.h"

struct TwoSat {
    int n; vector<int> a, e, z;
    void either(auto... x) {
        (e.push_back(max(2 * x, ~(2 * x))), ...);
    }
    bool solve() {
        Table<int> adj(2 * n); a.assign(n, -1);
        rep(i, size(e))
            adj[e[i]].push_back(e[i ^ 1] ^ 1);
        function<bool(int)> dfs = [&] (int u) {
            if (a[u / 2] > -1) return a[u / 2] != u % 2;
            z.push_back(u / 2); a[u / 2] = u % 2;
            return ranges::any_of(adj[u], dfs);
        };
        rep(i, n) if (z.clear(); dfs(2 * i)) {
            for (int x : z) a[x] = -1;
            if (dfs(2 * i + 1)) return 0;
        }
        return 1;
    }
    void atMostOne(const auto& v) {
        for (int x : v)
            either(~n, ~x, ~n, n + 1, ~x, n + 1), n++;
        n++;
    }
};
