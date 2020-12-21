/*
ID: sketchc1
LANG: C++14
TASK: kimbits
*/
#include <bits/stdc++.h>
using namespace std;

void setupBits(vector<vector<int>>& dp) {
    dp[0][0] = 1;
    for (int i = 1; i < dp.size(); ++i) {
        dp[i][0] = 1;
        dp[0][i] = 1;
        dp[i][i] = 1 << (i - 1);
    }
    for (int row = 1; row < dp.size(); ++row) {
        for (int col = 1; col < dp[row].size(); ++col) {
            dp[row][col] = dp[row - 1][col - 1] + dp[row - 1][col];
        }
    }
}

void printBits(string& s, int digs, int bits, int idx, vector<vector<int>>& dp) {
    if (digs == 0) {
        return;
    }

    int startsWithZero = dp[digs - 1][bits];
    if (idx < startsWithZero) {
        s.push_back('0');
        printBits(s, digs - 1, bits, idx, dp);
    } else {
        s.push_back('1');
        printBits(s, digs - 1, bits - 1, idx - startsWithZero, dp);
    }
}

int main() {
    // i/o
    ifstream fin("kimbits.in");
    ofstream fout("kimbits.out");

    int64_t n, l, idx;
    fin >> n >> l >> idx;

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    setupBits(dp);

    string s = "";
    printBits(s, n, l, idx - 1LL, dp);

    fout << s << '\n';

    return EXIT_SUCCESS;
}
