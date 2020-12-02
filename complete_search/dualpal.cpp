/*
ID: sketchc1
LANG: C++14
TASK: dualpal
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
    ifstream fin("dualpal.in");
    ofstream fout("dualpal.out");

    int nums, startNum;
    fin >> nums >> startNum;

    int num = startNum + 1;
    while (nums) {
        int count = 0;
        for (int b = 2; b <= 10; ++b) {
            auto s = convertBaseFrom10(num, b);
            if (isPalindrome(s)) {
                ++count;
            }
        }
        if (count >= 2) {
            --nums;
            fout << num << '\n';
        }
        ++num;
    }

    return EXIT_SUCCESS;
}
