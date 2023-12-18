#include "../macros.h"

template<typename T, typename U>
vector<U> mo(vector<pair<int,int>> q, const vector<T>& a) {
    int l = 0, r = 0, block = 350;
    auto add = [&] (int i, [[maybe_unused]] bool right) {

    };
    auto del = [&] (int i, [[maybe_unused]] bool right) {

    };
    auto calc = [&] () -> U {

    };
    vector<int> o(size(q));
    vector<U> res(size(q));
#define Order(x) par(x.first / block, x.second ^ -(x.first / block & 1))
    iota(all(o), 0);
    sort(all(o), [&](int s, int t){ return Order(q[s]) < Order(q[t]); });
    for (int i : o) {
        par p = q[i];
        while (l > p.first) add(--l, false);
        while (r < p.second) add(r++, true);
        while (l < p.first) del(l++, false);
        while (r > p.second) del(--r, true);
        res[i] = calc();
    }
    return res;
}