/*
ID: sketchc1
LANG: C++14
TASK: inflate
*/
#include <bits/stdc++.h>
using namespace std;


int main() {
    // i/o
    ifstream fin("inflate.in");
    ofstream fout("inflate.out");

    int totalMinutes, classes;
    fin >> totalMinutes >> classes;
    cout << totalMinutes << '\t' << classes << '\n';

    vector<int> dp(totalMinutes + 1, 0);
    vector<pair<int, int>> vals(classes + 1);
    for (int i = 0; i < vals.size(); ++i) {
        int pt, mins;
        fin >> pt >> mins;
        vals[i] = make_pair(mins, pt);
    }

    sort(begin(vals), end(vals), [](auto&& lhs, auto&& rhs) {
        return static_cast<double>(lhs.second) / lhs.first > static_cast<double>(rhs.second) / rhs.first;
    });
    int cnt = 0;
    for (auto v : vals) {
        cnt++;
    }

    for (int i = 0; i < vals.size(); ++i) {
        auto mins = vals[i].first;
        auto points = vals[i].second;
        for (int t = mins; t <= totalMinutes; ++t) {
            if (dp[t] < dp[t - mins] + points) {
                dp[t] = dp[t - mins] + points;
            }
        }
    }
    fout << dp[totalMinutes] << '\n';
    return EXIT_SUCCESS;
}
