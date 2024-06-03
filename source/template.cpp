#include <bits/stdc++.h>
namespace std {
	ostream& operator,(ostream& os, auto&& x) { return os << x << ' '; }
	template<typename T> concept tupleio = requires(T x) { get<0>(x); };
	ostream& operator<<(ostream& os, const tupleio auto& t) { return apply([&] (auto&&... args) { (os , ... , args); }, t), os; }
	istream& operator>>(istream& is, tupleio auto& t) { return apply([&] (auto&&... args) { (is >> ... >> args); }, t), is; }
	template<typename T> concept rangeio = ranges::range<T> && !convertible_to<T, string>;
	ostream& operator<<(ostream& os, const rangeio auto &v) { for (auto&& e : v) os, e; return os; }
	istream& operator>>(istream& is, rangeio auto &v) { for (auto&& e : v) is >> e; return is; }
}
using namespace std;
using num = long long;
using ull = unsigned long long;
using seq = vector<num>;
template<typename T> using Table = vector<vector<T>>;
#define dbg(a) cerr << (#a) << " = " << (a) << endl
#define rep(a, b) for (num a = 0; a < (b); ++a)
#define all(a) begin(a), end(a)
mt19937 rng(static_cast<unsigned>(chrono::steady_clock::now().time_since_epoch().count()));

auto solve() {
	seq a(5);
	cin >> a;
	tuple<int,bool,char> c;
	pair<int,int> p;
	cout << c;
	cout << p;
	cin >> p;
	cin >> c;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
	// cin >> t;
	while (t--)
		cout, solve(), '\n';
}
