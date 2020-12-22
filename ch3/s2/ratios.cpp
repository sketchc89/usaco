/*
ID: sketchc1
LANG: C++14
TASK: ratios
*/
#include <bits/stdc++.h>
using namespace std;

constexpr static int NUM_MIXES = 3;
constexpr static int MAX_MIX = 128;

struct Mix {
    Mix()
            : a{}
            , b{}
            , c{} {}
    Mix(int _a, int _b, int _c)
            : a{_a}
            , b{_b}
            , c{_c} {}
    int a, b, c;
};

Mix operator+(const Mix& lhs, const Mix& rhs) {
    return Mix(lhs.a + rhs.a, lhs.b + rhs.b, lhs.c + rhs.c);
}


void checkMix(int a, int b, int c, Mix& m, vector<vector<vector<int>>>& dp) {
    if (a - m.a < 0 || b - m.b < 0 || c - m.c < 0) {
        // cout << "Not enough food\n";
        return;
    }
    if (dp[a - m.a][b - m.b][c - m.c] == -1) {
        return;
    }
    if (dp[a][b][c] == -1) {
        dp[a][b][c] = dp[a - m.a][b - m.b][c - m.c] + 1;
    } else {
        dp[a][b][c] = min(dp[a][b][c], dp[a - m.a][b - m.b][c - m.c] + 1);
    }
}

void findMixes(vector<int>& cnt, Mix& m, const vector<Mix>& mixes, const vector<vector<vector<int>>>& dp) {
    for (int i = 0; i < NUM_MIXES; ++i) {
        // check that it is in range and
        if (m.a - mixes[i].a >= 0 && m.b - mixes[i].b >= 0 && m.c - mixes[i].c >= 0
            && dp[m.a][m.b][m.c] == 1 + dp[m.a - mixes[i].a][m.b - mixes[i].b][m.c - mixes[i].c]) {
            // cout << "Before mix: " << m.a << ',' << m.b << ',' << m.c << "\tcnt: " << cnt[0] << ',' << cnt[1] << ',' << cnt[2] << '\n';
            m.a -= mixes[i].a;
            m.b -= mixes[i].b;
            m.c -= mixes[i].c;
            cnt[i]++;
            // cout << "After mix: " << m.a << ',' << m.b << ',' << m.c << "\tcnt: " << cnt[0] << ',' << cnt[1] << ',' << cnt[2] << '\n';
            findMixes(cnt, m, mixes, dp);
            break;
        }
    }
}

int main() {
    // i/o
    ifstream fin("ratios.in");
    ofstream fout("ratios.out");

    Mix goal;
    vector<Mix> mixes(NUM_MIXES);
    fin >> goal.a >> goal.b >> goal.c;
    for (int i = 0; i < mixes.size(); ++i) {
        fin >> mixes[i].a >> mixes[i].b >> mixes[i].c;
    }

    vector<vector<vector<int>>> dp(MAX_MIX, vector<vector<int>>(MAX_MIX, vector<int>(MAX_MIX, -1)));
    dp[0][0][0] = 0;
    for (int a = 0; a < MAX_MIX; ++a) {
        // cout << "A=" << a << '\t';
        // for (int d = 1; d < MAX_MIX; ++d) {
        //     cout << setw(3) << d;
        // }
        // cout << '\n';
        for (int b = 0; b < MAX_MIX; ++b) {
            // cout << b << '\t';
            for (int c = 0; c < MAX_MIX; ++c) {
                for (int m = 0; m < NUM_MIXES; ++m) {
                    checkMix(a, b, c, mixes[m], dp);
                }
                // if (dp[a][b][c] == -1) {
                //     cout << setw(3) << "-";
                // } else {
                //     cout << setw(3) << dp[a][b][c];
                // }
            }
            // cout << '\n';
        }
        // cout << '\n';
    }

    // cout << "Done checking\n";
    for (int fact = 1; fact < MAX_MIX; ++fact) {
        // cout << "Factor " << fact << '\n';
        // cout << fact * goal.a << '\t' << fact * goal.b << '\t' << fact * goal.c << '\n';
        if (fact * goal.a >= MAX_MIX || fact * goal.b > MAX_MIX || fact * goal.c >= MAX_MIX) {
            fout << "NONE\n";
            break;
        } else if (dp[fact * goal.a][fact * goal.b][fact * goal.c] != -1) {
            vector<int> cnt(NUM_MIXES, 0);
            Mix g(fact * goal.a, fact * goal.b, fact * goal.c);
            findMixes(cnt, g, mixes, dp);
            // cout << cnt[0] << ' ' << cnt[1] << ' ' << cnt[2] << ' ' << fact << '\n';
            fout << cnt[0] << ' ' << cnt[1] << ' ' << cnt[2] << ' ' << fact << '\n';
            break;
        }
    }

    return EXIT_SUCCESS;
}
