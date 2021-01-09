/*
ID: sketchc1
LANG: C++14
TASK: stall4
*/
#include <bits/stdc++.h>
using namespace std;

constexpr static int SRC = -1;
constexpr static int DST = -2;
constexpr static int DUMMY = -3;
constexpr static int INF = 1'000'000'000;

// used to create residual graph
struct Edge {
    Edge()
            : from{DUMMY}
            , to{DUMMY}
            , flow{}
            , capacity{}
            , isResidual{} {}

    Edge(int f, int t, int c)
            : from{f}
            , to{t}
            , flow{0}
            , capacity{c}
            , isResidual{c == 0} {}
    int to, from, flow, capacity;
    bool isResidual;
    int remainingCapacity() const {
        return capacity - flow;
    }
};

// helpful for running max flow multiple times with different capacities
/* void resetEdges(unordered_map<int, unordered_map<int, Edge>>& g) {
    for (auto& kv : g) {
        for (auto& kv2 : kv.second) {
            auto& edge = kv2.second;
            edge.flow = 0;
        }
    }
} */

// depth first search from src to dst where all unvisited nodes with positive remaining capacity are explored
int dfsFlow(int src, int dst, unordered_map<int, unordered_map<int, Edge>>& g) {
    unordered_set<int> visited;
    vector<Edge> path;
    stack<pair<pair<int, int>, vector<Edge>>> s;
    bool reachedTarget = false;
    int node = -1, flow = INF;
    s.push({{src, flow}, path});

    while (!s.empty()) {
        node = s.top().first.first;
        flow = s.top().first.second;
        path = s.top().second;
        s.pop();
        if (visited.count(node)) {
            continue;
        } else {
            visited.insert(node);
        }
        if (node == dst) {
            reachedTarget = true;
            break;
        }
        for (auto&& kv : g[node]) {
            auto newFlow = min(flow, kv.second.remainingCapacity());
            if (newFlow > 0) {
                path.push_back(kv.second);
                s.push({{kv.first, newFlow}, path});
                path.pop_back();
            }
        }
    }
    if (!reachedTarget) {
        return 0;
    }
    for (auto&& edge : path) {
        g[edge.from][edge.to].flow += flow;
        g[edge.to][edge.from].flow -= flow;
        assert(g[edge.from][edge.to].remainingCapacity() >= 0);
        assert(g[edge.to][edge.from].remainingCapacity() >= 0);
    }
    return flow;
}

/* helpful for debug logging */
string reprCow(int val) {
    if (val == SRC) {
        return "src";
    } else if (val == DST) {
        return "dst";
    } else if (val < 1000) {
        return "cow " + to_string(val);
    } else {
        return "stall " + to_string(val);
    }
}

int main() {
    // i/o
    ifstream fin("stall4.in");
    ofstream fout("stall4.out");

    int numCows, totalStalls;
    fin >> numCows >> totalStalls;

    unordered_map<int, unordered_map<int, Edge>> edges;
    for (int cow = 0; cow < numCows; ++cow) {
        // from src to cow
        edges[SRC][cow] = Edge(SRC, cow, 1);
        edges[cow][SRC] = Edge(cow, SRC, 0);

        int numStalls;
        fin >> numStalls;
        for (int j = 0; j < numStalls; ++j) {
            int stall = 1000;
            int x;
            fin >> x;
            stall += x;
            // from cow to stall
            edges[cow][stall] = Edge(cow, stall, 1);
            edges[stall][cow] = Edge(stall, cow, 0);
            // to destination
            edges[stall][DST] = Edge(stall, DST, 1);
            edges[DST][stall] = Edge(DST, stall, 0);
        }
    }

    // bipartite matching using dfs flow since this is a small graph
    // dinic / edmondkarp wont help since the path length is usually (always?) the same
    int maxFlow = 0;
    int flow = 1;
    while (flow > 0) {
        flow = dfsFlow(SRC, DST, edges);
        maxFlow += flow;
    }

    // optional logging
    /* string line = "\n" + string(50, '-') + "\n";
    for (auto&& kv : edges) {
        cout << "Num edges: " << kv.second.size() << "\t\t";
        for (auto&& kv2 : kv.second) {
            auto&& edge = kv2.second;
            if (edge.isResidual) {
                continue;
            }
            string fromStr = reprCow(edge.from);
            string toStr = reprCow(edge.to);
            cout << fromStr << "-->" << toStr << " = " << edge.flow << "/" << edge.capacity
                 << "\t\t";  //<< "; res? " << edge.isResidual << "\t\t";
        }
        cout << line;
    }
    cout << line << "MaxFlow: " << maxFlow << line; */

    fout << maxFlow << '\n';
    return EXIT_SUCCESS;
}
