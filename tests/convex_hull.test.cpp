#define PROBLEM "https://judge.yosupo.jp/problem/static_convex_hull"

#include "../utils/geometry/convex_hull.cpp"

auto solve() {
    int n;
    cin >> n;
    vector<c> a(n);
    cin >> a;
    auto p = convex_hull(a);
    for (cout << size(p) << '\n'; auto x : p)
        cout << x << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--)
        cout, solve(), '\n';
}
