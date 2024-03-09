#include "../macros.h"

struct Rollback {
    vector<tuple<void*,void*,int>> r;
    int time() const { return size(r); }
    template<typename T> void save(T* x) { r.emplace_back(x, new T(*x), sizeof(T)); }
    void rollback(int t) {
        while (ssize(r) > t) {
            auto [a, b, c] = r.back();
            memcpy(a, b, c);
            r.pop_back();
        }
    }
};