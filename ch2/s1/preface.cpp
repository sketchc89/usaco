/*
ID: sketchc1
LANG: C++14
TASK: preface
*/
#include <bits/stdc++.h>
using namespace std;

void toRoman(int num, unordered_map<char, int>& counter, unordered_map<int, string>& roman) {
    if (num >= 1000) {
        for (auto it = cbegin(roman[num / 1000 * 1000]); it != cend(roman[num / 1000 * 1000]); ++it) {
            counter[*it]++;
        }
        num %= 1000;
        toRoman(num, counter, roman);
    } else if (num >= 100) {
        for (auto it = cbegin(roman[num / 100 * 100]); it != cend(roman[num / 100 * 100]); ++it) {
            counter[*it]++;
        }
        num %= 100;
        toRoman(num, counter, roman);
    } else if (num >= 10) {
        for (auto it = cbegin(roman[num / 10 * 10]); it != cend(roman[num / 10 * 10]); ++it) {
            counter[*it]++;
        }
        num %= 10;
        toRoman(num, counter, roman);
    } else if (num > 0) {
        for (auto it = cbegin(roman[num]); it != cend(roman[num]); ++it) {
            counter[*it]++;
        }
    }
}

void printNum(char c, unordered_map<char, int>& counter, ofstream& fout) {
    if (counter.count(c)) {
        fout << c << ' ' << counter[c] << '\n';
    }
}

int main() {
    // i/o
    ifstream fin("preface.in");
    ofstream fout("preface.out");

    unordered_map<int, string> roman{{1, "I"},     {2, "II"},     {3, "III"},   {4, "IV"},   {5, "V"},     {6, "VI"},
                                     {7, "VII"},   {8, "VIII"},   {9, "IX"},    {10, "X"},   {20, "XX"},   {30, "XXX"},
                                     {40, "XL"},   {50, "L"},     {60, "LX"},   {70, "LXX"}, {80, "LXXX"}, {90, "XC"},
                                     {100, "C"},   {200, "CC"},   {300, "CCC"}, {400, "CD"}, {500, "D"},   {600, "DC"},
                                     {700, "DCC"}, {800, "DCCC"}, {900, "CM"},  {1000, "M"}, {2000, "MM"}, {3000, "MMM"}};

    int num;
    fin >> num;
    unordered_map<char, int> counter;
    for (int i = 1; i <= num; ++i) {
        toRoman(i, counter, roman);
    }
    printNum('I', counter, fout);
    printNum('V', counter, fout);
    printNum('X', counter, fout);
    printNum('L', counter, fout);
    printNum('C', counter, fout);
    printNum('D', counter, fout);
    printNum('M', counter, fout);

    return EXIT_SUCCESS;
}
