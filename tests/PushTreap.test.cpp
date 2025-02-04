#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"

#include "../utils/data structures/PushTreap.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<mint> init(n);
    cin >> init;
    int treap = transform_reduce(all(init), 0, join, node<mint>);
    while (q--) {
        int t;
        cin >> t;
        switch (t) {
            case 0: {
                num i; mint x;
                cin >> i >> x;
                auto [a, b] = split<1>(treap, i);
                treap = join(join(a, node(x)), b);
                break;
            }
            case 1: {
                num i;
                cin >> i;
                auto [a, _, b] = extract<1>(treap, i, i + 1);
                treap = join(a, b);
                break;
            }
            case 2: {
                num l, r;
                cin >> l >> r;
                auto [a, b, c] = extract<1>(treap, l, r);
                v[b].rev ^= 1;
                treap = join(join(a, b), c);
                break;
            }
            case 3: {
                num l, r; mint b, c;
                cin >> l >> r >> b >> c;
                auto [x, y, z] = extract<1>(treap, l, r);
                v[y].a = b, v[y].b = c;
                treap = join(join(x, y), z);
                break;
            }
            case 4: {
                num l, r;
                cin >> l >> r;
                auto [a, b, c] = extract<1>(treap, l, r);
                cout << v[b].sum << '\n';
                treap = join(join(a, b), c);
            }
        }
    }
}
