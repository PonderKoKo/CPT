#include "../macros.h"

template<num tl, num tr, auto cmp = less<>{}>
struct LiChaoTree {
    #define m l + (r - l) / 2
    using T = pair<int,num>;
    auto eva(T &y, num x) { return y.first * x + y.second; }
    vector<T> v{{0, 8e18}};
    vector<array<int,2>> c{{0, 0}};
    void add(T a) {
        int u = 0;
        num l = tl, r = tr;
        for(;;) {
            if (cmp(eva(a, m), eva(v[u], m))) swap(a, v[u]);
            if (l + 1 == r) break;
            bool z = cmp(eva(a, l), eva(v[u], l));
            if (!c[u][z]) {
                c[u][z] = size(v);
                v.push_back(a);
                c.emplace_back();
                break;
            }
            (z ? r : l) = m;
            u = c[u][z];
        }
    }
    auto query(num x) {
        int u = 0;
        num l = tl, r = tr;
        auto ans = eva(v[u], x);
        while (u = c[u][((x < m ? r : l) = m) == r])
            ans = min(ans, eva(v[u], x), cmp);
        return ans;
    }
    #undef m
};