/*
ID: sketchc1
LANG: C++14
TASK: stamps
*/
#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = 1'000'000'000;

int minStamps(int val, const int maxStamps, const vector<int>& values, vector<int>& dp) {
    if (val < 0) {
        return INF;
    }
    if (dp[val] != -1) {
        return dp[val];
    }
    int stamps = INF;
    for (int i = 0; i < values.size(); ++i) {
        stamps = min(stamps, 1 + minStamps(val - values[i], maxStamps, values, dp));
    }
    dp[val] = stamps;
    return dp[val];
}


int main() {
    // i/o
    ifstream fin("stamps.in");
    ofstream fout("stamps.out");

    int maxStamps, numValues;
    fin >> maxStamps >> numValues;

    vector<int> values(numValues);

    for (int i = 0; i < values.size(); ++i) {
        fin >> values[i];
    }

    int maxVal = *max_element(begin(values), end(values));
    // represents the minimum number of stamps that can be used to create this value
    vector<int> dp(maxVal * maxStamps + 1, -1);

    dp[0] = 0;
    int maxValue = 0;
    for (int i = 1; i < dp.size(); ++i) {
        if (minStamps(i, maxStamps, values, dp) > maxStamps) {
            maxValue = i - 1;
            break;
        }
        if (i == dp.size() - 1) {
            maxValue = i;
        }
    }

    fout << maxValue << '\n';

    return EXIT_SUCCESS;
}
