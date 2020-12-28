/*
ID: sketchc1
LANG: C++14
TASK: nuggets
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // i/o
    ifstream fin("nuggets.in");
    ofstream fout("nuggets.out");

    int N;
    fin >> N;
    vector<int> nuggets(N);
    for (int i = 0; i < nuggets.size(); ++i) {
        fin >> nuggets[i];
    }

    auto dp = array<bool, 3'000'001>{};
    dp[0] = true;
    for (int nug = 0; nug < nuggets.size(); ++nug) {
        for (int i = nuggets[nug]; i < dp.size(); ++i) {
            if (dp[i - nuggets[nug]]) {
                dp[i] = true;
            }
        }
    }
    int res = 0;
    for (int i = 0; i < dp.size(); ++i) {
        if (!dp[i]) {
            res = i;
            if (i > 2'000'000) {
                res = 0;
                break;
            }
        }
    }


    fout << res << '\n';


    return EXIT_SUCCESS;
}
