/*
ID: sketchc1
LANG: C++14
TASK: holstein
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> addElement(const vector<int>& combs, int n) {
    vector<int> res;
    for (auto comb : combs) {
        for (int i = 0; i < n; ++i) {
            if (comb & 1 << i == 0) {
                res.push_back(comb | 1 << i);
            }
        }
    }
    return res;
}


int main() {
    // i/o
    ifstream fin("holstein.in");
    ofstream fout("holstein.out");

    int V;
    fin >> V;
    vector<int> vitamins(V);
    for (int v = 0; v < vitamins.size(); ++v) {
        fin >> vitamins[v];
    }

    int N;
    fin >> N;
    vector<vector<int>> feeds(N, vector<int>(V, 0));
    for (int n = 0; n < feeds.size(); ++n) {
        for (int v = 0; v < feeds[n].size(); ++v) {
            fin >> feeds[n][v];
        }
    }
    // cout << "HELLO FRIENDS\n";

    // vector<vector<int>> combs(1 << N, vector<int>(V, 0));
    auto combs = array<array<int, 25>, 32768>{};
    int bestComb = -1;
    bool adequate = false;
    for (int comb = 1; comb < (1 << N); ++comb) {
        int addedFeed = 31 - __builtin_clz(comb);
        int prevComb = comb ^ (1 << (addedFeed));
        // cout << std::bitset<15>(comb) << '\t' << __builtin_clz(comb) << '\t' << std::bitset<15>(prevComb) << '\n';
        for (int v = 0; v < vitamins.size(); ++v) {
            combs[comb][v] = feeds[addedFeed][v] + combs[prevComb][v];
        }
    }
    // 000001
    // 000101
    // for (int v = 0; v < vitamins.size(); ++v) {
    //     vit[v] += feeds[i][v];
    // }
    int minVit = INT32_MAX;
    int minScoops = INT32_MAX;
    for (int comb = 1; comb < 1 << N; ++comb) {
        // cout << std::bitset<15>(comb) << ':';
        bool adequate = true;
        for (int v = 0; v < vitamins.size(); ++v) {
            // cout << combs[comb][v] << '\t';
            if (combs[comb][v] < vitamins[v]) {
                // cout << "INADEQUATE!";
                adequate = false;
                break;
            }
        }
        // cout << '\n';
        int scoops = __builtin_popcount(comb);
        // cout << "Scoops: " << scoops << '\n';
        if (adequate && scoops <= minScoops) {
            auto sum = accumulate(begin(combs[comb]), end(combs[comb]), 0);
            if (scoops < minScoops || sum < minVit) {
                // cout << "Replacing " << bestComb << " with " << comb << '\n';
                minScoops = __builtin_popcount(comb);
                bestComb = comb;
                minVit = sum;
            }
        }
    }
    fout << minScoops;
    // cout << bitset<15>(bestComb) << '\n';
    // cout << bitset<15>(bestComb & (1 << 1)) << '\n';
    for (int i = 0; i < N; ++i) {
        if ((bestComb & (1 << i)) == 0) {
            // cout << "skipping " << i << '\n';
            continue;
        }
        fout << ' ' << i + 1;
    }
    fout << '\n';

    return EXIT_SUCCESS;
}
