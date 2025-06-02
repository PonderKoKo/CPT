#define PROBLEM "https://cses.fi/problemset/task/1684/"

#include "../utils/graph/TwoSat.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    TwoSat ts(m);
    while (n--) {
        char c, d;
        int x, y;
        cin >> c >> x >> d >> y;
        --x, --y;
        ts.either(c == '+' ? x : ~x, d == '+' ? y : ~y);
    }
    if (ts.solve()) rep(i, m) cout << "-+"[ts.a[i]] << ' ';
    else cout << "IMPOSSIBLE";
}
