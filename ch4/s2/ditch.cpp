/*
ID: sketchc1
LANG: C++14
TASK: ditch
*/
#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = 1'000'000'000;

ofstream fout("ditch.out");

int maxFlow(int src, int dst, unordered_map<int, unordered_map<int, pair<int, int>>>& graph, vector<int>& path, const int numNodes) {
    vector<int> width(numNodes, 0);
    vector<int> visited(numNodes, 0), parent(numNodes, -1);
    width[0] = INF;
    priority_queue<pair<int, int>> pq;

    fout << '\n' << string(30, '-') << "\nFinding max flow path\n" << string(30, '-') << '\n';
    pq.emplace(make_pair(width[0], src));
    while (!pq.empty()) {
        auto node = pq.top().second;
        fout << "Node: " << node << "\t";
        pq.pop();
        if (visited[node]) {
            fout << '\n';
            continue;
        } else {
            visited[node] = true;
        }
        for (auto&& kv : graph[node]) {
            int maxW = min(width[node], kv.second.first);
            fout << "max width from " << node << " to " << kv.first << " is max of " << width[node] << " and " << kv.second.first << '\n';
            if (maxW > width[kv.first]) {
                parent[kv.first] = node;
                width[kv.first] = maxW;
                pq.emplace(make_pair(maxW, kv.first));
            }
        }
    }

    int x = dst;
    path.push_back(x);
    while (parent[x] != -1) {
        fout << "Parent of " << x << " is " << parent[x] << '\t';
        path.push_back(parent[x]);
        x = parent[x];
    }
    reverse(begin(path), end(path));
    // for (auto num : path) {
    //     fout << num << ',';
    // }
    // fout << '\n';
    return width[dst];
}

int main() {
    // i/o
    ifstream fin("ditch.in");

    // read input into graph
    int numEdges, numNodes;
    fin >> numEdges >> numNodes;
    // maybe sorting edges by weight would be a bit faster
    unordered_map<int, unordered_map<int, pair<int, int>>> graph;
    int src, dst, weight;
    for (int i = 0; i < numEdges; ++i) {
        fin >> src >> dst >> weight;
        --src;
        --dst;
        if (src != dst) {
            graph[src][dst].first = weight;
            graph[src][dst].second = weight;
            graph[dst][src].first = 0;
            graph[dst][src].second = weight;
        }
    }
    // for (auto&& kv : graph) {
    //     fout << kv.first << ':';
    //     for (auto&& toWeight : kv.second) {
    //         fout << toWeight.first << ',' << toWeight.second << '\t';
    //     }
    //     fout << '\n';
    // }

    // keep adding flow until there is no change from one step to the next
    bool progress = true;
    int totalFlow = 0;
    vector<int> path;
    while (true) {
        src = 0;
        dst = numNodes - 1;
        int node = src;

        path.clear();
        int flow = maxFlow(src, dst, graph, path, numNodes);
        if (flow == 0) {
            break;
        }

        totalFlow += flow;
        fout << "Progress, increasing by " << flow << " to " << totalFlow << '\n';
        // reduce capacity of every edge in the path found
        for (int i = 0; i < path.size() - 1; ++i) {
            auto a = path[i];
            auto b = path[i + 1];
            fout << "Decreasing " << a << "-->" << b << '\t';
            if (graph[a][b].first - flow < -graph[a][b].second) {
                flow = graph[a][b].second - graph[a][b].first;
            }
            if (graph[b][a].first + flow > graph[b][a].second) {
                flow = graph[b][a].first - graph[b][a].second;
            }
            graph[a][b].first = graph[a][b].first - flow;  // reduce flow from path
            graph[b][a].first = graph[b][a].first + flow;  // add residual flow in opposite direction of path
        }
    }

    fout << totalFlow << '\n';
    return EXIT_SUCCESS;
}
