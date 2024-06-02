#include "../macros.h"

template<typename T, auto f>
T exponentiate(T ans, T b, num e) {
    for (; e; e >>= 1, b = f(b, b))
		if (e & 1)
			ans = f(ans, b);
	return ans;
}