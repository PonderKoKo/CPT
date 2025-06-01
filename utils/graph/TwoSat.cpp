#include "../macros.h"

struct TwoSat {
    int n, t = 0; vector<int> a, e, q, s, z, b;
    void either(auto... x) {
        (e.push_back(max(2 * x + 1, 2 * ~x)), ...);
    }
    void dfs(int u) {
        if (b[u]) return;
        z[t] = u;
        b[u] = ++t;
        for (int i = s[u]; i < s[u + 1]; i++)
            dfs(q[i]), b[u] = min(b[u], b[q[i]]);
        if (u == z[b[u] - 1]) while (b[u] <= t)
            b[z[--t]] = 1e9 + u, a[z[t] / 2] = z[t] % 2;
    }
    bool solve() {
        a.resize(n), q = e, b = s = z = vector(2 * n + 1, 0);
        for (int x : e) s[x]++;
        partial_sum(all(s), begin(s));
        rep(i, size(e)) q[--s[e[i]]] = e[i ^ 1] ^ 1;
        rep(i, 2 * n) if (dfs(i); b[i] == b[i ^ 1]) return 0;
        return 1;
    }
    void atMostOne(const vector<int>& v) {
        if (size(v) <= 1) return;
        either(~v[0], ~v[1]);
        for (int i = 1, p = v[0]; ++i < size(v); p = n++)
            either(~p, n, ~v[i - 1], n, ~v[i], ~n);
    }
};
