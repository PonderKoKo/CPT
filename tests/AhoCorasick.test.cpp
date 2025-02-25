// #define PROBLEM "https://open.kattis.com/problems/stringmultimatching"

#include "../utils/strings/AhoCorasick.cpp"

auto solve() {
    num n;
    cin >> n;
    cin.ignore();
    vector<string> patterns(n);
    string text;
    for (auto& x : patterns)
        getline(cin, x);
    getline(cin, text);
    AhoCorasick<128,0> ac(patterns);
    Table<int> ans(n);
    for (int v = 0, i = 0; char c : text) {
        v = ac.f(v, c);
        i++;
        for (int u = v; ac.t[u].longest != -1; u = ac.t[u].shorter)
            ans[ac.t[u].longest].push_back(i);
    }
    rep(i, n) {
        rep(j, size(ans[i]))
            cout, ans[i][j] - size(patterns[i]);
        cout << '\n';
    }

}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    while (cin)
        cout, solve(), '\n';
}
