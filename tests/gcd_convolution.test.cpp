#define PROBLEM "https://judge.yosupo.jp/problem/gcd_convolution"

#include "../utils/numerical/convolutions.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<mint> a(n), b(a);
    cin >> a >> b; a.insert(begin(a), 0), b.insert(begin(b), 0);
    auto c = convolve(GCD, a, b);
    c.erase(begin(c));
    cout << c;
}
