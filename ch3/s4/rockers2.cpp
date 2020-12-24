/*
ID: sketchc1
LANG: C++14
TASK: rockers
*/
#include <bits/stdc++.h>
using namespace std;

/* alternative recursive version for this problem */
void raucous(
        int currSong,
        int totalSongs,
        int disksUsed,
        int timeUsed,
        int& res,
        const int numDisks,
        const int timePerDisk,
        const vector<int>& songs) {
    if (currSong == songs.size()) {
        res = max(res, totalSongs);
        return;
    }

    // dont include current song
    raucous(currSong + 1, totalSongs, disksUsed, timeUsed, res, numDisks, timePerDisk, songs);
    if (songs[currSong] <= timePerDisk - timeUsed) {  // put on current disk
        raucous(currSong + 1, totalSongs + 1, disksUsed, timeUsed + songs[currSong], res, numDisks, timePerDisk, songs);
    } else if (disksUsed + 1 < numDisks && songs[currSong] <= timePerDisk) {  // put on next disk
        raucous(currSong + 1, totalSongs + 1, disksUsed + 1, songs[currSong], res, numDisks, timePerDisk, songs);
    }
}

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
    raucous(0, 0, 0, 0, res, numDisks, timePerDisk, songs);
    ofstream fout("rockers.out");
    fout << res << '\n';


    return EXIT_SUCCESS;
}
