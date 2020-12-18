/*
ID: sketchc1
LANG: C++14
TASK: humble
*/
#include <bits/stdc++.h>
using namespace std;

constexpr static int MAX_N = 10000001;

int main() {
    // i/o
    ifstream fin("humble.in");
    ofstream fout("humble.out");

    int numPrimes, nth;
    fin >> numPrimes >> nth;

    vector<int64_t> primes(numPrimes);
    for (int i = 0; i < primes.size(); ++i) {
        fin >> primes[i];
    }

    priority_queue<int64_t, vector<int64_t>, greater<int64_t>> pq;
    set<int64_t> seen;

    pq.push(1);
    while (!pq.empty()) {
        auto val = pq.top();
        pq.pop();
        for (auto p : primes) {
            auto num = val * p;
            if (!seen.count(num)) {
                if (seen.size() == nth) {
                    if (num > *prev(end(seen))) {  //
                        break;
                    } else {
                        // cout << "Ejecting " << *prev(end(seen)) << " and adding new num " << num << '\t' << " size " << seen.size() <<
                        // '\n';
                        seen.insert(num);
                        pq.push(num);
                        seen.erase(prev(end(seen)));
                    }
                } else {
                    pq.push(num);
                    seen.insert(num);
                }
            }
        }
    }
    fout << *prev(end(seen)) << '\n';

    return EXIT_SUCCESS;
}
