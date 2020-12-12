/*
ID: sketchc1
LANG: C++14
TASK: concom
*/
#include <bits/stdc++.h>
using namespace std;

set<int> ownership(int start, map<int, map<int, int>>& graph) {
    set<int> res;
    unordered_map<int, int> curOwnership;
    unordered_set<int> visited;
    stack<int> s;
    s.push(start);
    while (!s.empty()) {
        auto node = s.top();
        s.pop();
        if (visited.count(node)) {
            continue;
        } else {
            visited.insert(node);
        }
        for (auto kv : graph[node]) {
            if (kv.first == node || kv.first == start) {
                continue;
            }
            curOwnership[kv.first] += kv.second;
            if (curOwnership[kv.first] > 50) {
                s.push(kv.first);
                res.insert(kv.first);
            }
        }
    }
    return res;
}

int main() {
    // i/o
    ifstream fin("concom.in");
    ofstream fout("concom.out");

    int numTriples;
    fin >> numTriples;

    set<int> s;
    map<int, map<int, int>> graph;
    vector<pair<pair<int, int>, int>> trips(numTriples);
    for (int t = 0; t < trips.size(); ++t) {
        int from, to, w;
        fin >> from >> to >> w;
        graph[from][to] = w;
    }

    vector<pair<int, int>> res;
    for (auto&& kv : graph) {
        auto res = ownership(kv.first, graph);
        for (auto to : res) {
            fout << kv.first << ' ' << to << '\n';
        }
    }

    return EXIT_SUCCESS;
}
