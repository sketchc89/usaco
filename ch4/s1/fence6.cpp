/*
ID: sketchc1
LANG: C++14
TASK: fence6
*/
#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = 1'000'000'000;

struct Segment {
    int id;
    int weight;
    vector<int> connA, connB;
    char aId, bId;
};

int dijksta(int aId, int bId, const vector<vector<int>>& mat) {
    int N = mat.size();
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(N, INF), visited(N, 0);
    dist[aId] = 0;
    pq.emplace(make_pair(0, aId));
    while (!pq.empty()) {
        auto node = pq.top().second;
        pq.pop();
        if (visited[node]) {
            continue;
        } else {
            visited[node] = 1;
        }
        for (int i = 0; i < mat[node].size(); ++i) {
            if (mat[node][i] == INF) {
                continue;
            }
            if (dist[node] + mat[node][i] < dist[i]) {
                dist[i] = dist[node] + mat[node][i];
                pq.emplace(make_pair(dist[i], i));
            }
        }
    }
    return dist[bId];
}

void nameEnd(Segment& seg, vector<Segment>& segs, int& currName) {
    assert(seg.connA.size() > 0);
    if (seg.connA[0] >= seg.id) {
        seg.aId = currName;
        ++currName;
    } else {
        /* Check if connA from seg matches connA from the earlier node
         * if it does then assign it the id of the a side
         * if it doesn't then assign it the id of the b side */
        const auto& earlySeg = segs[seg.connA[0]];
        bool match = true;
        for (int i = 0; i < earlySeg.connA.size(); ++i) {
            if (earlySeg.connA[i] != seg.connA[i]) {
                match = false;
                break;
            }
        }
        if (match) {
            seg.aId = earlySeg.aId;
        } else {
            seg.aId = earlySeg.bId;
        }
    }

    if (seg.connB[0] >= seg.id) {
        seg.bId = currName;
        ++currName;
    } else {
        /* Check if connA from seg matches connA from the earlier node
         * if it does then assign it the id of the a side
         * if it doesn't then assign it the id of the b side */
        const auto& earlySeg = segs[seg.connB[0]];
        bool match = true;
        for (int i = 0; i < earlySeg.connA.size(); ++i) {
            if (earlySeg.connA[i] != seg.connB[i]) {
                match = false;
                break;
            }
        }
        if (match) {
            seg.bId = earlySeg.aId;
        } else {
            seg.bId = earlySeg.bId;
        }
    }
}

int main() {
    // i/o
    ifstream fin("fence6.in");
    ofstream fout("fence6.out");

    int numSegments;
    fin >> numSegments;

    unordered_map<int, unordered_map<int, int>> graph;
    unordered_map<int, int> lengths;

    /* Read all of the input into a custom struct so we can pick it apart
     * Really terrible input format that is more difficult to handle than the problem itself */
    vector<Segment> segments(numSegments);
    for (int i = 0; i < numSegments; ++i) {
        int id, weight, numConnA, numConnB;
        fin >> id >> weight >> numConnA >> numConnB;
        --id;
        segments[id].id = id;
        segments[id].weight = weight;
        segments[id].connA.resize(numConnA);
        segments[id].connB.resize(numConnB);
        for (int j = 0; j < segments[id].connA.size(); ++j) {
            fin >> segments[id].connA[j];
            --segments[id].connA[j];
        }
        for (int j = 0; j < segments[id].connB.size(); ++j) {
            fin >> segments[id].connB[j];
            --segments[id].connB[j];
        }
        segments[id].connA.push_back(id);
        segments[id].connB.push_back(id);
        sort(begin(segments[id].connA), end(segments[id].connA));
        sort(begin(segments[id].connB), end(segments[id].connB));
    }

    /* Name the nodes at the end of each segment
     * Give a new name if the node hasn't been seen
     * Use the old name if the node has already been seen before */
    int currName = 0;
    for (int i = 0; i < segments.size(); ++i) {
        nameEnd(segments[i], segments, currName);
    }
    int N = currName;

    /* create an adjacency matrix from segment-node struct */
    vector<vector<int>> mat(N, vector<int>(N, INF));
    for (int i = 0; i < segments.size(); ++i) {
        mat[segments[i].aId][segments[i].bId] = segments[i].weight;
        mat[segments[i].bId][segments[i].aId] = segments[i].weight;
    }

    /* Remove segment from graph,
     * Calculate the shortest path from one end of segment to other end of segment
     * Add the segment length
     * The minimum cycle is the smallest after doing this for every segment */
    int minCycle = INF;
    for (int seg = 0; seg < segments.size(); ++seg) {
        // cout << "removing segment " << seg << '\n';
        int cycleLength = segments[seg].weight;
        if (cycleLength > minCycle) {
            // give up early, because the segment is already longer than the longest cycle
            continue;
        }
        int temp = INF;
        int aId = segments[seg].aId;
        int bId = segments[seg].bId;
        swap(temp, mat[aId][bId]);  // store old value
        cycleLength += dijksta(aId, bId, mat);
        minCycle = min(minCycle, cycleLength);
        swap(temp, mat[aId][bId]);  // replace old value
    }

    fout << minCycle << '\n';


    return EXIT_SUCCESS;
}
