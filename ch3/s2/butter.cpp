/*
ID: sketchc1
LANG: C++14
TASK: butter
*/
#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = 1'000'000'000;

int cowDistance(int src, unordered_map<int, unordered_map<int, int>>& graph, const vector<int>& loc) {
    vector<int> dist(graph.size(), INF), visited(graph.size(), false);
    dist[src] = 0;

    // min heap
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(make_pair(0, src));

    while (!pq.empty()) {
        auto node = pq.top().second;
        pq.pop();
        if (visited[node]) {
            continue;
        } else {
            visited[node] = true;
        }
        for (auto&& kv : graph[node]) {
            int to = kv.first;
            int w = kv.second;
            if (dist[node] + w < dist[to]) {
                dist[to] = dist[node] + w;
                pq.emplace(make_pair(dist[to], to));
            }
        }
    }

    // cout << "Source: " << src << '\t';
    int res = 0;
    for (int i = 0; i < loc.size(); ++i) {
        res += dist[loc[i]];
    }
    // cout << "Cost: " << res << '\n';
    return res;
}
int main() {
    // i/o
    ifstream fin("butter.in");
    ofstream fout("butter.out");

    int numCows, numPastures, numPaths;
    fin >> numCows >> numPastures >> numPaths;
    vector<int> cowLoc(numCows);
    for (int i = 0; i < cowLoc.size(); ++i) {
        fin >> cowLoc[i];
        cowLoc[i]--;  // 0-based
    }

    unordered_map<int, unordered_map<int, int>> graph;
    for (int i = 0; i < numPaths; ++i) {
        int a, b, w;
        fin >> a >> b >> w;
        --a;  // 0-based
        --b;  // 0-based
        graph[a][b] = w;
        graph[b][a] = w;
    }

    int res = INT32_MAX;
    for (int i = 0; i < numPastures; ++i) {
        res = min(res, cowDistance(i, graph, cowLoc));
    }

    fout << res << '\n';


    return EXIT_SUCCESS;
}
