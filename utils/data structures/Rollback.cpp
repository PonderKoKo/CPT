#include "../macros.h"

struct Rollback {
    vector<tuple<void*,void*,int>> r;
    int time() const { return size(r); }
    template<typename T> void save(T* x) { r.emplace_back(x, new T(*x), sizeof(T)); }
    void rollback(int t) {
        while (time() > t) {
        	apply(memcpy, r.back());
            r.pop_back();
        }
    }
};