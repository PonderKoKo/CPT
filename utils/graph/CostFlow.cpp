#include "../macros.h"

struct CostFlow {
	static constexpr num inf = numeric_limits<num>::max() / 4;
	struct Edge {
		int from, to;
		num cap, flow, cost;
	};
	vector<Edge> e;
	seq pot;
	Table<int> adj;
	vector<int> prev;
	CostFlow(int n) : pot(n), adj(n), prev(n) {}
	void addEdge(int from, int to, num cap, num cost) {
		if (from == to || cap <= 0)
			return;
		adj[from].push_back(size(e));
		adj[to].push_back(size(e));
		e.emplace_back(from, to, cap, 0, cost);
	}
	bool path(int s, int t) {
		seq dist(size(adj), inf);
		priority_queue<pair<num,int>,vector<pair<num,int>>,greater<>> pq;
		for (pq.emplace(dist[s] = 0, s); !empty(pq);) {
			auto [d, u] = pq.top();
			pq.pop();
			if (dist[u] != d)
				continue;
			d += pot[u];
			for (int i : adj[u]) {
				auto [from, v, cap, flow, cost] = e[i];
				cap -= flow;
				if (u == v)
					cap = flow, v = from, cost *= -1;
				num dv = d - pot[v] + cost;
				if (!cap || dv >= dist[v])
					continue;
				dist[v] = dv, prev[v] = i;
				pq.emplace(dv, v);
			}
		}
		rep(i, ssize(adj))
			pot[i] = min(inf, pot[i] + dist[i]);
		return dist[t] != inf;
	}

	pair<num,num> solve(int s, int t, num flow_limit = inf, num cost_limit = inf) {
		num flow{0}, cost{0};
		while (path(s, t)) {
#define BACKTRACE for (int x{t}, i, r; i = prev[x], r = e[i].to != x, x != s; x = r ? e[i].to : e[i].from)
			num f{flow_limit - flow}, c{0};
			BACKTRACE
				f = min(f, r ? e[i].flow : e[i].cap - e[i].flow), c += (r ? -1 : 1) * e[i].cost;
			if (c > 0)
				f = min(f, (cost_limit - cost) / c);
			flow += f;
			cost += f * c;
			BACKTRACE
				e[i].flow += r ? -f : f;
			if (flow == flow_limit || cost + c > cost_limit)
				break;
#undef BACKTRACE
		}
		return {flow, cost};
	}

	void setPotential(int s) {
		fill(all(pot), inf);
		pot[s] = 0;
		int steps = size(pot);
		for (char changed = 1; changed-- && steps--;)
			rep(u, ssize(pot))
				if (pot[u] != inf)
					for (int i : adj[u])
						if (num w = pot[u] + e[i].cost; e[i].from == u && w < pot[e[i].to])
							pot[e[i].to] = w, changed = 1;
		assert(steps >= 0); // Negative Cost Cycle
	};
};

// Performance: About equal to kactl
// Unlike kactl, supports multi-edges, flow and cost limits
/* Janky testing code
 * void solve() {
    chrono::duration<num,std::nano> mine{0}, theirs{0};
    rep(j, 100) {
        num n = 500, m = 10000, caps = 10, costs = 10;
        CostFlow cf(n);
        MCMF mf(n);
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        set<par> edges;
        while (ssize(edges) < m) {
            int a = uniform_int_distribution<int>(0, n - 1)(rng);
            int b = uniform_int_distribution<int>(0, n - 1)(rng);
            int cap = uniform_int_distribution<int>(0, caps)(rng);
            int cost = uniform_int_distribution<int>(0, costs)(rng);
            if (a == b || edges.contains(par(a, b)))
                continue;
            edges.emplace(a, b);
            cf.addEdge(a, b, cap, cost);
            mf.addEdge(a,b,cap,cost);
        }
        auto time = chrono::steady_clock::now();
        auto x = cf.solve(0, n-1);
        auto mid = chrono::steady_clock::now();
        auto y = mf.maxflow(0, n-1);
        auto end = chrono::steady_clock::now();
        mine += mid - time;
        theirs += end - mid;
        if (x != y) {
            cerr << "ERROR!";
            exit(0);
        }
    }
    cout << "mine: " << mine.count() / 1000000  << "ms" << endl;
    cout << "thei: " << theirs.count() / 1000000 << "ms" << endl;
}
 */