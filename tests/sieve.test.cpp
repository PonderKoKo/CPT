#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include "../utils/numerical/sieve.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, a, b;
    cin >> n >> a >> b;
    vector<int> p = sieve(n + 1).first, ans;
    for (int i = b; i < size(p); i += a)
        ans.push_back(p[i]);
    cout, size(p), size(ans), '\n', ans;
}
