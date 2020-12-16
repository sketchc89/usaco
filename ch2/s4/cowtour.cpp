/*
ID: sketchc1
LANG: C++14
TASK: cowtour
*/
#include <bits/stdc++.h>
using namespace std;

constexpr static double INF = 1e9;

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

void allPairsShortestPath(vector<vector<double>>& mat) {
    int N = mat.size();
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (mat[i][k] + mat[k][j] < mat[i][j]) {
                    mat[i][j] = mat[i][k] + mat[k][j];
                }
            }
        }
    }
}

int main() {
    // i/o
    ifstream fin("cowtour.in");
    ofstream fout("cowtour.out");

    int N;
    fin >> N;

    vector<pair<double, double>> positions(N);
    for (int i = 0; i < N; ++i) {
        fin >> positions[i].first >> positions[i].second;
    }
    fin.ignore(INT32_MAX, '\n');

    vector<vector<int>> conn(N, vector<int>(N, 0));
    for (int row = 0; row < N; ++row) {
        string rowStr;
        getline(fin, rowStr);
        for (int col = 0; col < N; ++col) {
            conn[row][col] = rowStr[col] - '0';
        }
    }

    // compute distance between nodes and join components
    vector<vector<double>> dist(N, vector<double>(N, INF));
    UnionFind uf(N);
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            if (conn[row][col]) {
                double d =
                        sqrt(pow(positions[row].first - positions[col].first, 2) +  //
                             pow(positions[row].second - positions[col].second, 2));
                dist[row][col] = d;
                dist[col][row] = d;
                uf.unify(row, col);
            }
        }
        dist[row][row] = 0.0;
    }

    allPairsShortestPath(dist);

    double res = numeric_limits<double>::max();
    int firstComponent = uf.root(0), secondComponent = -1;
    double firstDiameter = 0.0, secondDiameter = 0.0;
    vector<double> maxDistance(N);

    // determine the diameter of the two components, the largest of all pairs shortest paths in a component
    for (int row = 0; row < N; ++row) {
        double diameter = 0;
        int component = uf.root(row);
        for (int col = 0; col < N; ++col) {
            if (dist[row][col] > maxDistance[col] && dist[row][col] < INF) {
                maxDistance[col] = dist[row][col];
            }
            if (dist[row][col] > diameter && dist[row][col] < INF) {
                diameter = dist[row][col];
            }
        }
        if (component == firstComponent) {
            firstDiameter = max(firstDiameter, diameter);
        } else {
            if (secondComponent != -1 && component != secondComponent) {
                cerr << "WARNING: Already set second component to " << secondComponent << " and resetting to component " << component
                     << "\n";
            }
            secondComponent = component;
            secondDiameter = max(secondDiameter, diameter);
        }
    }

    // best diameter is either diameter from first component, diameter from second component
    // or node i->j in different components + max distance i + max distance j
    double bestIntraComponentDiameter = INF;
    double diameter = INF;
    double bestDiameter = max(firstDiameter, secondDiameter);
    for (int row = 0; row < N; ++row) {
        if (uf.root(row) == secondComponent) {  // do all firstComponent to secondComponent
            continue;
        }
        for (int col = 0; col < N; ++col) {
            if (uf.find(row, col)) {  // same component
                continue;
            }
            double d = sqrt(pow(positions[row].first - positions[col].first, 2) + pow(positions[row].second - positions[col].second, 2));
            diameter = maxDistance[row] + maxDistance[col] + d;
            bestIntraComponentDiameter = min(bestIntraComponentDiameter, diameter);
        }
        bestDiameter = max(firstDiameter, max(secondDiameter, bestIntraComponentDiameter));
    }

    // output
    fout << setprecision(6) << fixed << bestDiameter << '\n';
    return EXIT_SUCCESS;
}
