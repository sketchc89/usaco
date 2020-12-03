/*
ID: sketchc1
LANG: C++14
TASK: milk
*/
#include <bits/stdc++.h>
using namespace std;


int main() {
    // i/o
    ifstream fin("milk.in");
    ofstream fout("milk.out");

    int demand, numFarmers;
    fin >> demand >> numFarmers;

    vector<pair<int, int>> milk(numFarmers);
    int price, supply;
    for (int i = 0; i < numFarmers; ++i) {
        fin >> price >> supply;
        milk[i] = make_pair(price, supply);
    }
    sort(begin(milk), end(milk));

    int cost = 0;
    for (int i = 0; i < numFarmers; ++i) {
        if (demand > milk[i].second) {
            demand -= milk[i].second;
            cost += milk[i].first * milk[i].second;
        } else {
            cost += milk[i].first * demand;
            break;
        }
    }

    fout << cost << '\n';

    return EXIT_SUCCESS;
}
