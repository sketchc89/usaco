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

    int res = 0;
    for (int disk = 0; disk < numDisks; ++disk) {
        cout << "\nWorking on disk " << disk << '\n';
        vector<vector<int>> dp(timePerDisk + 1);
        dp[0].push_back(-1);  // sentinel value
        for (int i = 0; i < songs.size(); ++i) {
            cout << "\nSong# " << i << " with duration " << songs[i] << '\t';
            if (songs[i] == -1) {
                continue;
            }
            for (int t = timePerDisk; t >= songs[i]; --t) {
                if (dp[t - songs[i]].size() > 0) {
                    cout << "\tCan put at time " << t << '\t';
                    if (dp[t].size() < dp[t - songs[i]].size() + 1) {
                        dp[t].clear();
                        for (auto idx : dp[t - songs[i]]) {
                            if (idx != -1) {
                                dp[t].push_back(idx);
                            }
                        }
                        dp[t].push_back(i);
                    } else {
                        cout << " wouldnt improve disk\t";
                    }
                    cout << "Size at time " << t << " is " << dp[t].size();
                }
            }
        }
        int songsOnDisk = 0;
        int timeToDelete = 0;
        cout << "\nFinding new most songs\n";
        for (int t = 1; t <= timePerDisk; ++t) {
            if (dp[t].size() >= songsOnDisk) {
                songsOnDisk = dp[t].size();
                timeToDelete = t;
                cout << "New most songs " << songsOnDisk << " with time " << timeToDelete << '\n';
            }
        }
        if (songsOnDisk == 0) {
            cout << "No songs on disk!\n";
            break;
        }
        res += songsOnDisk;
        cout << "There are " << songsOnDisk << " songs on Disk# " << disk << '\n';
        cout << "There are " << res << " total songs on all disks\n";
        cout << "Deleting songs in time " << timeToDelete << " for disk: " << disk << " used songs: ";
        for (int song = 0; song < dp[timeToDelete].size(); ++song) {
            cout << dp[timeToDelete][song] << '\t';
            songs[dp[timeToDelete][song]] = -1;
        }
        cout << '\n';
    }
    ofstream fout("rockers.out");
    fout << res << '\n';


    return EXIT_SUCCESS;
}
