#include "bits/stdc++.h"
#ifndef DEBUG
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
#endif
#define many int t; cin >> t; while (t--)
#define yesno cout << (solve() ? "YES" : "NO") << '\n'
#define print cout << solve() << '\n'
#define call solve()
#define rep(a, b) for (num a = 0; a < (b); ++a)
#define all(a) (a).begin(), (a).end()
using namespace std;
using num = long long int;
using seq = vector<num>;
using bits = vector<char>;
using par = pair<num,num>;
using Graph = vector<vector<num>>;
template<typename T> using Table = vector<vector<T>>;
template<typename T, typename U> ostream& operator<<(ostream& os, const pair<T,U>& p) { return os << p.first << ' ' << p.second; }
template<typename T, typename U> istream& operator>>(istream& is, pair<T,U>& p) { return is >> p.first >> p.second; }
template<typename T> ostream& operator<<(ostream& os, const vector<T>& v) { for (auto& e : v) os << e << ' '; return os; }
template<typename T> istream& operator>>(istream& is, vector<T>& v) { for (auto& e : v) is >> e; return is; }
template<typename T> num sign(T x) { return (T(0) < x) - (x < T(0)); }
constexpr num operator ""_e(unsigned long long x) { num ans = 1; rep(i, static_cast<num>(x)) ans *= 10; return ans; }

void solve() {

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	call;
	return 0;
}
