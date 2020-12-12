/*
ID: sketchc1
LANG: C++14
TASK: nocows
*/
#include <bits/stdc++.h>
using namespace std;

constexpr int64_t MOD = 9901;

int main() {
    // i/o
    ifstream fin("nocows.in");
    ofstream fout("nocows.out");
    int numNodes, height;
    fin >> numNodes >> height;
    vector<vector<int64_t>> dp(height + 1, vector<int64_t>(numNodes + 1, 0));

    for (int h = 1; h <= height; ++h) {
        dp[h][1] = 1;
    }

    for (int totalNodes = 3; totalNodes <= numNodes; totalNodes += 2) {
        for (int h = 1; h <= height; ++h) {
            for (int leftNodes = 1; leftNodes <= totalNodes - 2; ++leftNodes) {
                dp[h][totalNodes] += dp[h - 1][leftNodes] * dp[h - 1][totalNodes - leftNodes - 1];
                dp[h][totalNodes] %= MOD;
            }
        }
    }

    int64_t res = ((dp[height][numNodes] - dp[height - 1][numNodes]) + MOD) % MOD;
    fout << res << '\n';

    return EXIT_SUCCESS;
}
