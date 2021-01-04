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

// use bfs to find augmenting path that is the shortest path measured in number of nodes rather than weight between src and target
// in practice converges to a solution quickly
int edmondsKarp(int src, int dst, unordered_map<int, unordered_map<int, Edge>>& graph, const int N) {
    // breadth first search, first pair is node to process and the edge used to get there
    // followed by the path of these pairs used to get to the current step
    queue<pair<pair<int, int>, vector<pair<int, int>>>> q;
    vector<int> visited(N, 0);
    vector<pair<int, int>> path;  // track in order to reduce flow after augmenting path found
    q.emplace(make_pair(make_pair(src, INF), path));
    int node = -1, flow = 0;     // dummy values
    bool reachedTarget = false;  // used to tell if augmenting path was found, if it wasn't flow doesnt need to be modified

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

        if (node == dst) {  // SUCCESS
            reachedTarget = true;
            break;
        }
        /* for each edge connected to this node, enqueue all edges that have a flow greater than zero
         * where the flow is the lesser of the current flow and the flow of the edge */
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

    /* increase the flow of the forward edge and decrease the flow of the residual edge
     * uses edge id because the graph is not simple and can have multiple edges per node pair */
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

    /* Important: this is not a simple graph. Can have multiple edges per node pair
     * wasted a lot of time b/c I didn't realize this */
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
        residual.isResidual = true;  // useful for debugging
        edges[src][i] = forward;     // use i as edge id to pair up forward and residual edges
        edges[dst][i] = residual;    // alternatively could use multimap but it's messier IMO
    }

    int maxFlow = 0;
    int flow = 1;  // to get into while loop
    // keep adding to max flow until an augmenting path cannot be found
    while (flow > 0) {
        int src = 0;
        int dst = numNodes - 1;
        // find augmenting path
        flow = edmondsKarp(src, dst, edges, numNodes);
        maxFlow += flow;
    }

    ofstream fout("ditch.out");
    fout << maxFlow << '\n';
    return EXIT_SUCCESS;
}
