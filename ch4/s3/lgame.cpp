/*
ID: sketchc1
LANG: C++14
TASK: ditch
*/

#include <bits/stdc++.h>
using namespace std;

void generateCombinations(int idx, string& curr, const string& s, unordered_map<string, int>& sBag) {
    if (idx == s.size()) {
        if (curr.size() >= 3) {
            sBag.insert({curr, 0});
        }
        return;
    }
    curr.push_back(s[idx]);
    generateCombinations(idx + 1, curr, s, sBag);
    curr.pop_back();
    generateCombinations(idx + 1, curr, s, sBag);
}

int main() {
    ifstream fin("lgame.in"), fdict("lgame.dict");
    ofstream fout("lgame.out");

    vector<int> points{
            2, 5, 4, 4, 1, 6, 5, 5, 1, 7,  //
            6, 3, 5, 2, 3, 5, 7, 2, 1, 2,  //
            4, 6, 6, 7, 5, 7               //
    };

    string s, w;
    fin >> s;
    sort(begin(s), end(s));
    int64_t val;
    unordered_map<string, vector<string>> dict;
    unordered_map<string, int> stringBag;
    string curr = "";
    generateCombinations(0, curr, s, stringBag);
    for (auto& str : stringBag) {
        for (char c : str.first) {
            str.second += points[c - 'a'];
        }
        // cout << str.first << ':' << str.second << '\n';
    }
    while (fdict >> w) {
        if (w == ".") {
            break;
        }
        if (w.size() > s.size()) {
            continue;
        }
        auto sortW = w;
        sort(begin(sortW), end(sortW));
        auto it = dict.find(sortW);
        dict[sortW].push_back(w);
    }
    vector<string> bestStr;
    int bestPoints = 0;
    for (auto&& str : stringBag) {
        auto it = dict.find(str.first);
        if (it != dict.end()) {
            // cout << "Found " << str.first << " for " << str.second << " points\n";
            if (str.second > bestPoints) {
                bestStr.clear();
                bestStr.insert(end(bestStr), begin(it->second), end(it->second));
                bestPoints = str.second;
            } else if (str.second == bestPoints) {
                bestStr.insert(end(bestStr), begin(it->second), end(it->second));
            }
        }
    }
    cout << bestPoints << '\n';
    for (auto&& bs : bestStr) {
        cout << bs << '\n';
    }

    return EXIT_SUCCESS;
}
