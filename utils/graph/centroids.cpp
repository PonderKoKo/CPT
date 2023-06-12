#include "../macros.h"

num findSize(num node, num parent, seq& sizes, const vector<bool>& visited, const Graph& adj) {
    if (visited[node])
        return 0;
    sizes[node] = 1;
    for (num next : adj[node])
        if (next != parent)
            sizes[node] += findSize(next, node, sizes, visited, adj);
    return sizes[node];
}

num findCentroid(num node, num parent, num total, const seq& sizes, const vector<bool>& visited, const Graph& adj) {
    for (num next : adj[node])
        if (next != parent && !visited[next] && sizes[next] > total / 2)
            return findCentroid(next, node, total, sizes, visited, adj);
    return node;
}

void centroidDecomposition(num node, num parent, const Graph& adj, vector<bool>& visited, seq& sizes) {
    findSize(node, -1, sizes, visited, adj);
    num centroid = findCentroid(node, -1, sizes[node], sizes, visited, adj);
    // Parent of centroid in Centroid Tree is parent
    // Perform centroid algo here, size of current component is sizes[node]
    visited[centroid] = true;
    for (num next : adj[centroid])
        if (!visited[next])
            centroidDecomposition(next, node, adj, visited, sizes);
}