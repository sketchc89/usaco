/*
ID: sketchc1
LANG: C++14
TASK: comehome
*/
#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = 1'000'000'000;

/* Dijkstra's */
int cowSpeed(char cow, unordered_map<char, unordered_map<char, int>>& graph) {
    unordered_set<char> visited;    // keep track of processed nodes
    unordered_map<char, int> dist;  // keep track of shortest path lengths

    /* initialize shortest path to infinity except starting cow */
    for (auto&& kv : graph) {
        dist[kv.first] = INF;
    }
    dist[cow] = 0;

    /* priority queue with shortest paths coming first */
    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;
    pq.push(make_pair(0, cow));

    while (!pq.empty()) {
        auto c = pq.top().second;  // throw out weight
        pq.pop();

        if (visited.count(c)) {
            continue;
        } else {
            visited.insert(c);
        }

        for (auto&& kv : graph[c]) {
            auto neighbor = kv.first;
            auto w = kv.second;
            /* Relax edge if path through this node is better than existing shortest path */
            if (dist[c] + w < dist[neighbor]) {
                dist[neighbor] = dist[c] + w;
                pq.emplace(make_pair(dist[neighbor], neighbor));
            }
        }
    }

    /* trying to get to farm Z */
    return dist['Z'];
}

int main() {
    // i/o
    ifstream fin("comehome.in");
    ofstream fout("comehome.out");

    int N;
    fin >> N;
    unordered_map<char, unordered_map<char, int>> graph;
    for (int i = 0; i < N; ++i) {
        char from, to;
        int weight;
        fin >> from >> to >> weight;
        /* if path exists only store shortest path given, otherwise store path given */
        if (graph[from].count(to)) {
            graph[from][to] = min(graph[from][to], weight);
            graph[to][from] = min(graph[to][from], weight);
        } else {
            graph[from][to] = weight;
            graph[to][from] = weight;
        }
    }

    // run djikstra's for each cow
    char bestCow = '#';
    int bestSpeed = INF;
    for (auto&& kv : graph) {
        /* Cows start in capital letters between A and Y, target is Z */
        if (kv.first < 'A' || kv.first > 'Y') {
            continue;
        }
        /* Run for each cow and update best found if it is that */
        auto res = cowSpeed(kv.first, graph);
        if (res < bestSpeed) {
            bestCow = kv.first;
            bestSpeed = res;
        }
    }

    fout << static_cast<char>(bestCow) << ' ' << bestSpeed << '\n';

    return EXIT_SUCCESS;
}
