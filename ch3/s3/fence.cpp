/*
ID: sketchc1
LANG: C++14
TASK: fence
*/
#include <bits/stdc++.h>
using namespace std;

int findStart(map<int, multiset<int>>& g) {
    for (auto&& kv : g) {
        if (kv.second.size() % 2 == 1) {
            return kv.first;
        }
    }
    return begin(g)->first;  // just start at first node
}

int main() {
    // i/o
    ifstream fin("fence.in");
    ofstream fout("fence.out");

    int numFences;
    fin >> numFences;
    map<int, multiset<int>> graph;
    for (int i = 0; i < numFences; ++i) {
        int a, b;
        fin >> a >> b;
        graph[a].insert(b);
        graph[b].insert(a);
    }

    int start = findStart(graph);
    stack<int> s;
    vector<int> path;
    s.push(start);
    while (!s.empty()) {
        auto node = s.top();
        // cout << "Node is " << node << '\t';
        if (graph[node].size() == 0) {
            // cout << " has no more neighbors!\t";
            path.push_back(node);
            // cout << " adding " << node << ',';
            s.pop();
            // while (!s.empty() && s.top() != node) {
            //     path.push_back(s.top());
            //     // cout << s.top() << ',';
            //     s.pop();
            // }
            // if (!s.empty()) {
            //     path.push_back(s.top());
            //     // cout << node << ',';
            //     s.pop();
            // }
            // // cout << '\n';
        } else {
            auto neighbor = *begin(graph[node]);
            // cout << " has " << graph[node].size() << " neighbors, adding " << neighbor << '\n';
            s.push(neighbor);
            auto it = graph[node].find(neighbor);
            graph[node].erase(it);
            it = graph[neighbor].find(node);
            graph[neighbor].erase(it);
        }
    }
    for (auto&& kv : graph) {
        if (kv.second.size() == 0) {
            continue;
        }
        cout << kv.first << '\t';
        for (auto n : kv.second) {
            cout << n << ',';
        }
        cout << '\n';
    }
    reverse(begin(path), end(path));
    for (auto node : path) {
        fout << node << '\n';
    }

    return EXIT_SUCCESS;
}
