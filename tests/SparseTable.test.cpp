#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "../utils/data structures/SparseTable.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;
    SparseTable<int,ranges::min> st(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << st.query(l, r) << '\n';
    }
}
