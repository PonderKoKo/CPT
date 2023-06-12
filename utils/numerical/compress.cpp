#include "../macros.h"

template<typename T>
num compress(T x) {
	static map<T,num> m;
	if (!m.contains(x))
		m[x] = ssize(m);
	return m[x];
}

// For maintaining order
template<typename T>
struct Compressor {
	map<T,num> m;
	vector<T> r;
	bool finalized{false};
	num operator[](T x) { return m[x]; }
	void finalize() {
		for (num i = 0; auto& [x, z] : m)
			z = i++, r.push_back(x);
	}
	T decompress(num i) { return r[i]; }
};