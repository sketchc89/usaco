/*
ID: sketchc1
LANG: C++14
TASK: combo
*/
#include <bits/stdc++.h>
using namespace std;


int main() {
    // i/o
    ifstream fin("combo.in");
    ofstream fout("combo.out");

    int N;
    fin >> N;
    vector<int> settings(6);
    for (int i = 0; i < settings.size(); ++i) {
        fin >> settings[i];
        settings[i]--;
    }

    unordered_set<int> first, second, third;
    constexpr int err = 2;
    for (int i = -err; i <= err; ++i) {
        first.insert(((settings[0] + i) % N + N) % N + 1);
        second.insert(((settings[1] + i) % N + N) % N + 1);
        third.insert(((settings[2] + i) % N + N) % N + 1);
    }

    vector<vector<vector<int>>> combs(N + 1, vector<vector<int>>(N + 1, vector<int>(N + 1, 0)));
    int comb = 0;
    for (auto f : first) {
        for (auto s : second) {
            for (auto t : third) {
                if (!combs[f][s][t]) {
                    // cout << f << ',' << s << ',' << t << '\t';
                    ++comb;
                    combs[f][s][t] = 1;
                }
            }
            // cout << '\n';
        }
        // cout << '\n';
    }

    first.clear();
    second.clear();
    third.clear();
    for (int i = -err; i <= err; ++i) {
        first.insert(((settings[3] + i) % N + N) % N + 1);
        second.insert(((settings[4] + i) % N + N) % N + 1);
        third.insert(((settings[5] + i) % N + N) % N + 1);
    }
    for (auto f : first) {
        for (auto s : second) {
            for (auto t : third) {
                if (!combs[f][s][t]) {
                    // cout << f << ',' << s << ',' << t << '\t';
                    ++comb;
                    combs[f][s][t] = 1;
                }
            }
            // cout << '\n';
        }
        // cout << '\n';
    }
    fout << comb << '\n';
    return EXIT_SUCCESS;
}
