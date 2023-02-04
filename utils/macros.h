#ifndef EXAMPLE_CPP_MACROS_H
#define EXAMPLE_CPP_MACROS_H
#include <bits/stdc++.h>

#define rep(a, b) for (num a = 0; a < (b); ++a)
#define all(a) (a).begin(), (a).end()
#define many int t; cin >> t; while (t--)
#define yesno cout << (solve() ? "YES" : "NO") << '\n'
#define print cout << solve() << '\n'
#define call solve()

#define sum(a) accumulate(all(a), 0ll)
#define meq(a,b) a = max(a, b)
#define reps(a,s,b) for (num a = s; a < (b); ++a)
#define sz(a) static_cast<num>(a.size())


using namespace std;

using num = long long int;
using seq = vector<num>;
using bits = vector<bool>;
using par = pair<num,num>;
using Graph = vector<vector<num>>;
template<typename T> ostream& operator<<(ostream& os, const vector<T>& v) { for (auto& e : v) os << e << ' '; return os; }
template<typename T> istream& operator>>(istream& is, vector<T>& v) { for (auto& e : v) is >> e; return is; }
template<typename T, typename U> ostream& operator<<(ostream& os, const pair<T,U>& p) { return os << p.first << ' ' << p.second; }
template<typename T, typename U> istream& operator>>(istream& is, pair<T,U>& p) { return is >> p.first >> p.second; }
#endif
