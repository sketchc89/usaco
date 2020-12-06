/*
ID: sketchc1
LANG: C++14
TASK: crypt1
*/
#include <bits/stdc++.h>
using namespace std;


int main() {
    // i/o
    ifstream fin("crypt1.in");
    ofstream fout("crypt1.out");

    int numDigits;
    fin >> numDigits;
    vector<int> dig(numDigits);
    unordered_set<int> threes, twos, digits;

    for (int i = 0; i < numDigits; ++i) {
        fin >> dig[i];
        digits.insert(dig[i]);
    }
    for (int i = 111; i <= 999; ++i) {
        if (digits.count(i / 100) && digits.count((i / 10) % 10) && digits.count(i % 10)) {
            threes.insert(i);
            // cout << i << ' ';
        }
    }
    cout << '\n';
    for (int i = 11; i <= 99; ++i) {
        if (digits.count(i / 10) && digits.count(i % 10)) {
            twos.insert(i);
            // cout << i << ' ';
        }
    }
    int solutions = 0;
    for (auto three : threes) {
        for (auto two : twos) {
            auto prod1 = two % 10 * three;
            if (two == 22 && three == 222) {
                // fout << "HI!\n";
            }
            if (prod1 > 999 || threes.count(prod1) == 0) {
                // fout << "Prod1 failed " << prod1 << '\n';
                continue;
            }
            auto prod2 = two / 10 * three;
            if (prod2 > 999 || threes.count(prod2) == 0) {
                // fout << "Prod2 failed " << prod2 << '\n';
                continue;
            }
            auto sum = 10 * prod1 + prod2;
            if (sum > 9999 || threes.count(sum / 10) == 0 || threes.count(sum - sum / 1000 * 1000) == 0) {
                // fout << "Sum failed " << sum << '\t' << sum / 10 << '\t' << sum - sum / 1000 * 1000 << '\n';
                continue;
            }
            ++solutions;
            // fout << "  " << three << "\n   " << two << "\n------\n  " << prod1 << "\n " << prod2 << "\n------\n " << sum << '\n';
        }
    }
    fout << solutions << '\n';

    // for (auto num : threes) {
    //     cout << num << ' ';
    // }
    // cout << '\n';
    // for (auto num : twos) {
    //     cout << num << ' ';
    // }
    // cout << '\n';


    return EXIT_SUCCESS;
}
