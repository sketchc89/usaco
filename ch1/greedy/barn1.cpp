/*
ID: sketchc1
LANG: C++14
TASK: barn1
*/
#include <bits/stdc++.h>
using namespace std;


int main() {
    // i/o
    ifstream fin("barn1.in");
    ofstream fout("barn1.out");

    int numBoards, numStalls, numCows;
    fin >> numBoards >> numStalls >> numCows;

    // special case, lots of boards
    if (numBoards >= numCows) {
        fout << numCows << '\n';
        return EXIT_SUCCESS;
    }

    vector<int> stall(numCows);
    for (int i = 0; i < stall.size(); ++i) {
        fin >> stall[i];
    }
    sort(begin(stall), end(stall));
    vector<pair<int, int>> diff(numCows);
    diff[0] = make_pair(INT32_MAX, stall[0]);
    for (int i = 1; i < diff.size(); ++i) {
        diff[i] = make_pair(stall[i] - stall[i - 1], stall[i]);
    }
    sort(begin(diff), end(diff), greater<>());


    // for (int i = 0; i < numBoards; ++i) {
    //     cout << "not covering stalls before " << diff[i].second << " with space " << diff[i].first << '\n';
    // }

    int totalDiff = numBoards;
    for (int i = numBoards; i < diff.size(); ++i) {
        // cout << "covering stall before " << diff[i].second << " with space " << diff[i].first << '\n';
        totalDiff += diff[i].first;
    }
    fout << totalDiff << '\n';

    return EXIT_SUCCESS;
}
