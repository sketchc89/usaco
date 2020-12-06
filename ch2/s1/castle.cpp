/*
ID: sketchc1
LANG: C++14
TASK: castle
*/
#include <bits/stdc++.h>
using namespace std;


class UnionFind {
public:
    UnionFind(int n) {
        _parent.reserve(n);
        _size.reserve(n);
        for (int i = 0; i < n; ++i) {
            _parent[i] = i;
            _size[i] = 1;
        }
    }

    int root(int x) {
        while (_parent[x] != x) {
            _parent[x] = _parent[_parent[x]];
            x = _parent[x];
        }
        return x;
    }

    bool unified(int x, int y) {
        return root(x) == root(y);
    }

    void unify(int x, int y) {
        if (unified(x, y)) {
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

    int size(int x) {
        return _size[root(x)];
    }

private:
    vector<int> _parent, _size;
};

int main() {
    // i/o
    ifstream fin("castle.in");
    ofstream fout("castle.out");


    int col, row, conn;
    fin >> col >> row;
    UnionFind graph(col * row);
    for (int r = 0; r < row; ++r) {
        for (int c = 0; c < col; ++c) {
            int pos = r * col + c;
            fin >> conn;
            if ((conn & 4) == 0) {
                graph.unify(pos, pos + 1);
            }
            if ((conn & 8) == 0) {
                graph.unify(pos, pos + col);
            }
        }
    }
    unordered_set<int> rooms;
    int maxRoom = 0;
    for (int i = 0; i < row * col; ++i) {
        int root = graph.root(i);
        rooms.insert(root);
        maxRoom = max(maxRoom, graph.size(root));
    }
    char maxDir = ' ';
    int maxSize = 0;
    int maxPos = 0;
    int size = 0;
    if (row == 1) {
        for (int c = 0; c < col - 1; ++c) {
            size = 0;
            if (!graph.unified(c, c + 1)) {
                size = graph.size(c) + graph.size(c + 1);
                if (size > maxSize) {
                    maxPos = c;
                    maxDir = 'E';
                    maxSize = size;
                }
            }
        }
    }


    for (int r = 1; r < row; ++r) {
        for (int c = 0; c < col; ++c) {
            int pos = r * col + c;
            size = 0;
            if (c % col < col - 1 && !graph.unified(pos, pos + 1)) {
                size = graph.size(pos) + graph.size(pos + 1);
                if (size > maxSize) {
                    maxSize = size;
                    maxDir = 'E';
                    maxPos = pos;
                } else if (size == maxSize) {
                    if (pos % col <= maxPos % col) {
                        maxDir = 'E';
                        maxPos = pos;
                    }
                }
            }
            if (!graph.unified(pos, pos - col)) {
                size = graph.size(pos) + graph.size(pos - col);
                if (size > maxSize) {
                    maxSize = size;
                    maxDir = 'N';
                    maxPos = pos;
                } else if (size == maxSize) {
                    if (pos % col <= maxPos % col) {
                        maxPos = pos;
                        maxDir = 'N';
                    }
                }
            }
            if (size > maxSize) {
                maxSize = size;
            }
        }
    }
    fout << rooms.size() << '\n';
    fout << maxRoom << '\n';
    fout << maxSize << '\n';
    fout << 1 + maxPos / col << ' ' << 1 + maxPos % col << ' ' << static_cast<char>(maxDir) << '\n';

    return EXIT_SUCCESS;
}
