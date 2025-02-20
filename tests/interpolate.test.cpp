#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_1_A"

#include "../utils/numerical/interpolate.cpp"

int main() {
    rep(p, 100) {
        mint ans = 0;
        rep(n, 10000) {
            assert(power_sum(p, n) == ans);
            ans += mint(n) ^ p;
        }
    }
    cout << "Hello World\n";
}
