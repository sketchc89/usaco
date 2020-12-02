/*
ID: sketchc1
LANG: C++14
TASK: palsquare
*/
#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(const string& s) {
    for (int i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size() - 1 - i]) {
            return false;
        }
    }
    return true;
}

string convertBaseFrom10(int n, int toBase) {
    const static string BASE_STR = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string res = "";
    while (n) {
        res.push_back(BASE_STR[n % toBase]);
        n /= toBase;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    // i/o
    ifstream fin("palsquare.in");
    ofstream fout("palsquare.out");

    int targetBase;
    fin >> targetBase;

    for (int i = 1; i < 300; ++i) {
        auto s = convertBaseFrom10(i, targetBase);
        auto t = convertBaseFrom10(i * i, targetBase);
        if (isPalindrome(t)) {
            fout << s << ' ' << t << '\n';
        }
    }
    return EXIT_SUCCESS;
}
