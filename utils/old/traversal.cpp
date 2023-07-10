#include "macros.h"

/* Dinic's algorithm for Max Flow
 * Complexity: O(|V|^2 * |E|), but O(sqrt(V) * E) for Unit Graphs!
 */
template <typename flow_type>
struct dinic {
    struct edge {
        size_t src, dst, rev;
        flow_type flow, cap;
    };

    int n;
    vector<vector<edge>> adj;

    explicit dinic(int n) : n(n), adj(n), level(n), q(n), it(n) {}

    void add_edge(size_t src, size_t dst, flow_type cap, flow_type rcap = 0) {
        adj[src].push_back({src, dst, adj[dst].size(), 0, cap});
        if (src == dst)
            adj[src].back().rev++;
        adj[dst].push_back({dst, src, adj[src].size() - 1, 0, rcap});
    }

    vector<int> level, q, it;

    bool bfs(int source, int sink) {
        fill(level.begin(), level.end(), -1);
        for (int qf = level[q[0] = sink] = 0, qb = 1; qf < qb; ++qf) {
            sink = q[qf];
            for (edge &e : adj[sink]) {
                edge &r = adj[e.dst][e.rev];
                if (r.flow < r.cap && level[e.dst] == -1)
                    level[q[qb++] = e.dst] = 1 + level[sink];
            }
        }
        return level[source] != -1;
    }

    flow_type augment(int source, int sink, flow_type flow) {
        if (source == sink)
            return flow;
        for (; it[source] != adj[source].size(); ++it[source]) {
            edge &e = adj[source][it[source]];
            if (e.flow < e.cap && level[e.dst] + 1 == level[source]) {
                flow_type delta = augment(e.dst, sink, min(flow, e.cap - e.flow));
                if (delta > 0) {
                    e.flow += delta;
                    adj[e.dst][e.rev].flow -= delta;
                    return delta;
                }
            }
        }
        return 0;
    }

    flow_type max_flow(int source, int sink) {
        for (vector<edge>& u : adj)
            for (edge& e : u)
                e.flow = 0;
        flow_type flow = 0;
        flow_type oo = numeric_limits<flow_type>::max();

        while (bfs(source, sink)) {
            fill(it.begin(), it.end(), 0);
            for (flow_type f; (f = augment(source, sink, oo)) > 0;)
                flow += f;

        } // level[u] = -1 => source side of min cut
        return flow;
    }
};

/*
 * void kosaraju_orderDFS(num v, Graph& adj, bits& visited, seq& order) {
    visited[v] = true;
    for (auto& u : adj[v])
        if (!visited[u])
            kosaraju_orderDFS(u, adj, visited, order);
    order.push_back(v);
}


void kosaraju_componentDFS(num v, Graph& rev, bits& visited, seq& component) {
    visited[v] = true;
    component.push_back(v);
    for (auto u : rev[v])
        if (!visited[u])
            kosaraju_componentDFS(u, rev, visited, component);
}


void kosaraju(Graph& adj) {
    num n = adj.size();
    Graph rev(n);
    rep(i, n)
        for (auto j : adj[i])
            rev[j].push_back(i);
    bits visited(n);
    seq order;
    rep(i, n)
        if (!visited[i])
            kosaraju_orderDFS(i, adj, visited, order);
    reverse(all(order));
}
 */

void cutDFS(num v, num p, num& timer, bits& visited, seq& tin, seq& low, Graph& adj, set<num>& cut_vertices, vector<set<num>>& blocks, seq& node_stack) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    num children = 0;
    for (num to : adj[v]) {
        num stack_start = node_stack.size();
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            cutDFS(to, v, timer, visited, tin, low, adj, cut_vertices, blocks, node_stack);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && (p != -1 || children++)) {
                cut_vertices.insert(v);
                node_stack.push_back(v);
                blocks.emplace_back(node_stack.begin() + stack_start, node_stack.end());
                node_stack.resize(stack_start);
            }
        }
    }
    node_stack.push_back(v);
    if (p == -1) {
        blocks.emplace_back(all(node_stack));
        node_stack.clear();
    }
}

pair<set<num>,vector<set<num>>> find_cut_vertices_and_blocks(Graph& adj) {
    num timer = 0;
    bits visited(adj.size(), false);
    seq tin(adj.size(), -1);
    seq low(adj.size(), -1);
    set<num> cut_vertices; /* Duplicate Inserts are possible => use set */
    vector<set<num>> blocks;
    seq node_stack;
    for (num i = 0; i < adj.size(); ++i)
        if (!visited[i])
            cutDFS (i, -1, timer, visited, tin, low, adj, cut_vertices, blocks, node_stack);
    return make_pair(cut_vertices, blocks);
}

