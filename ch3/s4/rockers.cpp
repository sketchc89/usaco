/*
ID: sketchc1
LANG: C++14
TASK: rockers
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // i/o
    ifstream fin("rockers.in");

    int numSongs, timePerDisk, numDisks;
    fin >> numSongs >> timePerDisk >> numDisks;

    vector<int> songs(numSongs);
    for (int i = 0; i < songs.size(); ++i) {
        fin >> songs[i];
    }

    vector<vector<int>> dp(numDisks, vector<int>(timePerDisk + 1, 0));
    for (int song = 0; song < songs.size(); ++song) {
        // cout << "\nSong# " << song << " with duration " << songs[song] << '\n' << string(30, '-');
        const auto duration = songs[song];
        for (int disk = numDisks - 1; disk >= 0; --disk) {
            // cout << "\nWorking on disk " << disk << '\n';
            for (int timeLeft = 0; timeLeft <= timePerDisk; ++timeLeft) {
                // cout << "Time left on disk is " << timeLeft << '\t';
                if (timeLeft < duration) {
                    if (duration <= timePerDisk && disk < numDisks - 1) {
                        // cout << "Added onto next disk already processed\t";
                        dp[disk + 1][timePerDisk - duration] = max(dp[disk + 1][timePerDisk - duration], dp[disk][timeLeft] + 1);
                        // cout << "Now max songs that can fit on disk " << disk + 1 << " with " << timePerDisk - duration << " time left is
                        // "
                        //      << dp[disk + 1][timePerDisk - duration] << '\t';
                    }
                } else {
                    dp[disk][timeLeft - duration] = max(dp[disk][timeLeft - duration], dp[disk][timeLeft] + 1);
                    // cout << "Tried adding to current disk\t";
                    // cout << "Now max songs that can fit on disk " << disk << " with " << timeLeft - duration << " time left is "
                    //      << dp[disk][timeLeft - duration] << '\t';
                }
                // cout << '\n';
            }
        }
    }
    int res = 0;
    for (int i = 0; i < dp.size(); ++i) {
        for (int j = 0; j < dp[i].size(); ++j) {
            res = max(res, dp[i][j]);
        }
    }
    ofstream fout("rockers.out");
    fout << res << '\n';


    return EXIT_SUCCESS;
}
