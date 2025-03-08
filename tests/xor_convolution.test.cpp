#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_xor_convolution"

#include "../utils/numerical/convolutions.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<mint> a(1 << n), b(a);
    cin >> a >> b;
    cout << convolve(XOR, a, b);
}
