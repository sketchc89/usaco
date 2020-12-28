/*
ID: sketchc1
LANG: C++14
TASK: ditch
*/
#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = 1'000'000'000;

int main() {
    // i/o
    ifstream fin("ditch.in");
    ofstream fout("ditch.out");

    // read input into graph
    int numEdges, numNodes;
    fin >> numEdges >> numNodes;
    // maybe sorting edges by weight would be a bit faster
    unordered_map<int, unordered_map<int, int>> graph;
    int src, dst, weight;
    while (fin >> src >> dst >> weight) {
        graph[src][dst] = weight;
    }

    // keep adding flow until there is no change from one step to the next
    bool progress = true;
    int totalFlow = 0;
    while (progress) {
        src = 1;  // 1 based b/c of input and we're using hash maps
        dst = numNodes;
        int flow = INF;
        int node = src;
        vector<int> path(1, node);

        progress = false;
        /* there's probably a better data structure but I had already done iterative dfs
         * before realizing i needed to move around the path as a vector */
        stack<pair<pair<int, int>, vector<int>>> s;

        s.push({{flow, node}, path});
        while (!s.empty()) {
            flow = s.top().first.first;
            node = s.top().first.second;
            path = s.top().second;
            s.pop();

            // if we reach the destination and there is flow then report progress has been made
            if (node == dst) {
                progress = flow > 0;
                break;
            }
            // go down everry path that still has capacity
            for (auto& kv : graph[node]) {
                int f = min(flow, kv.second);
                if (f > 0) {
                    path.push_back(kv.first);
                    s.push({{f, kv.first}, path});
                    path.pop_back();
                }
            }
        }
        if (progress) {
            totalFlow += flow;
            // reduce capacity of every edge in the path found
            for (int i = 0; i < path.size() - 1; ++i) {
                graph[path[i]][path[i + 1]] -= flow;
            }
        }
    }

    fout << totalFlow << '\n';
    return EXIT_SUCCESS;
}
