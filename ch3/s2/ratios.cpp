/*
ID: sketchc1
LANG: C++14
TASK: ratios
*/
#include <bits/stdc++.h>
using namespace std;

constexpr static int NUM_MIXES = 3;
constexpr static int MAX_MIX = 128;

struct Mix {
    Mix()
            : a{}
            , b{}
            , c{} {}
    Mix(int _a, int _b, int _c)
            : a{_a}
            , b{_b}
            , c{_c} {}
    int a, b, c;
};

Mix operator+(const Mix& lhs, const Mix& rhs) {
    return Mix(lhs.a + rhs.a, lhs.b + rhs.b, lhs.c + rhs.c);
}

Mix operator*(int scalar, const Mix& m) {
    return Mix(scalar * m.a, scalar * m.b, scalar * m.c);
}

Mix operator*(const Mix& m, int scalar) {
    return scalar * m;
}

bool operator==(const Mix& lhs, const Mix& rhs) {
    return lhs.a == rhs.a && lhs.b == rhs.b && lhs.c == rhs.c;
}

bool operator<(const Mix& lhs, const Mix& rhs) {
    if (lhs.a != rhs.a) {
        return lhs.a < rhs.a;
    } else if (lhs.b != rhs.b) {
        return lhs.b < rhs.b;
    } else {
        return lhs.c < rhs.c;
    }
}

int main() {
    // i/o
    ifstream fin("ratios.in");
    ofstream fout("ratios.out");

    Mix goal;
    vector<Mix> mixes(NUM_MIXES);
    fin >> goal.a >> goal.b >> goal.c;
    for (int i = 0; i < mixes.size(); ++i) {
        fin >> mixes[i].a >> mixes[i].b >> mixes[i].c;
    }

    // unordered_map is better but dont want to write hash function
    map<Mix, int> goalMixes;
    for (int fact = 1; fact < MAX_MIX; ++fact) {
        goalMixes.emplace(make_pair(fact * goal, fact));
    }

    // brute force, try every combination and see if it is in goal ratios, chosose best
    bool found = false;
    int bestA = INT32_MAX, bestB = INT32_MAX, bestC = INT32_MAX, bestMix = INT32_MAX;
    for (int a = 0; a < MAX_MIX; ++a) {
        for (int b = 0; b < MAX_MIX; ++b) {
            for (int c = 0; c < MAX_MIX; ++c) {
                Mix m = a * mixes[0] + b * mixes[1] + c * mixes[2];
                auto it = goalMixes.find(m);
                if (it != end(goalMixes)) {
                    found = true;
                    if (it->second < bestMix) {
                        bestMix = it->second;
                        bestA = a;
                        bestB = b;
                        bestC = c;
                    }
                }
            }
        }
    }

    if (bestMix == INT32_MAX) {
        fout << "NONE\n";
    } else {
        fout << bestA << ' ' << bestB << ' ' << bestC << ' ' << bestMix << '\n';
    }

    return EXIT_SUCCESS;
}
