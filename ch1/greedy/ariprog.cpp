/*
ID: sketchc1
LANG: C++14
TASK: ariprog
*/
#include <bits/stdc++.h>
using namespace std;


int main() {
    // i/o
    ifstream fin("ariprog.in");
    ofstream fout("ariprog.out");

    int seqLen, bsq;
    cin >> seqLen >> bsq;

    cout << "HI\n";
    unordered_set<int> s;
    for (int p = 0; p <= bsq; ++p) {
        for (int q = 0; q <= bsq; ++q) {
            cout << p << ',' << q << '\t';
            s.insert(p*p + q*q);
        }
    }

    int maxVal = bsq*bsq + bsq*bsq;
    vector<vector<int>> dp(seqLen+1, vector<int>(maxVal, 0));
    for (int len = 1; len <= seqLen; ++len) {
        cout << len << '\n';
        for (int i = 0; i <= maxVal; ++i) {
            if (s.count(i)) {
                if (i < len) {
                    dp[len][i] = 1;
                } else {
                    dp[len][i] = 1 + dp[len][i-len];
                }
                if (dp[len][i] == seqLen) {
                    fout << i - (seqLen - 1) * len << ' ' << len << '\n';
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
