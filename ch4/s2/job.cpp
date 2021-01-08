/*
ID: sketchc1
LANG: C++14
TASK: job
*/
#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = 1'000'000'000;

int main() {
    // i/o
    ifstream fin("job.in");
    ofstream fout("job.out");

    int numJobs, numA, numB;
    fin >> numJobs >> numA >> numB;
    vector<int> bTime(numB), aEnd(numJobs), bEnd(numJobs), allEnd(numJobs), bAvail(numB, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    int minA = INF;

    // process a jobs
    for (int i = 0; i < numA; ++i) {
        int rate;
        fin >> rate;
        pq.emplace(make_pair(rate, rate));
    }
    for (int job = 0; job < numJobs; ++job) {
        auto p = pq.top();
        pq.pop();
        aEnd[job] = p.first;
        p.first += p.second;
        pq.push(p);
    }
    minA = aEnd[numJobs - 1];

    // clear priority queue
    while (!pq.empty()) {
        pq.pop();
    }

    // process b jobs
    for (int i = 0; i < numB; ++i) {
        int rate;
        fin >> rate;
        pq.emplace(make_pair(rate, rate));
    }
    for (int job = 0; job < numJobs; ++job) {
        auto p = pq.top();
        pq.pop();
        bEnd[job] = p.first;
        p.first += p.second;
        pq.push(p);
    }

    // pair up the fastest time of a with the slowest time of b
    // second fastest with second slowest, etc.
    // maximum value of these is the minimum total time
    int minB = 0;
    for (int job = 0; job < numJobs; ++job) {
        if (aEnd[job] + bEnd[numJobs - 1 - job] > minB) {
            minB = aEnd[job] + bEnd[numJobs - 1 - job];
        }
    }

    fout << minA << ' ' << minB << '\n';

    return EXIT_SUCCESS;
}
