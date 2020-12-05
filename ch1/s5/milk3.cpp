/*
ID: sketchc1
LANG: C++14
TASK: milk3
*/
#include <bits/stdc++.h>
using namespace std;


struct Milk {
    Milk(int _a, int _b, int _c)
            : a{_a}
            , b{_b}
            , c{_c} {}
    int a, b, c;
};

bool operator<(const Milk& lhs, const Milk& rhs) {
    if (lhs.a != rhs.a) {
        return lhs.a < rhs.a;
    }
    if (lhs.b != rhs.b) {
        return lhs.b < rhs.b;
    }
    return lhs.c < rhs.c;
}

int main() {
    // i/o
    ifstream fin("milk3.in");
    ofstream fout("milk3.out");

    int a, b, c;
    fin >> a >> b >> c;
    set<Milk> s;
    vector<int> res;
    queue<Milk> q;
    q.emplace(Milk(0, 0, c));
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        if (s.count(curr)) {
            continue;
        }
        s.insert(curr);
        if (curr.a == 0) {
            res.push_back(curr.c);
        }
        // cout << "Milk: " << curr.a << '\t' << curr.b << '\t' << curr.c << '\n';
        if (curr.a > 0) {
            if (curr.b < b) {
                // cout << "Moved a to b\n";
                q.emplace(Milk(max(0, curr.a + curr.b - b), min(b, curr.a + curr.b), curr.c));
            }
            if (curr.c < c) {
                // cout << "Moved a to c\n";
                q.emplace(Milk(max(0, curr.a + curr.c - c), curr.b, min(c, curr.a + curr.c)));
            }
        }
        if (curr.b > 0) {
            if (curr.a < a) {
                // cout << "Moved b to a\n";
                q.emplace(Milk(min(a, curr.a + curr.b), max(0, curr.b + curr.a - a), curr.c));
            }
            if (curr.c < c) {
                // cout << "Moved b to c\n";
                q.emplace(Milk(curr.a, max(0, curr.b + curr.c - c), min(c, curr.b + curr.c)));
            }
        }
        if (curr.c > 0) {
            if (curr.a < a) {
                // cout << "Moved c to a\t";
                q.emplace(Milk(min(a, curr.a + curr.c), curr.b, max(0, curr.c + curr.a - a)));
                // cout << min(a, curr.a + curr.c) << curr.b << max(0, curr.c + curr.a - a) << '\n';
            }
            if (curr.b < b) {
                // cout << "Moved c to b\t";
                q.emplace(Milk(curr.a, min(b, curr.b + curr.c), max(0, curr.c + curr.b - b)));
                // cout << curr.a << '\t' << min(b, curr.b + curr.c) << '\t' << max(0, curr.c + curr.b - b) << '\n';
            }
        }
    }
    sort(begin(res), end(res));
    fout << res[0];
    // cout << "Results:\n" << res[0];
    for (int i = 1; i < res.size(); ++i) {
        // cout << ' ' << res[i];
        fout << ' ' << res[i];
    }
    fout << '\n';


    return EXIT_SUCCESS;
}
