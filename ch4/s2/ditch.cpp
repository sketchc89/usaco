/*
ID: sketchc1
LANG: C++14
TASK: ditch
*/

#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = 2'000'000'000;

struct Edge {
    int to, from, flow, capacity;
    bool isResidual;
    int remainingCapacity() const {
        return capacity - flow;
    }
};

int edmondsKarp(int src, int dst, unordered_map<int, unordered_map<int, Edge>>& graph, const int N) {
    queue<pair<pair<int, int>, vector<pair<int, int>>>> q;
    vector<int> visited(N, 0);
    vector<pair<int, int>> path;
    q.emplace(make_pair(make_pair(src, INF), path));
    int node = -1, flow = 0;
    bool reachedTarget = false;

    while (!q.empty()) {
        node = q.front().first.first;
        flow = q.front().first.second;
        path = q.front().second;
        q.pop();
        if (visited[node]) {
            continue;
        } else {
            visited[node] = true;
        }
        if (node == dst) {
            reachedTarget = true;
            break;
        }
        for (auto&& kv : graph[node]) {
            auto edgeId = kv.first;
            auto&& edge = kv.second;
            auto to = kv.second.to;
            auto maxFlowEdge = min(flow, edge.remainingCapacity());
            if (maxFlowEdge > 0) {
                path.emplace_back(make_pair(node, edgeId));
                q.emplace(make_pair(make_pair(to, maxFlowEdge), path));
                path.pop_back();
            }
        }
    }
    if (!reachedTarget) {
        return 0;
    }
    for (int i = 0; i < path.size(); ++i) {
        auto from = path[i].first;
        auto edgeId = path[i].second;
        auto& edge = graph[path[i].first][path[i].second];
        auto to = edge.to;
        auto& resEdge = graph[to][path[i].second];
        edge.flow += flow;
        resEdge.flow -= flow;

        assert(edge.remainingCapacity() >= 0);
        assert(resEdge.remainingCapacity() >= 0);
    }
    return flow;
}

int main() {
    ifstream fin("ditch.in");

    int numEdges, numNodes;
    fin >> numEdges >> numNodes;
    unordered_map<int, unordered_map<int, Edge>> edges;
    for (int i = 0; i < numEdges; ++i) {
        int src, dst, weight;
        fin >> src >> dst >> weight;
        --src;
        --dst;
        Edge forward, residual;
        forward.flow = 0;
        forward.from = src;
        forward.to = dst;
        forward.capacity = weight;
        forward.isResidual = false;
        residual.flow = 0;
        residual.from = dst;
        residual.to = src;
        residual.capacity = 0;
        residual.isResidual = true;
        edges[src][i] = forward;
        edges[dst][i] = residual;
    }
    int maxFlow = 0;
    int flow = 1;
    int count = 0;
    string line = "\n" + string(50, '-') + "\n";
    while (flow > 0) {
        int src = 0;
        int dst = numNodes - 1;
        // find augmenting path
        flow = edmondsKarp(src, dst, edges, numNodes);
        maxFlow += flow;
        ++count;
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            string s = to_string(j) + string(1, ':') + to_string(edges[i][j].remainingCapacity());
            if (j % 10 == 9) {
                cout << '\n';
            }
        }
    }
    ofstream fout("ditch.out");
    fout << maxFlow << '\n';
    return EXIT_SUCCESS;
}
