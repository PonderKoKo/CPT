#include "../macros.h"

auto exponentiate(auto a, auto b, num e, auto&& f) {
    for (; e; e /= 2, b = f(b, b))
		if (e & 1)
			a = f(a, b);
	return a;
}
