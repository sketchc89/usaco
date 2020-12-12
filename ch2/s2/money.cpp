/*
ID: sketchc1
LANG: C++14
TASK: money
*/
#include <bits/stdc++.h>
using namespace std;


int main() {
    // i/o
    ifstream fin("money.in");
    ofstream fout("money.out");

    int numCoins, target;
    fin >> numCoins >> target;
    vector<int64_t> coins(numCoins);
    for (int c = 0; c < coins.size(); ++c) {
        fin >> coins[c];
    }

    vector<int64_t> dp(target + 1, 0);
    dp[0] = 1;

    for (int c = 0; c < coins.size(); ++c) {
        const auto& coin = coins[c];
        for (int i = coin; i <= target; ++i) {
            if (dp[i - coin]) {
                dp[i] = dp[i] + dp[i - coin];
            }
        }
    }

    fout << dp[target] << '\n';

    return EXIT_SUCCESS;
}
