#include "../macros.h"

struct Trie {
	// Alphabet size and first character
	constexpr static num sigma = 26, alpha = 'a';
	struct Node {
		seq next;
		bool end;
		Node() : next(sigma, -1), end{false} {}
	};
	vector<Node> a{1};

	void insert(const auto& s) {
		num node = 0;
		for (auto c : s) {
			c -= alpha;
			assert(0 <= c && c < sigma);
			if (a[node].next[c] == -1)
				a[node].next[c] = ssize(a),
						a.emplace_back();
			node = a[node].next[c];
		}
		a[node].end = true;
	}
};