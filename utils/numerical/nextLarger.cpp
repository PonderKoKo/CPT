#include "../macros.h"

/* Stack trick for next larger element
 * Complexity O(n)
 * Works for less, greater, less_equal, greater_equal, not_equal_to
 * For each i, ans[i] is the index of the (next ? smallest j > i : biggest j < i), such that c(i, j) is true.
 */
template<bool next, auto c>
seq next_larger(const seq& a) {
	seq ans(size(a), next ? ssize(a) : -1);
	stack<num> st;
	rep(j, ssize(a)) {
		num i = next ? j : ssize(a) - j - 1;
		while (!st.empty() && c(a[st.top()], a[i]))
			ans[st.top()] = i, st.pop();
		st.push(i);
	}
	return ans;
}

// Untested alternate implementation
auto nl(const auto& a, auto c = greater<>{}, bool next = true) {
	int n = size(a);
	vector<int> b(n);
	rep(i, n) {
		int j = next ? n - i - 1 : i, k = j + (next ?: -1);
		while (0 <= k && k < n && !c(a[j], a[k]))
			k = b[k];
		b[j] = k;
	}
	return b;
}