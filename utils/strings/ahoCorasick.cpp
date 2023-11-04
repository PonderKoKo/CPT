#include "../macros.h"

struct AhoCorasick {
#define nx(v, c) trie[v].next[c]
    static constexpr num sigma = 26, alpha = 'a';
    struct Node {
        array<num,sigma> next{0};
        num count = 0;
    };
    vector<Node> trie;

    AhoCorasick(const vector<string>& patterns) : trie(1) {
        for (const string& p : patterns) {
            num v = 0;
            for (num c : p) {
                c -= alpha;
                if (!nx(v, c))
                    nx(v, c) = size(trie),
                            trie.emplace_back();
                v = nx(v, c);
            }
            trie[v].count++;
        }
        queue<tuple<num,num,num,num>> q;
        for (q.emplace(0, 0, 0, 0); !q.empty(); q.pop()) {
            auto [v, p, plink, pchar] = q.front();
            num link = p == 0 ? 0 : nx(plink, pchar);
            rep(c, sigma)
            if (!nx(v, c))
                nx(v, c) = nx(link, c);
            else
                q.emplace(nx(v, c), v, link, c);
            trie[v].count += trie[link].count;
        }
    }

    num match(const string& s, num& v) const {
        num ans = 0;
        for (num c : s) {
            c -= alpha;
            v = nx(v, c);
            ans += trie[v].count;
        }
        return ans;
    }

    num match(const string& s) const {
        num v = 0;
        return match(s, v);
    }
#undef nx
};