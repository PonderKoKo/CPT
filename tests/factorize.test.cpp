#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include "../utils/numerical/factorize.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q;
    cin >> q;
    while (q--) {
        num n;
        cin >> n;
        auto a = factorize(n);
        cout, size(a), a, '\n';
    }
}
