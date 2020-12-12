/*
ID: sketchc1
LANG: C++14
TASK: zerosum
*/
#include <bits/stdc++.h>
using namespace std;


/*! hacky af
 * @param idx - progress towards N
 * @param N - number of numbers to combine together in a row
 * @param val - running total of values in curr string
 * @param prev - previous value in string
 * @param curr - string representation of combinations
 * @param res - strings that add up to zero when combined */
void sum(int idx, const int N, int val, int prev, const string& curr, vector<string>& res) {
    if (idx > N) {
        // cout << "DONE: " << val << '\t' << curr << '\n';
        if (val == 0) {
            res.push_back(curr);
        }
        return;
    }

    /* add */
    val += idx;
    string idxStr = to_string(idx);
    string plusStr = curr + "+" + idxStr;
    sum(idx + 1, N, val, idx, plusStr, res);

    /* subtract */
    val -= 2 * idx;
    string negStr = curr + "-" + idxStr;
    sum(idx + 1, N, val, -idx, negStr, res);
    val += idx;

    if (prev > 0) {
        /* concatenate when previous value was added */
        string concatStr = curr + " " + idxStr;
        val -= prev;  // remove previous value
        prev *= 10;
        prev += idx;
        val += prev;
        sum(idx + 1, N, val, prev, concatStr, res);
    } else if (prev < 0) {
        /* concatenate when previous value was subtracted */
        string concatStr = curr + " " + idxStr;
        val -= prev;  // remove previous value
        prev *= 10;
        prev -= idx;
        val += prev;
        sum(idx + 1, N, val, prev, concatStr, res);
    }
}


int main() {
    // i/o
    ifstream fin("zerosum.in");
    ofstream fout("zerosum.out");

    int N;
    fin >> N;

    string curr = "1";
    vector<string> res;
    sum(2, N, 1, 1, curr, res);
    sort(begin(res), end(res));
    for (auto&& s : res) {
        fout << s << '\n';
    }

    return EXIT_SUCCESS;
}
