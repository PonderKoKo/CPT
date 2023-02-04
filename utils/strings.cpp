#include "macros.h"

class RollingHash {
    static constexpr num n = 3;
    static constexpr num base = 131;
    static constexpr array<num, n> modules{998244353, 1000000009, 1000000321};
    static array<seq, n> powers;
    array<num, n> hashes{0};
    num length;

    static num power(num m, num x) {
        if (x >= 0) {
            if (x <= 1'000'000) {
                while (powers[m].size() <= x)
                    powers[m].push_back(powers[m].back() * base % modules[m]);
                return powers[m][x];
            }
            num p = 1, b = modules[m];
            while (x > 0) {
                if (x & 1)
                    p *= b;
                b *= b;
                x >>= 1;
            }
            return p;
        } else {
            return power(m, -x - 1);
        }
    }

    void normalize() {
        rep(m, n) {
            hashes[m] %= modules[m];
            if (hashes[m] < 0)
                hashes[m] += modules[m];
        }
    }
public:
    RollingHash() = default;
    RollingHash(const seq& s) : length(size(s)) {
        rep(m, n)
            rep(i, ssize(s))
                hashes[m] += s[i] * power(m, i);
        normalize();
    }
    RollingHash(const string& s) : RollingHash(seq{all(s)}) {}
    RollingHash(num x) : RollingHash(seq{x}) {}

    RollingHash replace(num i, num prev, num next) const {
        RollingHash res(*this);
        rep(m, n)
            res.hashes[m] += (next - prev) * power(m, i);
        res.normalize();
        return res;
    }

    RollingHash& operator+=(const RollingHash& other) {
        rep(m, n)
            hashes[m] += power(m, length) * other.hashes[m];
        normalize();
        length += other.length;
        return *this;
    }

    // Assumes other is a suffix of this
    RollingHash& operator-=(const RollingHash& other) {
        length -= other.length;
        rep(m, n)
            hashes[m] -= power(m, length) * other.hashes[m];
        normalize();
        return *this;
    }

    // Assumes other is a prefix of this
    RollingHash& operator/=(const RollingHash& other) {
        length -= other.length;
        rep(m, n)
            hashes[m] -= other.hashes[m], hashes[m] *= power(m, -other.length);
        normalize();
        return *this;
    }

    struct hashify {
        num operator() (RollingHash r) const {
            return accumulate(all(r.hashes), 0ll, [](num a, num b) { return a ^ b; });
        }
    };

    friend RollingHash operator-(RollingHash lhs, const RollingHash& rhs) { return lhs -= rhs; }
    friend RollingHash operator+(RollingHash lhs, const RollingHash& rhs) { return lhs += rhs; }
    friend RollingHash operator/(RollingHash lhs, const RollingHash& rhs) { return lhs /= rhs; }
    auto operator<=>(const RollingHash&) const = default;
};
array<seq,RollingHash::n> RollingHash::powers{seq{1}, seq{1}, seq{1}};

class MultisetHash {
    static constexpr num n = 3;
    static constexpr num base = 131;
    static constexpr array<num, n> modules{998244353, 1000000009, 1000000321};
    array<num, n> hashes;
    num length;
public:
    MultisetHash() : hashes{1,1,1}, length(0) {}
    template<typename T>
    MultisetHash(const T& s) : length(size(s)) {
        rep(m, n)
            hashes[m] = accumulate(all(s), 1ll, [&](num a, num c) {
                return (a * (base + c)) % modules[m];
            });
    }

    MultisetHash& operator+=(const MultisetHash& other) {
        rep(m, n) {
            hashes[m] *= other.hashes[m];
            hashes[m] %= modules[m];
        }
        length += other.length;
        return *this;
    }

    MultisetHash& operator+=(num c) {
        rep(m, n) {
            hashes[m] *= (base + c);
            hashes[m] %= modules[m];
        }
        length++;
        return *this;
    }

    friend MultisetHash operator+(MultisetHash l, const MultisetHash& r) { return l += r; }
    friend MultisetHash operator+(MultisetHash l, num r) { return l += r; }

    auto operator<=>(const MultisetHash&) const = default;
};

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

    num match(const string& s) {
        num ans = 0;
        for (num v = 0; num c : s) {
            c -= alpha;
            v = nx(v, c);
            ans += trie[v].count;
        }
        return ans;
    }
#undef nx
};

pair<seq,Graph> cyclic_shifts(const string& s) {
    num n = ssize(s), logn = 64 - countl_zero(static_cast<unsigned long long>(n));
    seq order(n);
    iota(all(order), 0);
    sort(all(order), [&] (num i, num j) { return s[i] < s[j]; });
    Graph classes(logn+1, seq(n, 0));
    rep(i, n-1)
        classes[0][order[i+1]] = classes[0][order[i]] + (s[order[i]] != s[order[i+1]]);
    rep(k, logn) {
        seq second(order), count(n);
        for (num& x : second)
            x -= 1 << k, x += (x < 0) * n;
        reverse(all(second));
        for (num& x : classes[k])
            count[x]++;
        partial_sum(all(count), begin(count));
        for (num& x : second)
            order[--count[classes[k][x]]] = x;
        rep(i, n-1)
            classes[k+1][order[i+1]] = classes[k+1][order[i]] +
                                       (classes[k][order[i]] != classes[k][order[i+1]] ||
                                        classes[k][(order[i] + (1 << k)) % n] != classes[k][(order[i+1] + (1 << k)) % n]);
    }
    return make_pair(order, classes);
}

seq lcp_array(const string& s, const seq& order, const Graph& classes) {
    num n = ssize(s), logn = ssize(classes) - 1;
    seq lcp(n-1, 0);
    rep(i, n-1)
        for (num k = logn; k >= 0; k--)
            if (classes[k][(order[i]+lcp[i]) % n] == classes[k][(order[i+1]+lcp[i]) % n])
                lcp[i] += 1 << k;
    return lcp;
}

seq p_function(string s) {
    num n = ssize(s);
    seq p(n);
    for (num i = 1; i < n; i++) {
        num j = p[i-1];
        while (j > 0 && s[i] != s[j])
            j = p[j-1];
        if (s[i] == s[j])
            j++;
        p[i] = j;
    }
    return p;
}

seq z_function(string s) {
    num n = ssize(s);
    seq z(n);
    for (num i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}