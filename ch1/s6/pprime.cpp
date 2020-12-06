/*
ID: sketchc1
LANG: C++14
TASK: pprime
*/
#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(int val) {
    string s = to_string(val);
    int N = s.size();
    for (int i = 0; i < N / 2; ++i) {
        if (s[i] != s[N - 1 - i]) {
            return false;
        }
    }
    return true;
}

bool isPrime(int val) {
    for (int i = 2; i * i <= val; ++i) {
        if (val % i == 0) {
            return false;
        }
    }
    return true;
}

vector<int> genPalindrome(int digits) {
    if (digits < 1) {
        return {};
    } else if (digits == 1) {
        return {1, 2, 3, 4, 5, 6, 7, 8, 9};
    } else if (digits == 2) {
        return {11, 22, 33, 44, 55, 66, 77, 88, 99};
    }
    vector<int> res;
    auto vi = genPalindrome(digits - 2);
    for (int i = 1; i <= 9; ++i) {
        int val = i * pow(10, digits - 1) + i;
        res.push_back(val);
        for (auto num : vi) {
            int d = log10(num) / 1 + 1;  // number of digits
            // if digits is 3 and d is 1, then want to multiply by 10
            // if digits is 5 and d is 3, then want to multiply by 10
            // if digits is 5 and d is 1, then want to multiply by 100
            // if digits is 6 and d is 4, then want to multiply by 10
            // if digits is 6 and d is 2, then want to multiply by 100

            res.push_back(val + num * pow(10, (digits - d) / 2));
        }
    }
    move(begin(vi), end(vi), back_inserter(res));
    return res;
}

int main() {
    // i/o
    ifstream fin("pprime.in");
    ofstream fout("pprime.out");


    int lo, hi;
    fin >> lo >> hi;

    vector<int> palindromes;
    int temp = hi, digits = 0;
    while (temp) {
        temp /= 10;
        ++digits;
    }
    auto vi = genPalindrome(digits);
    auto vi2 = genPalindrome(digits - 1);
    move(begin(vi2), end(vi2), back_inserter(vi));
    sort(begin(vi), end(vi));
    // for (auto num : vi) {
    //     cout << num << ',';
    // }

    for (int i = 0; i < vi.size(); ++i) {
        if (vi[i] < lo) {
            continue;
        } else if (vi[i] > hi) {
            break;
        } else if (isPrime(vi[i])) {  // && isPrime(i)) {
            fout << vi[i] << '\n';
        }
    }

    return EXIT_SUCCESS;
}
