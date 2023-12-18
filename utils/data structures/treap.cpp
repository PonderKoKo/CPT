#include "../macros.h"
// Tree Heap
using Node = struct Implicitreap*;
struct Implicitreap {

    num val;
    // TODO Optional Updates
    bool reversed = false;
    // TODO Optional Aggregates
    num sum = val, max = val;

    Implicitreap(num value) : val(value) {}
};
int MAXT = 1e7;
static mt19937 rng(static_cast<unsigned>(chrono::steady_clock::now().time_since_epoch().count()));
vector<int> left(MAXT), right(MAXT), size(MAXT), priority(MAXT);
iota(all(priority), 0);


void update(Node node) {
    if (!node) return;
    Node& l = node->left, r = node->right;

#define access(u, field, neutral) (u ? u->field : neutral)
    node->size = 1 + access(l, size, 0) + access(r, size, 0);

    // TODO Update Aggregates
    node->sum = node->val + access(l, sum, 0) + access(r, sum, 0);
    node->max = max({node->val, access(l, max, numeric_limits<num>::min()), access(r, max, numeric_limits<num>::min())});
#undef access
}

void push(Node node) {
    if (!node) return;
    // TODO Merge Updates
    if (node->reversed) {
        node->reversed = false;
        swap(node->left, node->right);
        if (node->left)
            node->left->reversed ^= true;
        if (node->right)
            node->right->reversed ^= true;
    }
}

Node join(Node left, Node right) {
    push(left), push(right);
    if (!left) return right;
    if (!right) return left;
    if (left->priority <= right->priority)
        return left->right = join(left->right, right), update(left), left;
    else
        return right->left = join(left, right->left), update(right), right;
}

Node unify(initializer_list<Node> nodes) {
    return accumulate(all(nodes), (Node) nullptr, join);
}

// Split into pair<[0, key), [key, size)>
pair<Node,Node> split(Node node, num key) {
    if (!node)
        return make_pair(nullptr, nullptr);
    push(node);
#define access(u, field, neutral) (u ? u->field : neutral)
    if (1 + access(node->left, size, 0) <= key) {
        auto [rl, rr] = split(node->right, key - access(node->left, size, 0) - 1);
        node->right = rl;
        update(node);
        return make_pair(node, rr);
    } else {
        auto [ll, lr] = split(node->left, key);
        node->left = lr;
        update(node);
        return make_pair(ll, node);
    }
#undef access
}

tuple<Node,Node,Node> extract(Node node, num l, num r) {
    auto [remainder, right] = split(node, r);
    auto [left, mid] = split(remainder, l);
    return make_tuple(left, mid, right);
}

Implicitreap query(Node& node, num l, num r, const function<void(Node&)>& f = nullptr) {
    assert(0 <= l && l < r && r <= node->size);
    auto [left, mid, right] = extract(node, l, r);
    Implicitreap result = *mid;
    if (f) {
        f(mid);
        update(mid);
    }
    node = unify({left, mid, right});
    return result;
}

void remove(Node& node, num l, num r) {
    query(node, l, r, [&](Node& v) {
        v = nullptr;
    });
}

void reverse(Node& node, num l, num r) {
    query(node, l, r, [&](Node& v) {
        v->reversed ^= true;
    });
}

void change(Node& node, num i, num val) {
    query(node, i, i + 1, [&](Node& v) {
        v->val = val;
    });
}

void insert(Node& node, num i, Node other) {
    auto [left, right] = split(node, i);
    node = unify({left, other, right});
}

void move(Node& node, num l, num r, num i) {
    auto [left, mid, right] = extract(node, l, r);
    node = join(left, right);
    insert(node, i, mid);
}

void iterate(Node node, const function<void(num)>& f) {
    if (!node)
        return;
    push(node);
    iterate(node->left, f);
    f(node->val);
    iterate(node->right, f);
}

Node buildImplicitreap(const seq& a) { // Naive Implementation
    return accumulate(all(a), static_cast<Node>(nullptr), [&] (Node node, num x) {
        return join(node, new Implicitreap(x));
    });
}