/*
ID: sketchc1
LANG: C++14
TASK: camelot
*/
#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = 1'000'000'000;

// breadth first search using knight rules of movement from one spot to all others
void bfsDist(int r, int c, vector<int>& dist, const int R, const int C) {
    vector<pair<int, int>> kdirs{{-1, -2}, {-2, -1}, {-1, 2}, {-2, 1}, {1, -2}, {2, -1}, {1, 2}, {2, 1}};
    vector<int> visited(dist.size(), false);
    queue<pair<int, int>> q;
    q.emplace(make_pair(r * C + c, 0));
    while (!q.empty()) {
        auto node = q.front().first;
        auto d = q.front().second;
        q.pop();
        if (visited[node]) {
            continue;
        } else {
            visited[node] = true;
        }
        int row = node / C;
        int col = node % C;
        dist[row * C + col] = d;
        for (auto dir : kdirs) {
            int newRow = dir.first + row;
            int newCol = dir.second + col;
            if (newRow < 0 || newRow >= R || newCol < 0 || newCol >= C) {
                continue;
            } else {
                q.emplace(make_pair(newRow * C + newCol, d + 1));
            }
        }
    }
}

int main() {
    // i/o
    ifstream fin("camelot.in");
    ofstream fout("camelot.out");

    // create a graph of every spot on the board to every other spot
    int R, C;
    fin >> R >> C;
    vector<vector<int>> graph(R * C, vector<int>(R * C, INF));

    // read in as 0-based integers
    char c;
    int r;
    fin >> c >> r;
    pair<int, int> king = make_pair(r - 1, c - 'A');
    vector<pair<int, int>> knights;
    while (fin >> c >> r) {
        knights.emplace_back(make_pair(r - 1, c - 'A'));
    }

    // special case where no knights on board, auto success
    if (knights.size() == 0) {
        fout << 0 << '\n';
        return EXIT_SUCCESS;
    }

    // all pairs shortest path undirected
    for (int row = 0; row < R; ++row) {
        for (int col = 0; col < C; ++col) {
            bfsDist(row, col, graph[row * C + col], R, C);
        }
    }

    // it is always more efficient for a knight to pick up the king if he is more than 2 spots away
    // try to pick up the king (or gather at king)  at every other spot within two moves of king
    vector<pair<int, int>> kingDirs;
    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            kingDirs.emplace_back(make_pair(i, j));
        }
    }

    // find minimum moves to gather at every spot on the board
    // equivalent to moving all knights to one spot, precomputed
    // then diverting one knight to pickup the king if the king is not at that spot
    int minSum = INT32_MAX, minSumRow = -1, minSumCol = -1;
    for (int row = 0; row < R; ++row) {
        for (int col = 0; col < C; ++col) {
            int sum = 0;
            for (auto k : knights) {
                if (graph[row * C + col][k.first * C + k.second] != INF) {
                    sum += graph[row * C + col][k.first * C + k.second];
                } else {
                    sum = INF;
                    break;
                }
            }
            if (sum >= minSum) {
                continue;
            }
            int minInc = INF;
            // try diverting each knight and find minimum extra moves needed
            for (auto k : knights) {
                // try diverting to all of the spots around the king previously generated
                for (auto dir : kingDirs) {
                    int newRow = dir.first + king.first;
                    int newCol = dir.second + king.second;
                    if (newRow < 0 || newRow >= R || newCol < 0 || newCol >= C) {
                        continue;
                    }
                    int inc = max(abs(dir.first), abs(dir.second));
                    inc += graph[k.first * C + k.second][newRow * C + newCol];  // knight to king
                    inc += graph[newRow * C + newCol][row * C + col];           // both to target
                    inc -= graph[k.first * C + k.second][row * C + col];        // subtract straight path knight to target
                    minInc = min(minInc, inc);
                    if (minInc == 0) {
                        break;
                    }
                }
                if (minInc == 0) {
                    break;
                }
            }
            // add the diversion cost to the previously computed sum
            sum += minInc;

            // update the lowest sum if we found a better spot
            if (sum < minSum) {
                minSum = sum;
                minSumRow = row;
                minSumCol = col;
            }
        }
    }
    fout << minSum << '\n';

    return EXIT_SUCCESS;
}
