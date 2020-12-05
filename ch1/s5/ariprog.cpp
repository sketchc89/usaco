/*
ID: sketchc1
LANG: C++14
TASK: ariprog
*/
#include <bits/stdc++.h>
using namespace std;


int main() {
    // i/o
    ifstream fin("ariprog.in");
    ofstream fout("ariprog.out");

    int seqLen, bsq;
    fin >> seqLen >> bsq;

    set<int> s;
    auto arr = array<bool, 125001>{};
    for (int p = 0; p <= bsq; ++p) {
        for (int q = 0; q <= bsq; ++q) {
            arr[p * p + q * q] = true;
        }
    }
    int maxVal = bsq * bsq * 2;
    int maxDiff = maxVal / (seqLen - 1);

    vector<pair<int, int>> res;
    for (int val = 0; val <= maxVal; ++val) {
        if (!arr[val]) {
            continue;
        }
        for (int len = 1; len <= maxDiff; ++len) {
            if (len * (seqLen - 1) > val) {
                break;
            }
            auto temp = val;
            int count = 1;
            while (temp >= 0 && arr[temp]) {
                if (count >= seqLen) {
                    res.emplace_back(make_pair(temp, len));
                }
                temp -= len;
                ++count;
            }
        }
    }
    if (res.size() == 0) {
        fout << "NONE\n";
    } else {
        sort(begin(res), end(res), [](const auto& p1, const auto& p2) {
            if (p1.second != p2.second) {
                return p1.second < p2.second;
            }
            return p1.first < p2.first;
        });
        res.erase(unique(begin(res), end(res)), end(res));
        for (auto&& p : res) {
            fout << p.first << ' ' << p.second << '\n';
        }
    }

    return EXIT_SUCCESS;
}
