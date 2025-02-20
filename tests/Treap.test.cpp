#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set/?Treap"

#include "../utils/data structures/Treap.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    seq init(n);
    cin >> init;
    int treap = transform_reduce(all(init), 0, join, node<num>);
    while (q--) {
        num t, x;
        cin >> t >> x;
        if (t <= 1) {
            auto [a, _, b] = extract<0>(treap, x, x + 1);
            treap = t ? join(a, b) : join(join(a, node(x)), b);
        } else if (t == 2) {
            auto [a, b, c] = extract<1>(treap, x - 1, x);
            cout << (b ? v[b].x : -1) << '\n';
            treap = join(join(a, b), c);
        } else if (t == 3) {
            auto [a, b] = split<0>(treap, x + 1);
            cout << v[a].s << '\n';
            treap = join(a, b);
        } else if (t == 4) {
            auto [a, b] = split<0>(treap, x + 1);
            auto [c, d] = split<1>(a, v[a].s - 1);
            cout << (d ? v[d].x : -1) << '\n';
            treap = join(join(c, d), b);
        } else {
            auto [a, b] = split<0>(treap, x);
            auto [c, d] = split<1>(b, 1);
            cout << (c ? v[c].x : -1) << '\n';
            treap = join(join(a, c), d);
        }
    }
}
