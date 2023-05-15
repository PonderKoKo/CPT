#include "../macros.h"

/* Strongly Connected Components in Directed Graph in O(V + E)
 * Returns vector with mapping to components and number of those components.
 * Component Indices are in Reverse Topological Order (only edges to smaller components)
 */
pair<seq,num> scc(Graph& adj) {
	num n = ssize(adj);
	seq val(n), comp(n, -1);
	stack<num> z;
	num time{0}, count{0};
	function<num(num)> dfs = [&] (num j) {
		num low = val[j] = ++time;
		z.push(j);
		for (num e : adj[j])
			if (comp[e] == -1)
				low = min(low, val[e] ?: dfs(e));
		if (low == val[j]) {
			num x;
			do {
				x = z.top();
				z.pop();
				comp[x] = count;
			} while (x != j);
			count++;
		}
		return val[j] = low;
	};
	rep(i,n)
		if (comp[i] == -1)
			dfs(i);
	return make_pair(comp, count);
}

// Build Condensation Graph in O(V + E log E)
Graph condensation(const Graph& adj, const seq& comp) {
	Graph cadj(*max_element(all(comp)) + 1);
	rep(i, ssize(adj))
		for (num j : adj[i])
			if (comp[i] != comp[j])
				cadj[comp[i]].push_back(comp[j]);
	for (seq& row : cadj)
		sort(all(row)),
				row.erase(unique(all(row)), end(row));
	return cadj;
}