void rootingDFS(num node, seq& parent, Graph& adj) {
    for (num to : adj[node]) {
        if (parent[to] != -2)
            continue;
        parent[to] = node;
        rootingDFS(to, parent, adj);
    }
}

auto block_cut_forest(Graph& adj) {
    auto [cut_vertices, blocks] = find_cut_vertices_and_blocks(adj);
    seq block_map(adj.size());
    Graph block_adj(cut_vertices.size() + blocks.size());
    num block_num = 0;
    bits is_cut(block_adj.size());
    for (num cc : cut_vertices) {
        is_cut[block_num] = true;
        block_map[cc] = block_num++;
    }
    for (const auto& b : blocks) {
        for (num cc : b) {
            if (cut_vertices.count(cc)) {
                block_adj[block_map[cc]].push_back(block_num);
                block_adj[block_num].push_back(block_map[cc]);
            } else {
                block_map[cc] = block_num;
            }
        }
        block_num++;
    }
    seq parent(block_adj.size(), -2);
    rep(i, block_adj.size()) {
        if (parent[i] != -2)
            continue;
        parent[i] = -1;
        rootingDFS(i, parent, block_adj);
    }
    return make_tuple(parent, block_adj, block_map);
}

#define sz(x) (int)(x).size()
using ll = long long;
using vi = vector<int>;
struct PushRelabel {
    struct Edge {
        int dest, back;
        ll f, c;
    };
    vector<vector<Edge>> g;
    vector<ll> ec;
    vector<Edge*> cur;
    vector<vi> hs; vi H;
    PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}
    void addEdge(int s, int t, ll cap, ll rcap=0) {
        if (s == t) return;
        g[s].push_back({t, sz(g[t]), 0, cap});
        g[t].push_back({s, sz(g[s])-1, 0, rcap});
    }
    void addFlow(Edge& e, ll f) {
        Edge &back = g[e.dest][e.back];
        if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
        e.f += f; e.c -= f; ec[e.dest] += f;
        back.f -= f; back.c += f; ec[back.dest] -= f;
    }
    ll calc(int s, int t) {
        int v = sz(g); H[s] = v; ec[t] = 1;
        vi co(2*v); co[0] = v-1;
        rep(i,v) cur[i] = g[i].data();
        for (Edge& e : g[s]) addFlow(e, e.c);
        for (int hi = 0;;) {
            while (hs[hi].empty()) if (!hi--) return -ec[s];
            int u = hs[hi].back(); hs[hi].pop_back();
            while (ec[u] > 0) // discharge u
                if (cur[u] == g[u].data() + sz(g[u])) {
                    H[u] = 1e9;
                    for (Edge& e : g[u]) if (e.c && H[u] > H[e.dest]+1)
                            H[u] = H[e.dest]+1, cur[u] = &e;
                    if (++co[H[u]], !--co[hi] && hi < v)
                        rep(i,v) if (hi < H[i] && H[i] < v)
                        --co[H[i]], H[i] = v + 1;
                    hi = H[u];
                } else if (cur[u]->c && H[u] == H[cur[u]->dest]+1)
                    addFlow(*cur[u], min(ec[u], cur[u]->c));
                else ++cur[u];
        }
    }
    bool leftOfMinCut(int a) { return H[a] >= sz(g); }
};

