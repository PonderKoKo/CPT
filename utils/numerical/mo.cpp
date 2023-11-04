#include "../macros.h"


seq mo(vector<par> q, const seq& a) {
    num l = 0, r = 0, block = 350;
    auto add = [&] (num i, [[maybe_unused]] bool right) {

    };
    auto del = [&] (num i, [[maybe_unused]] bool right) {

    };
    auto calc = [&] () -> num {

    };
    seq o(size(q)), res = o;
#define Order(x) par(x.first / block, x.second ^ -(x.first / block & 1))
    iota(all(o), 0);
    sort(all(o), [&](num s, num t){ return Order(q[s]) < Order(q[t]); });
    for (num i : o) {
        par p = q[i];
        while (l > p.first) add(--l, false);
        while (r < p.second) add(r++, true);
        while (l < p.first) del(l++, false);
        while (r > p.second) del(--r, true);
        res[i] = calc();
    }
    return res;
}