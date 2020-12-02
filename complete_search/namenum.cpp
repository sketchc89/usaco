/*
ID: sketchc1
LANG: C++14
TASK: namenum
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // i/o
    ifstream fin("namenum.in");
    ifstream fdict("dict.txt");
    ofstream fout("namenum.out");

    unordered_map<char, int64_t> t9{{'A', 2}, {'B', 2}, {'C', 2},   //
                                    {'D', 3}, {'E', 3}, {'F', 3},   //
                                    {'G', 4}, {'H', 4}, {'I', 4},   //
                                    {'J', 5}, {'K', 5}, {'L', 5},   //
                                    {'M', 6}, {'N', 6}, {'O', 6},   //
                                    {'P', 7}, {'R', 7}, {'S', 7},   //
                                    {'T', 8}, {'U', 8}, {'V', 8},   //
                                    {'W', 9}, {'X', 9}, {'Y', 9}};  //
    int64_t num;
    fin >> num;

    string name;
    int count = 0;
    while (getline(fdict, name)) {
        // cout << name << '\n';
        int64_t val = 0;
        for (int i = 0; i < name.size(); ++i) {
            val *= 10;
            val += t9[name[i]];
        }
        // cout << val << '\n';
        if (val == num) {
            // cout << "SUCCESS!\n\n";
            fout << name << '\n';
            ++count;
        }
    }
    if (count == 0) {
        fout << "NONE\n";
    }

    return EXIT_SUCCESS;
}
