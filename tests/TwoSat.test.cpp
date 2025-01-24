#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"

#include "../utils/graph/TwoSat.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    int n, m;
    cin >> s >> s >> n >> m;
    TwoSat ts(n);
    rep(i, m) {
        int x, y, z;
        cin >> x >> y >> z;
        ts.either(x - (x > 0), y - (y > 0));
    }
    if (!ts.solve())
        cout << "s UNSATISFIABLE\n";
    else {
        cout << "s SATISFIABLE\nv ";
        rep(i, n) cout << (ts.a[i] ? (i + 1) : -i - 1) << ' ';
        cout << "0\n";
    }
}
