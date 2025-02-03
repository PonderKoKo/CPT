#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "../utils/data structures/UnionFind.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    UnionFind uf(n);
    while (q--) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t)
            cout << (uf.find(u) == uf.find(v)) << '\n';
        else
            uf.join(u, v);
    }
}
