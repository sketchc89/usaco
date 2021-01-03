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

int bottleneckDijkstra(int src, int dst, unordered_map<int, unordered_map<int, Edge>>& graph, const int N) {
    vector<int> maxFlow(N, 0), visited(N, 0), parent(N, -1);
    maxFlow[src] = INF;
    priority_queue<pair<int, int>> pq;
    pq.emplace(make_pair(INF, src));

    while (!pq.empty()) {
        auto nodeFlow = pq.top().first;
        auto node = pq.top().second;
        pq.pop();
        if (visited[node]) {
            continue;
        } else {
            visited[node] = true;
        }
        for (auto&& kv : graph[node]) {
            auto to = kv.first;
            auto&& edge = kv.second;
            auto maxFlowEdge = min(nodeFlow, edge.remainingCapacity());
            cout << "Node " << node << "\tTrying to add " << to << " with remaining capacity " << edge.remainingCapacity()
                 << " and node flow " << nodeFlow << "\tbest is " << maxFlowEdge << "\tEdge previously had max flow of " << maxFlow[to]
                 << '\n';
            if (maxFlowEdge > maxFlow[to]) {
                parent[to] = node;
                maxFlow[to] = maxFlowEdge;
                pq.emplace(make_pair(maxFlowEdge, to));
            }
        }
    }

    int flow = maxFlow[dst];
    if (flow == 0) {  // no need to reduce flow
        return flow;
    }
    // cout << "Found path with flow " << flow << '\n';
    // cout << "Decreasing flow in path\n";
    while (parent[dst] != -1) {
        cout << "Edge from " << parent[dst] << " to " << dst << "\tBefore: " << graph[parent[dst]][dst].remainingCapacity() << ','
             << graph[dst][parent[dst]].remainingCapacity() << "\t\t";
        graph[parent[dst]][dst].flow += flow;  // reduce forward edge
        graph[dst][parent[dst]].flow -= flow;  // increase back edge
        cout << "After: " << graph[parent[dst]][dst].remainingCapacity() << ',' << graph[dst][parent[dst]].remainingCapacity() << '\n';
        assert(graph[dst][parent[dst]].remainingCapacity() >= 0);
        assert(graph[parent[dst]][dst].remainingCapacity() >= 0);
        dst = parent[dst];  // move back in the path
    }
    // cout << "Decreased flow in path\n";
    return flow;
}

int main() {
    ifstream fin("ditch.in");

    int numEdges, numNodes;
    fin >> numEdges >> numNodes;
    int src, dst, weight;
    unordered_map<int, unordered_map<int, Edge>> edges;
    for (int i = 0; i < numEdges; ++i) {
        fin >> src >> dst >> weight;
        --src;
        --dst;
        if (src != dst) {
            Edge forward, residual;
            forward.flow = 0;
            forward.capacity = weight;
            forward.isResidual = false;
            residual.flow = 0;
            residual.capacity = 0;
            residual.isResidual = true;
            edges[src][dst] = forward;
            edges[dst][src] = residual;
        }
    }
    // cout << "I/O\n";
    int maxFlow = 0;
    int flow = 1;
    while (flow > 0) {
        // cout << '\n' << string(30, '-') << '\n';
        src = 0;
        dst = numNodes - 1;
        int node = src;
        // find augmenting path
        flow = bottleneckDijkstra(src, dst, edges, numNodes);
        maxFlow += flow;
        // cout << "new max flow " << maxFlow << "\n";
    }
    ofstream fout("ditch.out");
    fout << maxFlow << '\n';
    return EXIT_SUCCESS;
}
