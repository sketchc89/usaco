/*
ID: sketchc1
LANG: C++14
TASK: range
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // i/o
    ifstream fin("range.in");
    ofstream fout("range.out");

    int N;
    fin >> N;
    vector<string> pasture(N);
    vector<vector<int>> dp(N, vector<int>(N, 0));
    for (int row = 0; row < pasture.size(); ++row) {
        fin >> pasture[row];
    }

    for (int i = 0; i < N; ++i) {
        dp[i][0] = pasture[i][0] - '0';
        dp[0][i] = pasture[0][i] - '0';
    }
    for (int row = 1; row < dp.size(); ++row) {
        for (int col = 1; col < dp[row].size(); ++col) {
            if (pasture[row][col] == '0') {
                dp[row][col] = 0;
            } else {
                dp[row][col] = 1 + min(dp[row - 1][col - 1], min(dp[row - 1][col], dp[row][col - 1]));
            }
        }
    }

    map<int, int> counter;
    for (int sz = 2; sz <= N; ++sz) {
        for (int row = sz - 1; row < N; ++row) {
            for (int col = sz - 1; col < N; ++col) {
                if (dp[row][col] >= sz) {
                    counter[sz]++;
                }
            }
        }
    }

    for (auto&& kv : counter) {
        fout << kv.first << ' ' << kv.second << '\n';
    }

    return EXIT_SUCCESS;
}