#include <bits/extc++.h>
const ll INF = numeric_limits<ll>::max() / 4;
typedef vector<ll> VL;
struct MCMF {
    int N;
    vector<vi> ed, red;
    vector<VL> cap, flow, cost;
    vi seen;
    VL dist, pi;
    vector<pair<int,int>> par;
    MCMF(int N) :
            N(N), ed(N), red(N), cap(N, VL(N)), flow(cap), cost(cap),
            seen(N), dist(N), pi(N), par(N) {}
    void addEdge(int from, int to, ll cap, ll cost) {
        this->cap[from][to] = cap;
        this->cost[from][to] = cost;
        ed[from].push_back(to);
        red[to].push_back(from);
    }
    void path(int s) {
        fill(all(seen), 0);
        fill(all(dist), INF);
        dist[s] = 0; ll di;
        __gnu_pbds::priority_queue<pair<ll, int>> q;
        vector<decltype(q)::point_iterator> its(N);
        q.push({0, s});
        auto relax = [&](int i, ll cap, ll cost, int dir) {
            ll val = di - pi[i] + cost;
            if (cap && val < dist[i]) {
                dist[i] = val;
                par[i] = {s, dir};
                if (its[i] == q.end()) its[i] = q.push({-dist[i], i});
                else q.modify(its[i], {-dist[i], i});
            }
        };
        while (!q.empty()) {
            s = q.top().second; q.pop();
            seen[s] = 1; di = dist[s] + pi[s];
            for (int i : ed[s]) if (!seen[i])
                    relax(i, cap[s][i] - flow[s][i], cost[s][i], 1);
            for (int i : red[s]) if (!seen[i])
                    relax(i, flow[i][s], -cost[i][s], 0);
        }
        rep(i,N) pi[i] = min(pi[i] + dist[i], INF);
    }
    pair<ll, ll> maxflow(int s, int t) {
        ll totflow = 0, totcost = 0;
        while (path(s), seen[t]) {
            ll fl = INF;
            for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
                fl = min(fl, r ? cap[p][x] - flow[p][x] : flow[x][p]);
            totflow += fl;
            for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
                if (r) flow[p][x] += fl;
                else flow[x][p] -= fl;
        }
        rep(i,N) rep(j,N) totcost += cost[i][j] * flow[i][j];
        return {totflow, totcost};
    }
// I f some costs can be negative , c a l l t h i s before maxflow :
    void setpi(int s) { // ( otherwise , leave t h i s out)
        fill(all(pi), INF); pi[s] = 0;
        int it = N, ch = 1; ll v;
        while (ch-- && it--)
            rep(i,N) if (pi[i] != INF)
                for (int to : ed[i]) if (cap[i][to])
                    if ((v = pi[i] + cost[i][to]) < pi[to])
                        pi[to] = v, ch = 1;
        assert(it >= 0); // negative cost cycle
    }
};

bool dfs(int a, int L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
    if (A[a] != L) return 0;
    A[a] = -1;
    for (int b : g[a]) if (B[b] == L + 1) {
            B[b] = 0;
            if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
                return btoa[b] = a, 1;
        }
    return 0;
}
int hopcroftKarp(vector<vi>& g, vi& btoa) {
    int res = 0;
    vi A(g.size()), B(btoa.size()), cur, next;
    for (;;) {
        fill(all(A), 0);
        fill(all(B), 0);
        cur.clear();
        for (int a : btoa) if(a != -1) A[a] = -1;
        rep(a,sz(g)) if(A[a] == 0) cur.push_back(a);
        for (int lay = 1;; lay++) {
            bool islast = 0;
            next.clear();
            for (int a : cur) for (int b : g[a]) {
                    if (btoa[b] == -1) {
                        B[b] = lay;
                        islast = 1;
                    }
                    else if (btoa[b] != a && !B[b]) {
                        B[b] = lay;
                        next.push_back(btoa[b]);
                    }
                }
            if (islast) break;
            if (next.empty()) return res;
            for (int a : next) A[a] = lay;
            cur.swap(next);
        }
        rep(a,sz(g))
        res += dfs(a, 0, g, btoa, A, B);
    }
}

struct TwoSat {
    int N;
    vector<vi> gr;
    vi values; // 0 = false , 1 = true
    TwoSat(int n = 0) : N(n), gr(2*n) {}
    int addVar() { // ( optional )
        gr.emplace_back();
        gr.emplace_back();
        return N++;
    }
    void either(int f, int j) {
        f = max(2*f, -1-2*f);
        j = max(2*j, -1-2*j);
        gr[f].push_back(j^1);
        gr[j].push_back(f^1);
    }
    void setValue(int x) { either(x, x); }
    void atMostOne(const vi& li) { // ( optional )
        if (sz(li) <= 1) return;
        int cur = ~li[0];
        for (int i = 2; i < sz(li); i++) {
            int next = addVar();
            either(cur, ~li[i]);
            either(cur, next);
            either(~li[i], next);
            cur = ~next;
        }
        either(cur, ~li[1]);
    }
    vi val, comp, z; int time = 0;
    int dfs(int i) {
        int low = val[i] = ++time, x; z.push_back(i);
        for(int e : gr[i]) if (!comp[e])
                low = min(low, val[e] ?: dfs(e));
        if (low == val[i]) do {
                x = z.back(); z.pop_back();
                comp[x] = low;
                if (values[x>>1] == -1)
                    values[x>>1] = x&1;
            } while (x != i);
        return val[i] = low;
    }
    bool solve() {
        values.assign(N, -1);
        val.assign(2*N, 0); comp = val;
        rep(i,2*N) if (!comp[i]) dfs(i);
        rep(i,N) if (comp[2*i] == comp[2*i+1]) return 0;
        return 1;
    }
};