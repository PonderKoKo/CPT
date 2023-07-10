#include "../macros.h"

seq two_edge_comps(const Graph& adj) {
    num i = 0; // Next component index
    seq comp(size(adj)) /* Map from node to component index */, depth(adj.size(), -1);
    stack<num> st;
    function<num(num,num)> dfs = [&] (num u, num d) {
        num starting = ssize(st), up = 0; // Number of Edges to a node with lower depth
        st.push(u);
        depth[u] = d;
        for (num v : adj[u]) {
            if (depth[v] == -1) // Tree Edge
                up += dfs(v, d + 1);
            up += (d > depth[v]) - (d < depth[v]);
        }
        if (up <= 1) { // There are no Back Edges passing over u (up == 0 for root else 1)
            while (ssize(st) > starting)
                comp[st.top()] = i, st.pop();
            i++;
        }
        return up;
    };
    dfs(0, 0);
    return comp;
}