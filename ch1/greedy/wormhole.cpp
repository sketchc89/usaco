/*
ID: sketchc1
LANG: C++14
TASK: wormhole
*/
#include <bits/stdc++.h>
using namespace std;

/*  Distinct pairs algorithm
 *  12! / 2^6 */
/*  choose i, then some j greater than i
 *  choose k, that isn't i or j, is greater than i, then some l that is greater than k and isn't i or j
 *  choose m, that isn't i,j,k,l, is greater than k, then some n that is greater than m and isn't i,j,k,l */

void distinctPairs(
        int idx,
        int first,
        const int maxIdx,
        vector<int>& used,
        vector<pair<int, int>>& curr,
        vector<vector<pair<int, int>>>& res) {
    if (curr.size() == maxIdx / 2) {
        // for (auto n : curr) {
        //     cout << n.first << ',' << n.second << '\t';
        // }
        // cout << '\n';
        res.push_back(curr);
        return;
    }
    if (idx >= maxIdx) {
        return;
    }
    if (used[idx]) {
        distinctPairs(idx + 1, first, maxIdx, used, curr, res);
        return;
    }

    if (first == -1) {
        // choose this index for first element
        used[idx] = true;
        first = idx;
        distinctPairs(idx + 1, first, maxIdx, used, curr, res);
        // dont choose this index for first element
        used[idx] = false;
        distinctPairs(idx + 1, -1, maxIdx, used, curr, res);
    } else {
        // choose this index for second element
        used[idx] = true;
        curr.emplace_back(make_pair(first, idx));
        distinctPairs(first + 1, -1, maxIdx, used, curr, res);
        curr.pop_back();
        // dont choose index for second element
        used[idx] = false;
        distinctPairs(idx + 1, first, maxIdx, used, curr, res);
    }
}


int main() {
    // i/o
    ifstream fin("wormhole.in");
    ofstream fout("wormhole.out");

    int numWh;
    fin >> numWh;
    // vector < pair<int, int>> wormholes;
    map<pair<int, int>, int> locIdx;
    unordered_map<int, pair<int, int>> idxLoc;
    int x, y;
    for (int i = 0; i < numWh; ++i) {
        fin >> x >> y;
        auto p = make_pair(x, y);
        locIdx.emplace(make_pair(p, i));
        idxLoc.emplace(make_pair(i, p));
    }
    vector<pair<int, int>> next(numWh, {1'000'000'001, -1});
    for (int i = 0; i < numWh; ++i) {
        auto p1 = idxLoc[i];
        for (int j = 0; j < numWh; ++j) {
            if (i == j) {
                continue;
            }
            auto p2 = idxLoc[j];
            if (p1.second != p2.second) {
                continue;
            }
            if (p1.first < p2.first && p2.first < next[i].first) {
                next[i] = p2;
            }
        }
        // cout << "Next for " << i << '\t';
        // cout << p1.first << ',' << p1.second << "--->" << next[i].first << ',' << next[i].second << "\n\n";
    }


    vector<int> chosen(numWh, 0);
    vector<vector<pair<int, int>>> distinctPairings;
    vector<pair<int, int>> pairs;
    // there are
    // nC2 * n-2C2 * ... 2C2 / ((n/2)!) distinct pairings
    // e.g. 6C2 * 4C2 * 2C2 / 6! = 15
    distinctPairs(0, -1, numWh, chosen, pairs, distinctPairings);
    unordered_map<int, int> warp;
    vector<int> seen(numWh);
    int score = 0;
    for (auto&& pairing : distinctPairings) {
        warp.clear();
        for (auto&& p : pairing) {
            // cout << idxLoc[p.first].first << ',' << idxLoc[p.first].second << " " << idxLoc[p.second].first << ','
            //      << idxLoc[p.second].second << "\t\t";
            warp[p.first] = p.second;
            warp[p.second] = p.first;
        }
        // cout << '\n';
        bool stuck = false;
        for (const auto& p : pairing)
            for (const auto& p : locIdx) {
                const auto& startingPos = p.first;
                int startingIdx = p.second;
                for (int i = 0; i < seen.size(); ++i) {
                    seen[i] = false;
                }
                auto pos = startingPos;
                while (pos.first < 1'000'000'000) {
                    auto it = locIdx.find(pos);
                    if (it == locIdx.end()) {
                        pos.first++;
                    } else {
                        if (seen[it->second]) {
                            // cout << "found loop\n";
                            stuck = true;
                            break;
                        }
                        seen[it->second] = true;
                        pos = next[warp[it->second]];
                    }
                }
                if (stuck) {
                    break;
                }
            }
        if (stuck) {
            ++score;
        }
    }
    fout << score << '\n';
    // any distinct pairing where elements have the same y coordinate are off limits
    // any distinct pairing where two distinct pairings have


    return EXIT_SUCCESS;
}
