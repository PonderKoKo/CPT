#include "../macros.h"

struct Node {
    num x; // Value-Type
    num min = 1e18; // Aggregates with default for null node
    int l = 0, r = 0, s = 0, p = rng();
};
vector<Node> v(1); // Consider calling reserve
void update(Node& u) {
    u.s = 1 + v[u.l].s + v[u.r].s;
    u.min = min({u.x, v[u.l].min, v[u.r].min});
}
int node(auto x) {
    return update(v.emplace_back(x)), size(v) - 1;
}
#define nx
// persistent: #define nx(i) node(v[i])

int join(int l, int r) {
    if (!l || !r) return l ^ r;
    int c;
    if (v[l].p < v[r].p)
        v[c = nx(l)].r = join(v[l].r, r);
    else
        v[c = nx(r)].l = join(l, v[r].l);
    update(v[c]);
    return c;
}

pair<int,int> split(int i, int key) { // (num key)
    if (!i) return {0, 0};
    if (v[v[i = nx(i)].l].s < key) { // (v[i].x < key)
        auto [rl, rr] = split(v[i].r, key - v[v[i].l].s - 1); // (key)
        v[i].r = rl;
        update(v[i]);
        return {i, rr};
    } else {
        auto [ll, lr] = split(v[i].l, key);
        v[i].l = lr;
        update(v[i]);
        return {ll, i};
    }
}
#undef nx
