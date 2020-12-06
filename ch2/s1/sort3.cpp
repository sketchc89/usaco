/*
ID: sketchc1
LANG: C++14
TASK: sort3
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // i/o
    ifstream fin("sort3.in");
    ofstream fout("sort3.out");

    int n;
    fin >> n;
    vector<int> vi(n);
    unordered_map<int, int> counter;
    for (int i = 0; i < n; ++i) {
        fin >> vi[i];
        counter[vi[i]]++;
    }
    int oneInTwo = 0, oneInThree = 0, twoInOne = 0, twoInThree = 0, threeInOne = 0, threeInTwo = 0;
    /* count mispalced numbers */
    assert(n == counter[1] + counter[2] + counter[3]);
    for (int i = 0; i < counter[1]; ++i) {
        if (vi[i] == 2) {
            twoInOne++;
        } else if (vi[i] == 3) {
            threeInOne++;
        }
    }
    for (int i = counter[1]; i < counter[1] + counter[2]; ++i) {
        if (vi[i] == 1) {
            oneInTwo++;
        } else if (vi[i] == 3) {
            threeInTwo++;
        }
    }
    for (int i = counter[1] + counter[2]; i < n; ++i) {
        if (vi[i] == 1) {
            oneInThree++;
        } else if (vi[i] == 2) {
            twoInThree++;
        }
    }

    /* resolve two with one swap */
    int res = 0;
    auto oneTwoSwap = min(twoInOne, oneInTwo);
    auto twoThreeSwap = min(twoInThree, threeInTwo);
    auto oneThreeSwap = min(threeInOne, oneInThree);

    res += oneTwoSwap;
    res += twoThreeSwap;
    res += oneThreeSwap;
    twoInOne -= oneTwoSwap;
    oneInTwo -= oneTwoSwap;
    twoInThree -= twoThreeSwap;
    threeInTwo -= twoThreeSwap;
    threeInOne -= oneThreeSwap;
    oneInThree -= oneThreeSwap;


    /* resolve three with two swaps */
    auto misplaced = twoInOne + oneInTwo + twoInThree + threeInTwo + threeInOne + oneInThree;
    misplaced /= 3;
    misplaced *= 2;
    res += misplaced;

    fout << res << '\n';

    return EXIT_SUCCESS;
}
