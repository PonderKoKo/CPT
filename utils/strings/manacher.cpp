#include "../macros.h"

/* Manacher's Algorithm for all substring palindromes
 * Complexity O(n)
 * returns [even, odd]; for each position the longest half length of a palindrome around that position
 * For evens index i refers to the gap before index i
 */
pair<seq,seq> manacher(const string& s) {
	pair<seq,seq> ans{seq(size(s) + 1), seq(size(s))};
	rep(z,2) {
		seq& x = z ? ans.first : ans.second;
		num l{0}, r{0};
		rep(i, ssize(s)) {
			num t = r - i + z;
			if (i < r)
				x[i] = min(t, x[l+t]);
			num a{i - x[i]}, b{i + x[i] - z};
			while (a >= 1 && b + 1 < ssize(s) && s[a - 1] == s[b + 1])
				x[i]++, a--, b++;
			if (b > r)
				l = a, r = b;
		}
	}
	return ans;
}