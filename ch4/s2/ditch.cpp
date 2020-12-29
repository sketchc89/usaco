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
    for (int i = 0; i < numEdges; ++i) {
        fin >> src >> dst >> weight;
        if (src != dst) {
            graph[src][dst] = weight;
        }
    }
    // for (auto&& kv : graph) {
    //     cout << kv.first << ':';
    //     for (auto&& toWeight : kv.second) {
    //         cout << toWeight.first << ',' << toWeight.second << '\t';
    //     }
    //     cout << '\n';
    // }

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
        stack<pair<pair<int, int>, pair<vector<int>, unordered_set<int>>>> s;
        unordered_set<int> inPath;

        s.push({{flow, node}, {path, inPath}});
        while (!s.empty()) {
            flow = s.top().first.first;
            node = s.top().first.second;
            path = s.top().second.first;
            inPath = s.top().second.second;
            // cout << node << '\t' << flow << '\t';
            // for (auto num : path) {
            //     cout << num << ',';
            // }
            // cout << '\n';
            s.pop();


            // if we reach the destination and there is flow then report progress has been made
            if (node == dst && flow > 0) {
                // cout << "Reached destination with " << flow << '\n';
                progress = true;
                break;
            } else if (node == dst) {
                // cout << "Reached destination with no flow\n";
                continue;
            }

            // go down everry path that still has capacity
            for (auto& kv : graph[node]) {
                // cout << "Edge " << node << "-->" << kv.first << '\t';
                if (inPath.count(kv.first)) {
                    // cout << "Already seen " << kv.first << '\n';
                    continue;
                    //     cout << "Haven't seen " << kv.first << '\t';
                }

                // cout << "previous flow " << flow << '\t' << " new edge flow " << kv.second << '\n';
                int f = min(flow, kv.second);
                if (f > 0) {
                    // cout << " flow " << f << " greater than 0\n";
                    inPath.insert(kv.first);
                    path.push_back(kv.first);
                    s.push({{f, kv.first}, {path, inPath}});
                    path.pop_back();
                    inPath.erase(kv.first);
                    // } else {
                    //     cout << " no flow\n";
                }
            }
        }

        if (progress) {
            totalFlow += flow;
            // cout << "Progress, increasing by " << flow << " to " << totalFlow << '\n';
            // reduce capacity of every edge in the path found
            for (int i = 0; i < path.size() - 1; ++i) {
                // cout << "Decreasing " << path[i] << "-->" << path[i + 1] << '\n';
                graph[path[i]][path[i + 1]] -= flow;  // reduce flow from path
                graph[path[i + 1]][path[i]] += flow;  // add residual flow in opposite direction of path
            }
        }
    }

    fout << totalFlow << '\n';
    return EXIT_SUCCESS;
}
