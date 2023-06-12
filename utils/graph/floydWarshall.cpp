#include "../macros.h"

// in-place relaxation of Adjacency Matrix; Using 18_e as Infinity
void floydWarshall(Graph& adj) {
#define mineq(a, b) a = min(a, b)
	num n = ssize(adj);
	rep(i, n)
		mineq(adj[i][i], 0ll);
	rep(k, n) rep(i, n) rep(j, n)
		mineq(adj[i][j], max(adj[i][k] + adj[k][j], -18_e));
	rep(k, n) if (adj[k][k] < 0) rep(i, n) rep(j, n)
		if (adj[i][k] != 18_e && adj[k][j] != 18_e)
			adj[i][j] = -18_e;
#undef mineq
}
