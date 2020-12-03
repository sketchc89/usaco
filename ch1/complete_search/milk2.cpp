/*
ID: sketchc1
LANG: C++14
TASK: milk2
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // i/o
    ifstream fin("milk2.in");
    ofstream fout("milk2.out");

    int cows, start, end;
    fin >> cows;
    map<int, int> milkTime;
    for (int cow = 0; cow < cows; ++cow) {
        fin >> start >> end;
        milkTime[start]++;
        milkTime[end]--;
    }
    int curMilking = 0, curTime = 0, unmilkedTime = INT32_MIN, milkedTime = INT32_MIN;
    int startTime = begin(milkTime)->first, stopTime;
    bool milking = false;
    bool init = false;
    for (auto it = begin(milkTime); it != milkTime.end(); ++it) {
        curMilking += it->second;
        curTime = it->first;
        // cout << "Milking " << curMilking << " cows at time " << curTime << '\n';
        if (curMilking == 0 || it == prev(milkTime.end())) {  // not milking
            if (milking) {
                milkedTime = init ? max(milkedTime, curTime - startTime) : 0;
                stopTime = curTime;
                milking = false;
            }
        } else {  // done milking
            if (!milking) {
                unmilkedTime = init ? max(unmilkedTime, curTime - stopTime) : 0;
                startTime = curTime;
                milking = true;
            }
        }
        init = true;
    }

    if (milkedTime == INT32_MIN) {
        milkedTime = 0;
    }
    if (unmilkedTime == INT32_MIN) {
        unmilkedTime = 0;
    }
    fout << milkedTime << ' ' << unmilkedTime << '\n';


    return EXIT_SUCCESS;
}
