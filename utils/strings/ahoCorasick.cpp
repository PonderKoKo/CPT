#include "../macros.h"

template<int sigma = 26, int alpha = 'a'>
struct AhoCorasick {
    struct Node {
        int next[sigma]{}, count = 0, longest = -1, shorter = 0;
    };
    vector<Node> t{1};
    int& f(int v, int c) { return t[v].next[c - alpha]; }
    AhoCorasick(auto&& p) {
        rep(i, size(p)) {
            int v = 0;
            for (int c : p[i])
                v = f(v, c) ?: f(v, c) = (t.emplace_back(), size(t) - 1);
            t[v].count++;
            t[v].longest = i;
        }
        for (queue<pair<int,int>> q{{{0, 0}}}; !empty(q); q.pop()) {
            auto [v, l] = q.front();
            for (int c = alpha; c < alpha + sigma; c++)
                if (f(v, c))
                    q.emplace(f(v, c), v ? f(l, c) : 0);
                else
                    f(v, c) = f(l, c);
            t[v].count += t[l].count;
            if (t[v].longest < 0)
                t[v].longest = t[l].longest, t[v].shorter = t[l].shorter;
            else
                t[v].shorter = l;
        }
    }
};
