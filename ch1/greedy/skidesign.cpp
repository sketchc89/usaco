/*
ID: sketchc1
LANG: C++14
TASK: skidesign
*/
#include <bits/stdc++.h>
using namespace std;


int main() {
    // i/o
    ifstream fin("skidesign.in");
    ofstream fout("skidesign.out");

    int numHills;
    fin >> numHills;
    map<int, int> hills;
    int height;
    for (int i = 0; i < numHills; ++i) {
        fin >> height;
        hills[height]++;
    }

    int low = begin(hills)->first;
    int high = prev(end(hills))->first;
    int minCost = INT32_MAX;
    for (int lo = low; lo + 17 <= high; ++lo) {
        int hi = lo + 17;
        int cost = 0;
        // cout << lo << '-' << hi << '\t';
        for (auto&& kv : hills) {
            if (kv.first < lo) {
                cost += kv.second * pow(lo - kv.first, 2);
            } else if (kv.first > hi) {
                cost += kv.second * pow(kv.first - hi, 2);
            }
        }
        // cout << cost << '\n';
        if (cost < minCost) {
            minCost = cost;
        }
    }
    fout << minCost << '\n';


    return EXIT_SUCCESS;
}
