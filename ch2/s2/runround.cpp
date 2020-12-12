/*
ID: sketchc1
LANG: C++14
TASK: runround
*/
#include <bits/stdc++.h>
using namespace std;

bool isRunaround(int num) {
    string str = to_string(num);
    int n = str.size();
    unordered_set<int> s, uniq(begin(str), end(str));
    if (uniq.size() != str.size()) {
        return false;
    }
    int idx = 0;
    s.insert(0);
    while (true) {
        idx = (idx + (str[idx] - '0')) % n;
        if (s.count(idx)) {
            if (idx == 0 && s.size() == n) {
                return true;
            } else {
                return false;
            }
        } else {
            s.insert(idx);
        }
    }
    cout << '\n';
    return false;
}


int main() {
    // i/o
    ifstream fin("runround.in");
    ofstream fout("runround.out");

    uint64_t num;
    fin >> num;
    for (uint64_t i = num + 1ULL; i <= INT64_MAX; ++i) {
        if (isRunaround(i)) {
            fout << i << '\n';
            return EXIT_SUCCESS;
        }
    }

    return EXIT_SUCCESS;
}
