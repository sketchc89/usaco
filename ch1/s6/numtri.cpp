/*
ID: sketchc1
LANG: C++14
TASK: numtri
*/
#include <bits/stdc++.h>
using namespace std;


int main() {
    // i/o
    ifstream fin("numtri.in");
    ofstream fout("numtri.out");

    int n, x;
    fin >> n;
    vector<vector<int>> vvi;
    for (int i = 0; i < n; ++i) {
        vvi.push_back(vector<int>(i + 1, 0));
        for (int j = 0; j < i + 1; ++j) {
            fin >> vvi[i][j];
        }
    }
    vector<vector<int>> dp = vvi;
    dp[0][0] = vvi[0][0];
    for (int row = 1; row < n; ++row) {
        for (int col = 0; col <= row; ++col) {
            if (col == 0) {
                dp[row][col] = vvi[row][col] + dp[row - 1][col];
            } else if (col == row) {
                dp[row][col] = vvi[row][col] + dp[row - 1][col - 1];
            } else {
                dp[row][col] = vvi[row][col] + max(dp[row - 1][col - 1], dp[row - 1][col]);
            }
            // fout << row << ',' << col << ';' << vvi[row][col] << '=' << dp[row][col] << '\t';
        }
        // fout << '\n';
    }

    // for (auto val : dp[n - 1]) {
    //     cout << val << '\t';
    // }

    fout << *max_element(begin(dp[n - 1]), end(dp[n - 1])) << '\n';

    return EXIT_SUCCESS;
}
