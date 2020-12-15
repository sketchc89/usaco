/*
ID: sketchc1
LANG: C++14
TASK: fracdec
*/
#include <bits/stdc++.h>
using namespace std;


int main() {
    // i/o
    ifstream fin("fracdec.in");
    ofstream fout("fracdec.out");

    int num, den;
    fin >> num >> den;
    int whole = num / den;
    int rem = num % den;
    string res = "";
    res += to_string(whole);
    res.push_back('.');
    unordered_map<int, int> seen;
    int idx = res.size();
    if (rem == 0) {
        res.push_back('0');
    }
    while (rem) {
        rem *= 10;
        char val = rem / den + '0';
        auto it = seen.find(rem);
        if (it != end(seen)) {
            res.insert(seen[rem], 1, '(');
            res.push_back(')');
            break;
        } else {
            seen.insert({rem, idx});
            res.push_back(val);
        }
        rem %= den;
        ++idx;
    }

    if (res.size() < 76) {
        fout << res;
    } else {
        for (int i = 0; i < res.size(); ++i) {
            if (i % 76 == 0 && i != 0) {
                fout << '\n';
            }
            fout << res[i];
        }
    }
    fout << '\n';

    return EXIT_SUCCESS;
}
