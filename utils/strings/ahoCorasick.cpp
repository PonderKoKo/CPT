#include "../macros.h"
template<typename T = char, int sigma = 26, T alpha = 'a'>
struct AhoCorasick {
    struct Node {
        array<int,sigma> next{0};
        int count = 0, longest = -1;
    };
    vector<Node> t;

    int& f(int v, int c) { return t[v].next[c - alpha]; }

    AhoCorasick(const Table<T>& p) : t(1) {
        rep(i, ssize(p)) {
            int v = 0;
            for (auto c : p[i])
                v = f(v, c) ?: f(v, c) = (t.emplace_back(), size(t) - 1);
            t[v].count++;
            t[v].longest = i;
        }
        for (queue<pair<int,int>> q{{{0, 0}}}; !q.empty(); q.pop()) {
            auto [v, link] = q.front();
            for (auto c = alpha; c < alpha + sigma; c++)
                if (f(v, c))
                    q.emplace(f(v, c), v ? f(link, c) : 0);
                else
                    f(v, c) = f(link, c);
            t[v].count += t[link].count;
            if (t[v].longest == -1) t[v].longest = t[link].longest;
        }
    }

    vector<int> match(const vector<T>& s, int v = 0) {
        vector<int> ans;
        for (auto c : s)
            ans.push_back(v = f(v, c));
        return ans;
    }
};

/*
struct AhoCorasick {
    enum {sigma = 26, alpha = 'a'};
    struct Node {
        array<int,sigma> next{0};
        int count = 0, longest = -1;
        // vector<int> matches;
        // All optional, delete unneeded lines.
        // count -> number of matches ending at c
        // end -> index of longest pattern ending at c
        // matches -> indices of all patterns ending at c. At most (Sum P)^3/2 if no duplicates.
    };
    vector<Node> t;

    int& f(int v, char c) { return t[v].next[c - alpha]; }

    explicit AhoCorasick(const vector<string>& p) : t(1) {
        rep(i, ssize(p)) {
            int v = 0;
            for (char c : p[i])
                v = f(v, c) ?: f(v, c) = (t.emplace_back(), size(t) - 1);
            t[v].count++;
            t[v].longest = i;
            // t[v].matches.push_back(i);
        }
        for (queue<pair<int,int>> q{{{0, 0}}}; !q.empty(); q.pop()) {
            auto [v, link] = q.front();
            for (char c = alpha; c < alpha + sigma; c++)
                if (f(v, c))
                    q.emplace(f(v, c), v ? f(link, c) : 0);
                else
                    f(v, c) = f(link, c);
            t[v].count += t[link].count;
            if (t[v].longest == -1) t[v].longest = t[link].longest;
            // t[v].matches.insert(end(t[v].matches), all(t[link].matches));
        }
    }

    // Returns states traversed in automaton
    vector<int> match(const string& s, int v = 0) {
        vector<int> ans;
        for (char c : s)
            ans.push_back(v = f(v, c));
        return ans;
    }
};*/