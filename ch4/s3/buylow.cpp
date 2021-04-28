/*
ID: sketchc1
LANG: C++14
TASK: buylow
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // i/o
    ifstream fin("buylow.in");
    ofstream fout("buylow.out");

    int numPrices;
    fin >> numPrices;
    vector<int> prices(numPrices);
    for (int i = 0; i < prices.size(); ++i) {
        fin >> prices[i];
    }
    vector<pair<int, int>> dp(prices.size(), {1, 1});
    // for (int i = 0; i < dp.size(); ++i) {
    //     dp[i] = make_pair(1, i + 1);
    // }

    // i guess dp is going to represent first, the longest decreasing sequence, second, the number of sequences with that length

    string line = "\n" + string(50, '-') + "\n";
    cout << "0:\t" << dp[0].first << "\t\t" << dp[0].second << '\n';
    unordered_map<int, map<int, int, greater<int>>> counter;
    counter[1].insert({prices[0], 0});
    for (int end = 1; end < prices.size(); ++end) {
        for (int start = 0; start < end; ++start) {
            if (prices[start] > prices[end] && dp[start].first + 1 > dp[end].first) {
                // cout << "Buy low on " << start << "  buy lower on end. New len " << dp[end].first << "\n";
                dp[end].first = dp[start].first + 1;
            }
        }
        cout << end << ":" << prices[end] << "\t\t";
        counter[dp[end].first].insert({prices[end], end});
        auto it = counter.find(dp[end].first - 1);
        dp[end].second = 0;
        if (it != counter.end()) {
            auto lb = counter[dp[end].first - 1].lower_bound(prices[end]);
            for (auto it2 = counter[dp[end].first - 1].begin(); it2 != lb; ++it2) {
                cout << prices[it2->second] << "@" << it2->second << " vs " << prices[end] << '\t';
                dp[end].second += dp[it2->second].second;
            }
        }
        dp[end].second = max(1, dp[end].second);

        cout << "(" << dp[end].first << "," << dp[end].second << ")" << '\n';
    }

    int maxPath = 0, maxRep = 0;
    for (auto&& p : dp) {
        if (p.first > maxPath) {
            maxPath = p.first;
            maxRep = p.second;
        } else if (p.first == maxPath && p.second > maxRep) {
            maxRep = p.second;
        }
    }

    if (maxPath == 1 && maxRep == 1) {
        maxRep = prices.size();
    }

    fout << maxPath << ' ' << maxRep << '\n';
    return EXIT_SUCCESS;
}
