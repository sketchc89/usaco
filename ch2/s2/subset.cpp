/*
ID: sketchc1
LANG: C++14
TASK: subset
*/
#include <bits/stdc++.h>
using namespace std;

array<int64_t, 40> dp;

int main() {
    // i/o
    ifstream fin("subset.in");
    ofstream fout("subset.out");

    dp.fill(0);
    int64_t n;
    fin >> n;
    int64_t target = n * (n + 1) / 4;  // 1+2+...n = n*(n+1)/2
    if (n * (n + 1) % 4 != 0) {
        fout << 0 << '\n';
        return EXIT_SUCCESS;
    }
    // cout << "TARGET: " << target << '\n';

    for (int64_t i = 1; i <= n; ++i) {
        for (int64_t j = target; j >= i; --j) {
            if (dp[j - i] > 0) {
                // cout << i << ',' << j << '\n';
                dp[j] += dp[j - i];
            }
        }
        dp[i]++;
    }
    // for (int i = 0; i < dp.size(); ++i) {
    //     cout << i << ':' << dp[i] << '\n';
    // }
    fout << dp[target] / 2LL << '\n';


    return EXIT_SUCCESS;
}

// 0 - 1 //
// 1 - 1 // 1
// 2 - 1 // 2
// 3 - 2 // 1,2, 3
// 4 - 2 // 1-3, 4
