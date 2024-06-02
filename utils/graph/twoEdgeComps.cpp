#include "../macros.h"

/* Two-Edge-Connected components in O(n + m) */
/* Returns vector of node index to component index (indices range from 1 to |comps|). */
vector<int> ec(const Table<int>& adj) {
    vector<int> d(size(adj)), a(size(adj)), st;
    int i = 0;
    function<int(int,int)> dfs = [&] (int u, int up) {
        st.push_back(u);
        for (int v : adj[u])
            up += d[v] ? (d[u] > d[v]) - (d[u] < d[v]) : (d[v] = d[u] + 1, dfs(v, -1));
        if (!up && ++i)
            while (!a[u])
                a[st.back()] = i, st.pop_back();
        return up;
    };
    rep(u, ssize(adj)) if (!d[u]++) dfs(u, 0);
    return a;
}
// https://judge.yosupo.jp/submission/200558