#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include "../utils/data structures/SegmentTree.cpp"
#include "../utils/types/mint.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<array<mint,2>> a(n);
    cin >> a;
    SegmentTree<array<mint,2>,[](auto x, auto y) { return array{x[0] * y[0], y[0] * x[1] + y[1]}; }> st(a);
    while (q--) {
        int x, y, z, w;
        cin >> x >> y >> z >> w;
        if (x) {
            auto [ai, bi] = st.query(y, z);
            cout << ai * w + bi << '\n';
        }
        else
            st.update(y, {z, w});
    }
}
