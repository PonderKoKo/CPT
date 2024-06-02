#include "../macros.h"

struct Node {
    int l = 0, r = 0, s;
    unsigned p = rng();
    int x, m = x;
    explicit Node(int x, int s = 1) : s{s}, x{x} {}
};
// Consider calling reserve
vector<Node> v{Node(2e9, 0)};
int node(auto x) { return v.emplace_back(x), size(v) - 1; }
// Determines persistency
int nx(int i) { return node(v[i]); }
// int nx(int i) { return i; }

void update(int i) {
    v[i].s = 1 + v[v[i].l].s + v[v[i].r].s;
    v[i].m = min({v[i].x, v[v[i].l].m, v[v[i].r].m});
}

int join(int l, int r) {
    if (!l || !r) return l ^ r;
    int c;
    if (v[l].p < v[r].p)
        v[c = nx(l)].r = join(v[l].r, r);
    else
        v[c = nx(r)].l = join(l, v[r].l);
    update(c);
    return c;
}

pair<int,int> split(int i, int key) {
    if (!i) return {0, 0};
    int ci = nx(i);
    if (1 + v[v[i].l].s <= key) {
        auto [rl, rr] = split(v[i].r, key - v[v[i].l].s - 1);
        v[ci].r = rl;
        update(ci);
        return {ci, rr};
    } else {
        auto [ll, lr] = split(v[i].l, key);
        v[ci].l = lr;
        update(ci);
        return {ll, ci};
    }
}

tuple<int,int,int> extract(int i, int l, int r) {
    auto [remainder, right] = split(i, r);
    auto [left, mid] = split(remainder, l);
    return {left, mid, right};
}