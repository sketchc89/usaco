/*
ID: sketchc1
LANG: C++14
TASK: stamps
*/
#include <bits/stdc++.h>
using namespace std;


int main() {
    // i/o
    ifstream fin("stamps.in");
    ofstream fout("stamps.out");

    int maxStamps, numValues;
    fin >> maxStamps >> numValues;

    vector<vector<int64_t>> dp(numValues + 1, vector<int64_t>(maxStamps, 0));
    vector<int64_t> values(numValues + 1);

    values[0] = 0;
    for (int i = 1; i < values.size(); ++i) {
        fin >> values[i];
    }
    dp[0][0] = 1;
    for (int i = 1; i < dp.size(); ++i) {
        // cout << i << '\n';
        // cout << "Value: " << values[i] << '\n';
        for (int j = values[i]; j < maxStamps; ++j) {
            cout << "Checking " << i - 1 << '\t' << j - values[i] << " is " << dp[i - 1][j - values[i]] << '\n';
            if (dp[i - 1][j - values[i]] > 0) {
                dp[i][j] += dp[i - 1][j - values[i]];
            }
            cout << i << ',' << j << " is " << dp[i][j] << '\n';
        }
    }
    int maxValue = 0;
    for (int j = 0; j < dp[0].size(); ++j) {
        bool valid = false;
        for (int i = 0; i < dp.size(); ++i) {
            if (dp[i][j] > 0) {
                valid = true;
            }
        }
        if (!valid) {
            break;
        } else {
            maxValue = j;
        }
    }

    fout << maxValue << '\n';

    return EXIT_SUCCESS;
}
