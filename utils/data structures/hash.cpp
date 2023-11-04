#include "../macros.h"

#include <ext/pb_ds/assoc_container.hpp>

struct Hash {
	static uint64_t s(uint64_t x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		static const uint64_t random = chrono::steady_clock::now().time_since_epoch().count();
		x += 0x9e3779b97f4a7c15 + random;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const { return s(x); }

	template<typename T, typename U>
	size_t operator()(pair<T,U> p) const {
		return 3 * s(p.first) + s(p.second);
	}
};

template<typename T, typename U> using hashmap = __gnu_pbds::gp_hash_table<T,U,Hash>;
template<typename T> using hashset = hashmap<T,__gnu_pbds::null_type>;