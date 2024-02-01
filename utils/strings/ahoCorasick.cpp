#include "../macros.h"

// Untested
struct AhoCorasick {
    enum {sigma = 26, alpha = 'a'};
    struct Node {
        array<int,sigma> next{0};
        int prev = 0, count = 0, end = -1;
        // All optional but prev depends on end. Just delete all lines that mention the removed var.
        // count -> number of matches ending at c
        // end -> index of longest pattern ending at c
        // prev -> index of next node with match (for enumerating all matches)
    };
    vector<Node> t;

    int& f(int v, char c, bool sub = 1) { return t[v].next[c - alpha * sub]; }

    explicit AhoCorasick(const vector<string>& p) : t(transform_reduce(all(p), 1, plus<>(), [] (const string& x) { return size(x); })) {
        for (int i = 1, j = 0; const string& s : p) {
            int v = 0;
            for (auto c : s)
                v = f(v, c) ?: f(v, c) = i++;
            t[v].count++;
            t[v].end = j++;
        }
        for (queue<pair<int,int>> q{{{0, 0}}}; !q.empty(); q.pop()) {
            auto [v, link] = q.front();
            rep(c, sigma)
                if (!f(v, c, 0))
                    f(v, c, 0) = f(link, c, 0);
                else
                    q.emplace(f(v, c, 0), v ? f(link, c, 0) : 0);
            t[v].count += t[link].count;
            t[v].prev = t[link].end == -1 ? t[link].prev : link;
        }
    }

    // Returns states traversed in automaton
    vector<int> match(const string& s, int v) {
        vector<int> ans;
        for (char c : s)
            ans.push_back(v = f(v, c));
        return ans;
    }

    // Pass in state-vector obtained from match.
    num count(const vector<int>& a) {
        return transform_reduce(all(a), 0ll, plus<>(), [&] (int v) { return t[v].count; });
    }

    vector<int> longest(const vector<int>& a) {
        vector<int> b(size(a));
        transform(all(a), begin(b), [&] (int v) { return t[v].end; });
        return b;
    }

    Table<int> allMatches(const vector<int>& a) {
        Table<int> b;
        for (int v : a) {
            b.emplace_back();
            do {
                if (t[v].end != -1)
                    b.back().push_back(t[v].end);
            } while (v = t[v].prev);
        }
        return b;
    }
};