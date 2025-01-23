#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../utils/numerical/ntt.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<mint> a(n), b(m);
    cin >> a >> b;
    cout << convolve(a, b);
}