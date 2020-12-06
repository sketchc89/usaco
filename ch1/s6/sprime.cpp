/*
ID: sketchc1
LANG: C++14
TASK: sprime
*/
#include <bits/stdc++.h>
using namespace std;


bool isPrime(int val) {
    if (val < 2) {
        return false;
    }
    for (int i = 2; i * i <= val; ++i) {
        if (val % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    // i/o
    ifstream fin("sprime.in");
    ofstream fout("sprime.out");

    int n;
    fin >> n;

    vector<int> res;
    queue<pair<int, int>> q;
    q.emplace(make_pair(2, 1));
    q.emplace(make_pair(3, 1));
    q.emplace(make_pair(5, 1));
    q.emplace(make_pair(7, 1));
    while (!q.empty()) {
        auto num = q.front().first;
        auto dig = q.front().second;
        q.pop();

        if (!isPrime(num)) {
            continue;
        }
        if (dig == n) {
            // cout << num << '\t' << dig << '\n';
            res.push_back(num);
            continue;
        }
        num *= 10;
        for (int i = 0; i <= 9; ++i) {
            q.emplace(make_pair(num + i, dig + 1));
        }
    }
    sort(begin(res), end(res));

    for (auto num : res) {
        fout << num << '\n';
    }

    return EXIT_SUCCESS;
}
