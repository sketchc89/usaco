/*
ID: sketchc1
LANG: C++14
TASK: ttwo
*/
#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> dirs{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
constexpr static int SIZE = 10;

void printGrid(vector<string>& grid, pair<int, int> f, pair<int, int> c) {
    cout << grid.size();
    grid[f.first][f.second] = 'F';
    grid[c.first][c.second] = 'C';
    for (auto&& g : grid) {
        cout << g.size() << '\t';
        cout << g << '\n';
    }
    grid[f.first][f.second] = '.';
    grid[c.first][c.second] = '.';
}
void gridMove(pair<int, int>& pos, int& dirCount, vector<string>& grid) {
    auto newRow = pos.first + dirs[dirCount].first;
    auto newCol = pos.second + dirs[dirCount].second;
    if (newRow < 0 || newRow >= SIZE || newCol < 0 || newCol >= SIZE || grid[newRow][newCol] == '*') {
        dirCount = (dirCount + 1) % dirs.size();
    } else {
        pos = make_pair(newRow, newCol);
    }
}


int main() {
    // i/o
    ifstream fin("ttwo.in");
    ofstream fout("ttwo.out");

    pair<int, int> cowPose, farmerPose;
    vector<string> grid(SIZE);
    for (int i = 0; i < SIZE; ++i) {
        fin >> grid[i];
        auto fidx = grid[i].find('F');
        auto cidx = grid[i].find('C');
        if (fidx != string::npos) {
            farmerPose = {i, fidx};
            grid[i][fidx] = '.';
        }
        if (cidx != string::npos) {
            cowPose = {i, cidx};
            grid[i][cidx] = '.';
        }
    }

    // N, E, S, W
    int cowDirCount = 0, farmerDirCount = 0;
    int catchTime = 0, t = 1;

    for (; t < 1000; ++t) {
        gridMove(cowPose, cowDirCount, grid);
        gridMove(farmerPose, farmerDirCount, grid);
        if (cowPose == farmerPose) {
            catchTime = t;
            break;
        }
    }
    fout << catchTime << '\n';

    return EXIT_SUCCESS;
}
