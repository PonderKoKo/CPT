#include "../macros.h"

struct NetworkSimplex {
    seq supply, p = supply, dual = (p.push_back(0), p), d = p, to, c, r;
    num n = size(supply), inf = 1, m = 0, j = 0, q = n / 3 + 1;
    vector<set<int>> tree{size(p)};
    void add_edge(int u, int v, num cap, num cost) {
        inf += abs(cost); m += 2;
        to.push_back(v), to.push_back(u);
        c.push_back(cost), c.push_back(-cost);
        r.push_back(cap), r.push_back(0);
    }
    void update(int i) {
        num u = to[i ^ 1], v = to[i];
        dual[v] = dual[u] + c[i];
        p[v] = i ^ 1;
        d[v] = d[u] + 1;
        dfs(v);
    }
    void dfs(int u) {
        for (int i : tree[u])
            if (i != p[u])
                update(i);
    }
    void walk(num i, auto&& cb) {
        cb(i);
        for (array a{to[i], to[i ^ 1]}; a[0] != a[1]; a[i] = to[p[a[i]]]) {
            i = d[a[0]] < d[a[1]];
            cb(p[a[i]] ^ i);
        }
    }

#define toggle(i, f) rep(k, 2) tree[to[i ^ k]].f(i ^ !k)
    auto solve() {
        for (int i = 0; num x : supply) {
            num a = x < 0 ? i : n;
            add_edge(a, a ^ n ^ i++, abs(x), -exchange(inf, 0));
            toggle(size(c) - 1, insert);
        }
        dfs(n);
        rep(z, m / q + 1) {
            num x = 0, y, a = LLONG_MAX, b;
            rep(t, q) {
                num k = c[++j %= m];
                if (r[j] && (k += dual[to[j ^ 1]] - dual[to[j]]) < x)
                    x = k, y = j;
            }
            if (x) {
                z = -1;
                walk(y, [&](int i) { if (r[i] < a) a = r[i], b = i; });
                walk(y, [&](int i) { r[i] -= a; r[i ^ 1] += a; });
                toggle(y, insert);
                toggle(b, erase);
                update(p[to[b]] != b ^ y);
            }
        }
        __int128 un = 0, cost = 0;
        rep(i, m) if (c[++i] == inf) un += r[i - 1]; else cost += r[i] * c[i - 1];
        return pair{un, cost};
    }
#undef toggle
};
