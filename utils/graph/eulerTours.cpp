#include "../macros.h"

// Nodes are only added into euler when they are first visited. Good for Subtree Segment Trees
auto short_euler(num root, const Graph& adj) {
    const num n = ssize(adj);
    seq entry(n), exit(n), depth(n), euler(n);
    num t = 0;
    function<void(num,num,num)> dfs = [&](num u, num p, num d) {
        depth[u] = d, euler[t] = u, entry[u] = t++;
        for (num v : adj[u])
            if (v != p)
                dfs(v, u, d + 1);
        exit[u] = t;
    };
    dfs(root, -1, 0);
    return tuple(entry, exit, depth, euler);
}