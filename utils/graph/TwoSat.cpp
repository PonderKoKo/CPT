#include "../macros.h"

struct TwoSat {
    int n; vector<int> a, e, q, s, z;
    void either(auto... x) {
        (e.push_back(max(2 * x, ~(2 * x))), ...);
    }
    bool dfs(int u) {
        if (a[u / 2] > -1) return a[u / 2] != u % 2;
        z.push_back(u / 2); a[u / 2] = u % 2;
        for (int i = s[u]; i < s[u + 1]; i++)
            if (dfs(q[i])) return 1;
        return 0;
    }
    bool solve() {
        a.assign(n, -1), q = e, s.resize(2 * n + 1);
        for (int x : e) s[x]++;
        partial_sum(all(s), begin(s));
        rep(i, size(e))
            q[--s[e[i]]] = e[i ^ 1] ^ 1;
        rep(i, n) if (z.clear(); dfs(2 * i)) {
            for (int x : z) a[x] = -1;
            if (dfs(2 * i + 1)) return 0;
        }
        return 1;
    }
    void atMostOne(const vector<int>& v) {
        if (size(v) > 1) either(~v[0], ~v[1]);
        for (int i = 1, p = v[0]; i + 1 < size(v); i++, p = n++)
            either(~p, n, ~v[i], n, ~v[i+1], ~n);
    }
};
