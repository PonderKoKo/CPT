#include "../macros.h"

/*
 * Sqrt-tree impelementation
 *
 * Time complexity:
 *   build:  O(N * loglogN)
 *   update: O(sqrt(N))
 *   query:  O(1)
 *
 * Memory usage: O(N * loglogN)
 *
 * Code written by:
 *   Alexander Kernozhitsky (aka gepardo)
 *
 * Date: 24.04.2018
 */

class SqrtTree {
	using T = num;
	static T f(T x, T y) {
		return min(x, y);
	}

};