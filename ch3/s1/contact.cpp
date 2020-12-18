/*
ID: sketchc1
LANG: C++14
TASK: contact
*/
#include <bits/stdc++.h>
using namespace std;

struct SizeLex {
    bool operator()(const string& lhs, const string& rhs) const {
        if (lhs.size() != rhs.size()) {
            return lhs.size() < rhs.size();
        } else {
            return lhs < rhs;
        }
    }
};

int main() {
    // i/o
    ifstream fin("contact.in");
    ofstream fout("contact.out");

    int minBits, maxBits, patterns;

    fin >> minBits >> maxBits >> patterns;
    fin.ignore(INT32_MAX, '\n');
    string temp, s;
    while (getline(fin, temp)) {
        s += move(temp);
    }
    unordered_map<string, int> counter;
    for (int len = minBits; len <= maxBits; ++len) {
        // cout << "LEN " << len << "\n\n";
        for (int i = 0; i + len <= s.size(); ++i) {
            counter[s.substr(i, len)]++;
        }
    }
    // for (auto&& kv : counter) {
    //     cout << kv.first << ':' << kv.second << '\n';
    // }
    map<int, set<string, SizeLex>, greater<int>> revMap;
    for (auto&& kv : counter) {
        revMap[kv.second].insert(kv.first);
    }
    int count = 0;
    for (auto&& kv : revMap) {
        ++count;
        fout << kv.first << '\n';

        int subcount = 1;
        for (auto str : kv.second) {
            fout << str;
            if (subcount % 6 == 0 || subcount == kv.second.size()) {
                fout << '\n';
            } else {
                fout << ' ';
            }
            subcount++;
        }
        if (count == patterns) {
            break;
        }
    }


    return EXIT_SUCCESS;
}
