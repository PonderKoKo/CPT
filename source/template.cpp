#include <bits/stdc++.h>
#ifdef DEBUG
#define dbg(z) cerr << #z << " = " << (z) << endl;
#else
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
#define dbg(z) ;
#endif
#define rep(a, b) for (num a = 0; a < (b); ++a)
#define all(a) (a).begin(), (a).end()

using namespace std;
using num = long long int;
using ull = unsigned long long;
using seq = vector<num>;
using bits = vector<char>;
using par = pair<num,num>;
using Graph = vector<vector<num>>;
template<typename T> using Table = vector<vector<T>>;
template<typename T, typename U> ostream& operator<<(ostream& os, const pair<T,U>& p) { return os << p.first << ' ' << p.second; }
template<typename T, typename U> istream& operator>>(istream& is, pair<T,U>& p) { return is >> p.first >> p.second; }
template<typename T> ostream& operator<<(ostream& os, const vector<T>& v) { for (auto& e : v) os << e << ' '; return os; }
template<typename T> istream& operator>>(istream& is, vector<T>& v) { for (auto& e : v) is >> e; return is; }
constexpr num operator ""_e(unsigned long long x) { num ans = 1; rep(i, static_cast<num>(x)) ans *= 10; return ans; }
template<typename T> ostream& operator,(ostream& os, const T& x) { return os << x << ' '; }
mt19937 rng(static_cast<unsigned>(chrono::steady_clock::now().time_since_epoch().count()));

auto solve() {

}

constexpr bool SINGLE{true};
int main() {
#ifdef DEBUG
	cin.exceptions(istream::badbit | istream::failbit);
#else
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#endif
	for (int t = SINGLE ?: *istream_iterator<int>(cin); t--;)
		cout, solve(), '\n';
	return 0;
}
