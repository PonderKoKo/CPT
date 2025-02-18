#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"

#include "../utils/numerical/is_prime.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q;
    cin >> q;
    while (q--) {
        num n;
        cin >> n;
        cout << (is_prime(n) ? "Yes" : "No") << '\n';
    }
}
