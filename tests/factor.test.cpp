#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include "../utils/numerical/factor.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q;
    cin >> q;
    while (q--) {
        num n;
        cin >> n;
        auto a = factor(n);
        cout, size(a), a, '\n';
    }
}
