/*
ID: sketchc1
LANG: C++14
TASK: prefix
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // i/o
    ifstream fin("prefix.in");
    ofstream fout("prefix.out");

    unordered_set<string> prefixes;
    for (;;) {
        string s;
        fin >> s;
        if (s == ".") {
            break;
        } else {
            prefixes.insert(s);
        }
    }
    string sequence, seq;
    while (fin >> seq) {
        sequence += move(seq);
    }

    vector<int> dp(sequence.size() + 1, 0);
    dp[0] = 1;
    int longest = 0;
    for (int start = 0; start < sequence.size(); ++start) {
        if (!dp[start]) {
            continue;
        }
        longest = start;
        for (auto p : prefixes) {
            if (p == sequence.substr(start, p.size())) {
                dp[start + p.size()] = 1;
            }
        }
    }

    fout << longest << '\n';

    return EXIT_SUCCESS;
}
