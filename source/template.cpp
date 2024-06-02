#include <bits/stdc++.h>
namespace std {
	template<typename... Args> ostream& operator<<(ostream& os, const tuple<Args...>& t) { return apply([&](auto&&... args){ ((os << args << ' '), ...); }, t), os; }
	template<typename... Args> istream& operator>>(istream& is, tuple<Args...>& t) { return apply([&](auto&&... args){ ((is >> args), ...); }, t), is; }
	
	template<typename T> concept rangeio = requires(T x) { requires !convertible_to<T, string>; requires ranges::range<T>; };
	ostream& operator<<(ostream& os, const rangeio auto &v) { for (auto&& e : v) os << e << ' '; return os; }
	istream& operator>>(istream& is, const rangeio auto &v) { for (auto&& e : v) is >> e; return is; }
}
using namespace std;
ostream& operator,(ostream& os, auto&& x) { return os << x << ' '; }
using num = long long;
using ull = unsigned long long;
using seq = vector<num>;
using bits = vector<char>;
template<typename T> using Table = vector<vector<T>>;
#define dbg(a) cerr << (#a) << " = " << (a) << endl
#define rep(a, b) for (num a = 0; a < (b); ++a)
#define all(a) begin(a), end(a)
constexpr num operator ""_e(unsigned long long x) { num ans = 1; rep(i, static_cast<num>(x)) ans *= 10; return ans; }
mt19937 rng(static_cast<unsigned>(chrono::steady_clock::now().time_since_epoch().count()));

auto solve() {
	
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
	// cin >> t;
	while (t--)
		cout, solve(), '\n';
}
