/*
ID: sketchc1
LANG: C++14
TASK: frac1
*/
#include <bits/stdc++.h>
using namespace std;


int main() {
    // i/o
    ifstream fin("frac1.in");
    ofstream fout("frac1.out");

    int n;
    fin >> n;
    map<double, pair<int, int>> fracs;
    for (int bot = 1; bot <= n; ++bot) {
        for (int top = 0; top <= bot; ++top) {
            auto it = fracs.find(static_cast<double>(top) / bot);
            if (it == fracs.end()) {
                fracs[static_cast<double>(top) / bot] = {top, bot};
            }
        }
    }
    for (auto&& kv : fracs) {
        fout << kv.second.first << '/' << kv.second.second << '\n';
    }

    return EXIT_SUCCESS;
}
