#include "../macros.h"

struct TwoSat {
	vector<pair<int,int>> e;
	int n;

	TwoSat(int n) : n(n) {}

	void either(int a, int b) {
		a = max(2 * a, 2 * ~a + 1);
		b = max(2 * b, 2 * ~b + 1);
		e.emplace_back(a, b ^ 1);
		e.emplace_back(b, a ^ 1);
	}

	pair<bool,vector<int>> solve() {
		vector<int> s(2 * n + 1), q(size(e)), ans(n, -1), z;
		for (const auto& [a, b] : e)
			s[a]++;
		partial_sum(all(s), begin(s));
		for (const auto& [a, b] : e)
			q[--s[a]] = b;
		function<bool(int)> dfs = [&] (int u){
			z.push_back(u / 2);
			ans[u / 2] = u % 2;
			for (int v : span(q).subspan(s[u], s[u + 1] - s[u]))
				if (ans[v / 2] == -1 ? dfs(v) : ans[v / 2] != v % 2)
					return true;
			return false;
		};
		rep(i, n) {
			if (ans[i] == -1) {
				z.clear();
				if (dfs(2 * i)) {
					for (int x : z)
						ans[x] = -1;
					if (dfs(2 * i + 1))
						return {};
				}
			}
		}
		return {true, ans};
	}

	void atMostOne(const vector<int>& v) {
		if (size(v) > 1)
			either(~v[0], ~v[1]);
		for (int i = 1, p = v[0]; i + 1 < size(v); i++, p = n++) {
			either(~p, n);
			either(~v[i], n);
			either(~n, ~v[i+1]);
		}
	}

	void force(int a) { either(a, a); }
	void implies(int a, int b) { either(~a, b); }
};

/* kactl style
struct TwoSat {
	vector<pair<int,int>> e;
	int n;

	TwoSat(int n) : n(n) {}

	void either(int a, int b) {
		a = max(2 * a + 1, 2 * ~a);
		b = max(2 * b + 1, 2 * ~b);
		e.emplace_back(a, b ^ 1);
		e.emplace_back(b, a ^ 1);
	}

	pair<bool,vector<int>> solve() {
		vector<int> s(2 * n + 1), q(size(e)), assignment(n, -1), time(2 * n), comp(time);
		stack<int> z;
		for (const auto& [a, b] : e)
			s[a]++;
		partial_sum(all(s), begin(s));
		for (const auto& [a, b] : e)
			q[--s[a]] = b;
		int t{0}, x;
		function<int(int)> dfs = [&] (int u){
			int lo = time[u] = ++t;
			z.push(u);
			for (int v : span{q}.subspan(s[u], s[u + 1] - s[u]))
				if (!comp[v])
					lo = min(lo, time[v] ?: dfs(v));
			if (lo == time[u]) do {
					x = z.top(), z.pop();
					comp[x] = lo;
					assignment[x / 2] = x & 1;
				} while (x != u);
			return time[u] = lo;
		};
		rep(i, 2 * n) {
			if (!comp[i])
				dfs(i);
			if (i & 1 && comp[i] == comp[i^1])
				return {};
		}
		return {true, assignment};
	}

	void atMostOne(const vector<int>& v) {
		if (size(v) > 1)
			either(~v[0], ~v[1]);
		for (int i = 1, p = v[0]; i + 1 < size(v); i++, p = n++) {
			either(~p, n);
			either(~v[i], n);
			either(~n, ~v[i+1]);
		}
	}

	void force(int a) { either(a, a); }
	void implies(int a, int b) { either(~a, b); }
};*/