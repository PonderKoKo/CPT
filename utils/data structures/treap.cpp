#include "../macros.h"

struct Node {
    num x;
    num sum = 0; // Specify neutral aggregates (for null node).
    int l = 0, r = 0, s = 0, p = rng();
    void update();
};
vector<Node> v(1);
void Node::update() {
    s = 1 + v[l].s + v[r].s;
    sum = x + v[l].sum + v[r].sum; // Update aggregates
}
int node(auto x) { // Consider adding auto... and x... below if you want multiple values.
    return v.emplace_back(x).update(), size(v) - 1;
}
#define op(i, a, b) v[i /* = node(v[i]) */].a = b, v[i].update(), i // Uncomment for persistence
int join(int l, int r) {
    return l && r ? v[l].p < v[r].p ?
                    (op(l, r, join(v[l].r, r))) :
                    (op(r, l, join(l, v[r].l))) :
           l ^ r;
}
template<bool by_size>
array<int,2> split(int i, auto b) {
    if (!i) return {0, 0};
    bool q = (by_size ? v[v[i].l].s : v[i].x) < b;
    if (by_size && q) b += ~v[v[i].l].s;
    auto a = split<by_size>(q[&v[i].l], b);
    a[!q] = (q[& op(i, l], a[!q]));
    return a;
}

void each(int i, auto&& f) { if (i) each(v[i].l, f), f(i), each(v[i].r, f); }
// transform_reduce(all(a), 0, join, node<ll>) to construct a treap with values from a.

int unite(int l, int r) { // union of separate sorted treaps. the double op is kind of wasteful for persistence.
    if (!l || !r) return l ^ r;
    if (v[l].p > v[r].p) swap(l, r);
    auto [a, b] = split<0>(r, v[l].x);
    op(l, l, unite(v[l].l, a));
    op(l, r, unite(v[l].r, b));
    return l;
}
#undef op

template<bool by_size>
array<int,3> extract(int i, auto l, auto r) {
    auto [x, c] = split<by_size>(i, r);
    auto [a, b] = split<by_size>(x, l);
    return {a, b, c};
}
