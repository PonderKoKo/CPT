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


/* WIP
 * template<typename CAP>
struct Dinic {
	struct Edge {
		int from, to;
		CAP cap, flow;
	};
	vector<Edge> e;
	vector<int> ptr, lvl;
	vector<vector<int>> adj;
	int t;
	explicit Dinic(int n) : adj(n) {}

	void addEdge(const int& from, const int& to, const CAP& cap) {
		if (from == to || !cap)
			return;
		adj[from].push_back(size(e));
		adj[to].push_back(size(e));
#ifndef __clang__
		e.emplace_back(from, to, cap, 0);
#else
		e.push_back({from,to,cap,0});
#endif
	}
#define v (e[i].to != u ? e[i].to : e[i].from)
#define rem (e[i].to != u ? e[i].flow : e[i].cap - e[i].flow)
	CAP dfs(const int& u, const CAP& f) {
		if (u == t || !f)
			return f;
		for (int& i = ptr[u]; i < ssize(adj[u]); i++) // One among many problems is here: we should use adj[i] for the macro
			if (int c; lvl[u] + 1 == lvl[v] && (c = dfs(v, min(f, rem))))
				return e[i].flow += u == e[i].to ? c : -c, c;
		return 0;
	}

	num solve(const int& s, const int& tt) {
		t = tt;
		assert(s != t);
		num flow = 0;
		for (CAP l = numeric_limits<CAP>::max(); l; lvl[t] || (l /= 2)) {
			lvl = ptr = vector<int>(size(adj));
			lvl[s] = 1;
			for (queue<int> q{{s}}; !empty(q) && !lvl[t]; q.pop()) {
				const int& u = q.front();
				for (int i : adj[q.front()])
					if (!lvl[v] && rem >= l)
						q.push(v), lvl[v] = lvl[u] + 1;
			}
			while (auto f = dfs(s, numeric_limits<CAP>::max()))
				flow += f;
		}
		return flow;
	}
#undef v
#undef rem
	bool leftOfMinCut(const int& u) { return lvl[u]; }
};
 */