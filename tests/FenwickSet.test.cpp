#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "../utils/data structures/FenwickSet.cpp"
#include "../utils/numerical/compress.cpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    seq a(n);
    vector<pair<num,num>> b(q);
    cin >> a >> b;
    vector<num*> coords;
    for (auto& x : a) coords.push_back(&x);
    for (auto& [x, y] : b) if (x != 2) coords.push_back(&y);
    seq decompress = compress(coords);
    seq init(size(decompress));
    for (auto x : a) init[x] = 1;
    FenwickSet<1> fs(init);
    auto dec = [&] (int x) -> num {
        if (x == size(decompress) || x == -1) return -1;
        return decompress[x];
    };
    for (auto [x, y] : b) {
        if (x == 0)
            fs.insert(y);
        else if (x == 1)
            fs.erase(y);
        else if (x == 2)
            cout << dec(fs.find_by_order(y)) << '\n';
        else if (x == 3)
            cout << fs.order_of_key(y + 1) << '\n';
        else if (x == 4)
            cout << dec(fs.prev(y + 1)) << '\n';
        else
            cout << dec(fs.lower_bound(y)) << '\n';
    }
}