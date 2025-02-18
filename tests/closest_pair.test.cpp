#define PROBLEM "https://judge.yosupo.jp/problem/closest_pair"

#include "../utils/geometry/closest_pair.cpp"

auto solve() {
    int n;
    cin >> n;
    vector<c> a(n);
    cin >> a;
    auto [p, q] = closest_pair(a);
    int i = find(all(a), p) - begin(a), j = find((p == q ? i + 1 : 0) + all(a), q) - begin(a);
    return pair{i, j};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--)
        cout, solve(), '\n';
}
