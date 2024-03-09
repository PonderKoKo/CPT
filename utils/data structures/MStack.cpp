#include "../macros.h"

// Unfinished. Stack and Deque with O(1) everything and max/min queries.
template<typename cmp = less<> /* min */, typename T = num>
struct MStack {
    static constexpr T neutral{max(numeric_limits<T>::min(), numeric_limits<T>::max(), cmp{})};
    stack<T> st, agg{{neutral}};
    void push(const T& x) { st.push(x), agg.push(min(agg.top(), x, cmp{})); }
    void pop() { st.pop(), agg.pop(); }
    T getm() const { return agg.top(); }
    T top() const { return st.top(); }
    int size() const { return st.size(); }
};

template<typename cmp = less<> /* min */, typename T = num>
struct MDeque {
    MStack<cmp, T> l, r;
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
    T getm() const { return min(l.getm(), r.getm(), cmp{}); }
    T front() const { return rebalance(), l.top(); }
    T back() const { return rebalance(), r.top(); }
};