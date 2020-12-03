/*
ID: sketchc1
LANG: C++14
TASK: gift1
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // i/o
    ifstream fin("gift1.in");
    ofstream fout("gift1.out");

    string name, giver, receiver, numStr, npStr;
    getline(fin, npStr);
    istringstream ss(npStr);
    int np;
    ss >> np;

    vector<string> nameVec(np);
    map<string, int> names;
    for (int i = 0; i < np; ++i) {
        getline(fin, name);
        nameVec[i] = name;
        names.emplace(make_pair(name, 0));
    }

    int amount, split;
    int count = 1000;
    while (getline(fin, giver)) {
        getline(fin, numStr);
        istringstream ss(numStr);
        ss >> amount >> split;

        for (int i = 0; i < split; ++i) {
            getline(fin, receiver);
            names[receiver] += amount / split;
            names[giver] -= amount / split;
        }
    }
    for (int i = 0; i < np; ++i) {
        fout << nameVec[i] << ' ' << names[nameVec[i]] << '\n';
    }

    return EXIT_SUCCESS;
}
