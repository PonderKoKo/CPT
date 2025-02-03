#include "../macros.h"

struct Rollback : vector<tuple<void*,void*,int>> {
    template<typename T> void save(T* x) {
        emplace_back(x, new T(*x), sizeof(T));
    }
    void rollback(int t) {
        while (t < size())
        	apply(memcpy, back()), pop_back();
    }
};
