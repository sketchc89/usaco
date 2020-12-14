/*
ID: sketchc1
LANG: C++14
TASK: maze1
*/
#include <bits/stdc++.h>
using namespace std;

struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        return hash<int>()(p.first >> 16 | p.first << 16) ^ hash<int>()(p.second);
    }
};
constexpr static int INF = 1'000'000'000;
vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool isValid(
        const pair<int, int>& fencePos,  //
        const pair<int, int>& mazePos,
        const vector<string>& maze,
        const vector<vector<int>>& grid) {

    int R = grid.size();
    int C = grid[0].size();
    if ((mazePos.first - 1) / 2 < 0  //
        || (mazePos.first - 1) / 2 >= R
        || (mazePos.second - 1) / 2 < 0
        || (mazePos.second - 1) / 2 >= C) {
        return false;
    }
    if (maze[fencePos.first][fencePos.second] == '|' || maze[fencePos.first][fencePos.second] == '-') {
        return false;
    }
    if (maze[fencePos.first][fencePos.second] == '+') {
        cerr << "ERROR: HIT + at " << fencePos.first << ',' << fencePos.second << "\n";
        abort();
        return false;
    }
    return true;
}

int maxSteps(pair<int, int> pos, const vector<string>& maze, vector<vector<int>>& grid) {
    unordered_set<pair<int, int>, PairHash> visited;
    queue<pair<int, pair<int, int>>> q;
    q.emplace(make_pair(1, pos));
    while (!q.empty()) {
        auto num = q.front().first;
        auto mazePos = q.front().second;
        q.pop();
        if (visited.count(mazePos)) {
            continue;
        } else {
            visited.insert(mazePos);
        }
        auto& stepsPos = grid[(mazePos.first - 1) / 2][(mazePos.second - 1) / 2];
        stepsPos = min(num, stepsPos);
        for (auto dir : dirs) {
            auto fence = make_pair(mazePos.first + dir.first, mazePos.second + dir.second);
            auto newPos = make_pair(num + 1, make_pair(mazePos.first + 2 * dir.first, mazePos.second + 2 * dir.second));
            if (isValid(fence, newPos.second, maze, grid)) {
                q.emplace(newPos);
            }
        }
    }
    return 0;
}

int main() {
    // i/o
    ifstream fin("maze1.in");
    ofstream fout("maze1.out");

    int W, H;
    fin >> W >> H;

    vector<string> maze(2 * H + 1);
    fin.ignore(INT32_MAX, '\n');
    for (int row = 0; row < maze.size(); ++row) {
        getline(fin, maze[row]);
    }
    pair<int, int> startPos1{-1, -1}, startPos2{-1, -1}, unassigned{-1, -1};
    /* Check the top and bottom row for openings */
    for (int col = 1; col < 2 * W + 1; col += 2) {
        if (maze[0][col] == ' ') {
            if (startPos1 == unassigned) {
                startPos1 = {1, col};
            } else {
                startPos2 = {1, col};
            }
        }
        if (maze[2 * H][col] == ' ') {
            if (startPos1 == unassigned) {
                startPos1 = {2 * H - 1, col};
            } else {
                startPos2 = {2 * H - 1, col};
            }
        }
    }
    /* Check the left and right column for openings */
    for (int row = 1; row < 2 * H + 1; row += 2) {
        if (maze[row][0] == ' ') {
            if (startPos1 == unassigned) {
                startPos1 = {row, 1};
            } else {
                startPos2 = {row, 1};
            }
        }
        if (maze[row][2 * W] == ' ') {
            if (startPos1 == unassigned) {
                startPos1 = {row, 2 * W - 1};
            } else {
                startPos2 = {row, 2 * W - 1};
            }
        }
    }

    /* Create 2D integer matrix representing steps from opening and label spot
     * next to opening 1 */
    vector<vector<int>> steps(H, vector<int>(W, INF));
    steps[startPos1.first / 2][startPos1.second / 2] = 1;
    steps[startPos2.first / 2][startPos2.second / 2] = 1;

    /* Walk from each opening, modifying steps matrix */
    maxSteps(startPos1, maze, steps);
    maxSteps(startPos2, maze, steps);

    /* Get maximum step value from matrix */
    int res = 0;
    for (int r = 0; r < steps.size(); ++r) {
        for (int c = 0; c < steps[r].size(); ++c) {
            res = max(steps[r][c], res);
        }
    }
    fout << res << '\n';


    return EXIT_SUCCESS;
}
