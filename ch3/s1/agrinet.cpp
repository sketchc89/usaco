/*
ID: sketchc1
LANG: C++14
TASK: agrinet
*/
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

class UnionFind {
public:
    UnionFind(int n) {
        for (int i = 0; i < n; ++i) {
            _size.push_back(1);
            _parent.push_back(i);
        }
    }

    int root(int x) {
        while (x != _parent[x]) {
            _parent[x] = _parent[_parent[x]];
            x = _parent[x];
        }
        return x;
    }

    bool find(int x, int y) {
        return root(x) == root(y);
    }

    void unify(int x, int y) {
        if (find(x, y)) {
            return;
        }

        x = root(x);
        y = root(y);
        if (_size[x] < _size[y]) {
            swap(x, y);
        }
        _size[x] += _size[y];
        _parent[y] = x;
    }

private:
    vector<int> _parent, _size;
};

int main() {
    // i/o
    ifstream fin("agrinet.in");
    ofstream fout("agrinet.out");

    int N;
    fin >> N;
    UnionFind uf(N);
    cout << "N is " << N << '\n';

    priority_queue<pair<int, pii>, vector<pair<int, pii>>, greater<pair<int, pii>>> pq;
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            int weight;
            fin >> weight;
            if (col > row) {  // undirected graph
                pq.emplace(make_pair(weight, make_pair(row, col)));
            }
        }
    }

    int res = 0;
    while (!pq.empty()) {
        auto w = pq.top().first;
        auto a = pq.top().second.first;
        auto b = pq.top().second.second;
        pq.pop();
        if (!uf.find(a, b)) {
            res += w;
            uf.unify(a, b);
        }
    }
    fout << res << '\n';

    return EXIT_SUCCESS;
}
