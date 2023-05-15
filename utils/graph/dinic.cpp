#include "../macros.h"

struct Dinic {
    struct Edge {
        num to, rev, c, oc;
        num flow() const { return max(oc - c, 0LL); }
    };
    seq lvl, ptr, q;
    vector<vector<Edge>> adj;
    Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
    void addEdge(int a, int b, num c, num rcap = 0) {
        adj[a].push_back({b, ssize(adj[b]), c, c});
        adj[b].push_back({a, ssize(adj[a]) - 1, rcap, rcap});
    }
    num dfs(num v, num t, num f) {
        if (v == t || !f) return f;
        for (num& i = ptr[v]; i < ssize(adj[v]); i++) {
            Edge& e = adj[v][i];
            if (lvl[e.to] == lvl[v] + 1)
                if (num p = dfs(e.to, t, min(f, e.c))) {
                    e.c -= p, adj[e.to][e.rev].c += p;
                    return p;
                }
        }
        return 0;
    }
    num calc(num s, num t) {
        num flow = 0; q[0] = s;
        rep(L, 31) do { // ’ int L=30’ maybe f a s t e r for random data
                lvl = ptr = seq(size(q));
                num qi = 0, qe = lvl[s] = 1;
                while (qi < qe && !lvl[t]) {
                    num v = q[qi++];
                    for (Edge e : adj[v])
                        if (!lvl[e.to] && e.c >> (30 - L))
                            q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
                }
                while (num p = dfs(s, t, LLONG_MAX)) flow += p;
            } while (lvl[t]);
        return flow;
    }
    bool leftOfMinCut(int a) { return lvl[a] != 0; }
};
