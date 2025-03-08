#include "../macros.h"

struct Rollback : vector<pair<int*,int>> {
    void save(auto& x) { emplace_back(&x, x); }
    void restore(int t) {
        while (t < size())
            *back().first = back().second, pop_back();
    }
};
// Can't template this to T*,T because that requires this->s everywhere.
