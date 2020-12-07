/*
ID: sketchc1
LANG: C++14
TASK: hamming
*/
#include <bits/stdc++.h>
using namespace std;


int main() {
    // i/o
    ifstream fin("hamming.in");
    ofstream fout("hamming.out");

    int numWords, numBits, hDist;
    fin >> numWords >> numBits >> hDist;
    queue<int> q;
    set<int> seen, codes;
    q.push(0);
    while (!q.empty()) {
        auto num = q.front();
        q.pop();
        if (seen.count(num)) {
            continue;
        } else {
            seen.insert(num);
        }
        // cout << "Checking " << num << '\n';
        bool valid = true;
        for (auto n : codes) {
            if (__builtin_popcount(n ^ num) < hDist) {
                valid = false;
                break;
            }
        }
        if (!valid) {
            continue;
        }
        // cout << "Found new code " << num << '\n';
        codes.insert(num);
        if (codes.size() == numWords) {
            break;
        }
        for (int i = 0; i < (1 << numBits); ++i) {
            if (__builtin_popcount(i ^ num) >= hDist) {
                q.push(i);
            }
        }
    }
    for (auto it = begin(codes); it != end(codes); ++it) {
        auto d = distance(begin(codes), it);
        if (d == 0) {
            fout << *it;
        } else if (d % 10 == 0) {
            fout << '\n' << *it;
        } else {
            fout << ' ' << *it;
        }
    }
    fout << '\n';


    // for (int i = 0; i < (1 << numBits); ++i) {
    //     vector<int> vi;
    //     vi.push_back(i);
    //     for (int j = 0; j < (1 << numBits); ++j) {
    //         if (__builtin_popcount(i ^ j) >= hDist) {
    //             cout << __builtin_popcount(i ^ j) << '\n';
    //             cout << bitset<7>(i) << '\n'    //
    //                  << bitset<7>(j) << '\n'    //
    //                  << string('-', 8) << '\n'  //
    //                  << bitset<7>(i ^ j) << '\n';
    //             vi.push_back(j);
    //         }
    //     }
    //     if (vi.size() >= numWords) {
    //         fout << vi[0];
    //         for (int w = 1; w < numWords; ++w) {
    //             if (w % 10 == 0) {
    //                 fout << '\n';
    //             }
    //             fout << ' ' << vi[w];
    //         }
    //         fout << '\n';
    //     }
    // }


    return EXIT_SUCCESS;
}
