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
    // cout << "Size of mat is " << N << '\n';
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (mat[i][k] + mat[k][j] < mat[i][j]) {
                    // cout << "ijk " << i << ',' << j << ',' << k << '\t';
                    // cout << mat[i][j] << '\t' << mat[i][k] + mat[k][j] << '\n';
                    mat[i][j] = mat[i][k] + mat[k][j];
                }
            }
        }
    }

    // cout << "\n\n\n";
    // for (auto&& vi : mat) {
    //     for (auto num : vi) {
    //         if (num >= INF) {
    //             cout << '-' << " ";
    //         } else {
    //             cout << setprecision(2) << fixed << num << " ";
    //         }
    //     }
    //     cout << '\n';
    // }
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
        // cout << positions[i].first << ',' << positions[i].second << '\t';
    }
    // cout << '\n';
    fin.ignore(INT32_MAX, '\n');

    vector<vector<int>> conn(N, vector<int>(N, 0));
    for (int row = 0; row < N; ++row) {
        string rowStr;
        getline(fin, rowStr);
        // cout << "Row: " << row << '\t' << rowStr << '\n';
        for (int col = 0; col < N; ++col) {
            conn[row][col] = rowStr[col] - '0';
        }
    }

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
        // cout << '\n';
    }

    allPairsShortestPath(dist);

    // int res = computeDiameter(graph);
    double res = numeric_limits<double>::max();
    int firstComponent = uf.root(0), secondComponent = -1;
    double firstDiameter = 0.0, secondDiameter = 0.0;
    vector<double> maxDistance(N);

    // for (int row = 0; row < N; ++row) {
    //     cout << uf.root(row) << ',';
    //     if (row % 10 == 0 && row != 0) {
    //         cout << '\n';
    //     }
    // }
    // cout << '\n';

    for (int row = 0; row < N; ++row) {
        double diameter = 0;
        int component = uf.root(row);
        for (int col = 0; col < N; ++col) {
            if (dist[row][col] > maxDistance[col] && dist[row][col] < INF) {
                maxDistance[col] = dist[row][col];
            }
            if (dist[row][col] > diameter && dist[row][col] < INF) {
                diameter = dist[row][col];
                // cout << "Diameter " << dist[row][col] << '\n';
            }
        }
        if (component == firstComponent) {
            firstDiameter = max(firstDiameter, diameter);
            // cout << "First component is " << component << '\n';
        } else {
            if (secondComponent != -1 && component != secondComponent) {
                cerr << "WARNING: Already set second component to " << secondComponent << " and resetting to component " << component
                     << "\n";
            }
            secondComponent = component;
            // cout << "Second component is " << component << '\n';
            secondDiameter = max(secondDiameter, diameter);
        }
    }
    // for (auto i = 0; i < N; ++i) {
    //     cout << "Max distance: " << maxDistance[i] << '\n';
    // }

    double bestIntraComponentDiameter = INF;
    double diameter = INF;
    double bestDiameter = max(firstDiameter, secondDiameter);
    // cout << "Best Diameter inside components is " << bestDiameter << '\n';
    for (int row = 0; row < N; ++row) {
        if (uf.root(row) == secondComponent) {  // do all firstComponent to secondComponent
            // cout << "Skipping " << row << '\n';
            continue;
        }
        for (int col = 0; col < N; ++col) {
            if (uf.find(row, col)) {  // same component
                // cout << row << " and " << col << " are in the same component\n";
                continue;
            }
            double d = sqrt(pow(positions[row].first - positions[col].first, 2) + pow(positions[row].second - positions[col].second, 2));
            diameter = maxDistance[row] + maxDistance[col] + d;
            bestIntraComponentDiameter = min(bestIntraComponentDiameter, diameter);
            // cout << "Best intracomponent diameter so far " << bestIntraComponentDiameter << '\n';
        }
        bestDiameter = max(firstDiameter, max(secondDiameter, bestIntraComponentDiameter));
        // cout << "Best diameter so far " << bestDiameter << '\n';
    }
    // cout << "Result: " << res << '\n';
    fout << setprecision(6) << fixed << bestDiameter << '\n';
    return EXIT_SUCCESS;
}
