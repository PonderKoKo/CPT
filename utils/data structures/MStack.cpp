#include "../macros.h"

// Untested. Stack, Queue and Deque with O(1) everything and max/min queries.
#define m min
#define neutral 18_e
template<typename T>
struct mstack {
    stack<T> st, agg{{neutral}};
    void push(const T& x) { st.push(x), agg.push(m(agg.top(), x)); }
    void pop() { st.pop(), agg.pop(); }
    T getm() const { return agg.top(); }
    T top() const { return st.top(); }
    int size() const { return st.size(); }
};

template<typename T>
struct mqueue {
    stack<T> in;
    mstack<T> out;
    T in_agg{{neutral}};
    void rebalance() {
        if (!out.size())
            for (in_agg = neutral; !empty(in); in.pop())
                out.push(in.top());
    }
    void push(const T& x) { in.push(x), in_agg = m(in_agg, x); }
    void pop() { rebalance(), out.pop(); }
    T getm() const { return m(out.getm(), in_agg); }
    T front() const { return rebalance(), out.top(); }
    int size() const { return in.size() + out.size(); }
};

template<typename T>
struct mdeque {
    mstack<T> l, r;
    void rebalance() {
        auto& s = l, t = r;
        if (empty(l))
            s = r, t = l;
        else if (!empty(r))
            return;
        vector<T> u(size(s) / 2);
        rep(i, ssize(u))
            u[i] = s.top(), s.pop();
        for (; !empty(s); s.pop())
            t.push(s.top());
        for (const auto& x : u | views::reverse)
            s.push(x);
    }
    void push_front(const T& x) { l.push(x); }
    void push_back(const T& x) { r.push(x); }
    void pop_front() { rebalance(), l.pop(); }
    void pop_back() { rebalance(), r.pop(); }
    T getm() const { return m(l.getm(), r.getm()); }
    T front() const { return rebalance(), l.top(); }
    T back() const { return rebalance(), r.top(); }
};