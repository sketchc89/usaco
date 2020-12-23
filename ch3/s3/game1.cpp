/*
ID: sketchc1
LANG: C++14
TASK: game1
*/
#include <bits/stdc++.h>
using namespace std;

int bestScore(int left, int right, const vector<int>& vi, vector<vector<int>>& dp) {
    // out of range
    if (left < 0 || right < 0 || left >= vi.size() || right >= vi.size() || right < left) {
        return 0;
    }
    // already found
    if (dp[left][right] != -1) {
        return dp[left][right];
    }

    // the best score is the better of:
    // choose left plus the best of array left+1->right after the other player chooses
    // choose right plus the best of array left->right-1 after the other player chooses
    // the other player always chooses best so choose we are left with the lesser of
    // other player chooses left / other player chooses right
    int res =
            max(vi[left] + min(bestScore(left + 1, right - 1, vi, dp), bestScore(left + 2, right, vi, dp)),
                vi[right] + min(bestScore(left, right - 2, vi, dp), bestScore(left + 1, right - 1, vi, dp)));

    dp[left][right] = res;
    return dp[left][right];
}

int main() {
    // i/o
    ifstream fin("game1.in");
    ofstream fout("game1.out");

    int N;
    fin >> N;
    if (N == 2) {
        int a, b;
        fin >> a >> b;
        fout << max(a, b) << ' ' << min(a, b) << '\n';
        return EXIT_SUCCESS;
    }
    vector<int> vi(N);
    for (int i = 0; i < vi.size(); ++i) {
        fin >> vi[i];
    }
    vector<vector<int>> dp(N, vector<int>(N, -1));
    for (int i = 0; i < N; ++i) {
        dp[i][i] = vi[i];
    }

    int p1Score = bestScore(0, N - 1, vi, dp);
    // maybe there's a better way to calculate this along the way with an array of choices or something
    int p2Score;
    if (vi[0] + min(dp[1][N - 2], dp[2][N - 1]) > vi[N - 1] + min(dp[1][N - 2], dp[0][N - 3])) {
        p2Score = bestScore(1, N - 1, vi, dp);
    } else {
        p2Score = bestScore(0, N - 2, vi, dp);
    }

    fout << p1Score << ' ' << p2Score << '\n';

    return EXIT_SUCCESS;
}
