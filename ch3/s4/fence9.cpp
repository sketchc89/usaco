/*
ID: sketchc1
LANG: C++14
TASK: fence9
*/
#include <bits/stdc++.h>
using namespace std;

// true if positive, false if negative
template <typename T>
T signCrossProduct(const pair<T, T>& a, const pair<T, T>& b, const pair<T, T>& p) {
    // cross product ab x ap where z is 0
    T left = (b.first - a.first) * (p.second - a.second);
    T right = (b.second - a.second) * (p.first - a.first);
    if (left == right) {
        return 0;
    } else if (left > right) {
        return 1;
    } else {
        return -1;
    }
}

int main() {
    // i/o
    ifstream fin("fence9.in");
    ofstream fout("fence9.out");

    int n, m, p;
    fin >> n >> m >> p;
    auto A = make_pair(0, 0), B = make_pair(n, m), C = make_pair(p, 0);
    pair<double, double> midpoint = make_pair((n + p) / 3.0, m / 3.0);
    pair<double, double> a = A, b = B, c = C;
    int signAB = signCrossProduct(a, b, midpoint);
    int signAC = signCrossProduct(a, c, midpoint);
    int signBC = signCrossProduct(b, c, midpoint);

    // cout << signAB << '\t' << signAC << '\t' << signBC << '\n';

    int64_t res = 0;
    int prevY = 1;
    bool goingUp = true;
    for (int x = 1; x < max(n, p); ++x) {
        if (x == n + 1) {
            // cout << "Past the x position of the top of the triangle\n";
            goingUp = false;  // going down from outside to in
            prevY = m;        // set outside the triangle
            // cout << "Previous y is now " << prevY << '\n';
        }
        int y = prevY;
        while (true) {
            auto pt = make_pair(x, y);
            auto crossABP = signCrossProduct(A, B, pt);
            auto crossACP = signCrossProduct(A, C, pt);
            auto crossBCP = signCrossProduct(B, C, pt);
            // cout << crossABP << '\t' << crossACP << '\t' << crossBCP << '\n';
            if (goingUp) {
                if (signAB != crossABP || signAC != crossACP || signBC != crossBCP) {
                    cout << "Outside at " << x << ',' << y << "\tLast inside at " << y - 1 << "\t";
                    res += y - 1;
                    prevY = max(prevY, y - 1);  // last inside the triangle. start inside again
                    break;
                } else {
                    cout << "Inside at " << x << ',' << y << '\t';
                }
                ++y;
            } else {
                if (signAB == crossABP && signAC == crossACP && signBC == crossBCP) {
                    cout << "Inside the triangle breaking. Last outside at " << y + 1 << "\t";
                    res += y;
                    prevY = min(prevY, y + 1);  // last outside the triangle. start outside again
                    break;
                } else if (y == 0) {
                    break;
                } else {
                    cout << "Outside at " << x << ',' << y << '\t';
                }
                --y;
            }
        }

        cout << "Counted " << res << " lattice points at x = " << x << '\n';
    }
    cout << "Now removing\n";
    if (p < n) {
        prevY = 1;
        for (int x = p + 1; x < max(n, p); ++x) {
            int y = prevY;
            while (true) {
                auto pt = make_pair(x, y);
                auto crossABP = signCrossProduct(A, B, pt);
                auto crossACP = signCrossProduct(A, C, pt);
                auto crossBCP = signCrossProduct(B, C, pt);
                if (signAB == crossABP && signAC == crossACP && signBC == crossBCP) {
                    cout << "Inside the triangle breaking. Last outside at " << y - 1 << "\t";
                    res -= y - 1;
                    prevY = max(prevY, y - 1);  // last outside the triangle. start outside again
                    break;
                } else if (y >= m) {
                    break;
                } else {
                    cout << "Outside at " << x << ',' << y << '\t';
                }
                ++y;
            }
            cout << "Counted " << res << " lattice points at x = " << x << '\n';
        }
    }

    fout << res << '\n';

    return EXIT_SUCCESS;
}
