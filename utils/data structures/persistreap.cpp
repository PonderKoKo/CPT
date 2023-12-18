#include "../macros.h"

struct Node {
    int left = 0, right = 0, size;
    int value;
    num sum = value;
    explicit Node(int v, int s = 1) : size{s}, value{v} {}
};
vector<Node> v{Node(0, 0)};
template<bool p> int nx(int i) { return p ? (v.push_back(v[i]), size(v) - 1) : i; }

void update(int i) {
    if (!i) return;
    const int& l = v[i].left, r = v[i].right;
    v[i].size = 1 + v[l].size + v[r].size;
    v[i].sum = v[i].value + v[l].sum + v[r].sum;
}

template<bool p>
int join(int l, int r) {
    if (!l) return r;
    if (!r) return l;
    int c;
    if (rng() % (v[l].size + v[r].size) < v[l].size)
        v[c = nx<p>(l)].right = join<p>(v[l].right, r);
    else
        v[c = nx<p>(r)].left = join<p>(l, v[r].left);
    update(c);
    return c;
}

template<bool p>
pair<int,int> split(int i, int key) {
    if (!i)
        return {0, 0};
    const int& l = v[i].left, r = v[i].right;
    int ci = nx<p>(i);
    if (1 + v[l].size <= key) {
        auto [rl, rr] = split<p>(r, key - v[l].size - 1);
        v[ci].right = rl;
        update(ci);
        return {ci, rr};
    } else {
        auto [ll, lr] = split<p>(l, key);
        v[ci].left = lr;
        update(ci);
        return {ll, ci};
    }
}

template<bool p>
tuple<int,int,int> extract(int i, int l, int r) {
    auto [remainder, right] = split<p>(i, r);
    auto [left, mid] = split<p>(remainder, l);
    return {left, mid, right};
}

void printit(int i) {
    if (!i)
        return;
    printit(v[i].left);
    cout << v[i].value << ' ';
    printit(v[i].right);
}

template<bool p>
int join(vector<int> a) {
    for (int i = 1; i < ssize(a); i *= 2)
        for (int j = 0; j + i < ssize(a); j += 2 * i)
            a[j] = join<p>(a[j], a[j + i]);
    return a[0];
}