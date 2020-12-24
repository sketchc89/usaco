/*
ID: sketchc1
LANG: C++14
TASK: fence9
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // i/o
    ifstream fin("fence9.in");
    ofstream fout("fence9.out");

    double n, m, p;
    fin >> n >> m >> p;
    if (m == 0) {  // not a triangle with an area special case
        fout << 0 << '\n';
        return EXIT_SUCCESS;
    }
    //_
    //| \_
    //|   \// little prince snake eating elephant
    //|   /
    //|  /
    //| /
    //|/
    //         _//
    //       _/ /
    //     _/  /
    //   _/   /
    // _/    /
    ///     /
    //|    /
    //|   /
    //|  /
    //| /
    //|/
    // flip axis so that AC is the y axis; (m,n); (0, p)
    double slopeAB = static_cast<double>(n) / m;
    double slopeCB = static_cast<double>(n - p) / m;
    int64_t res = 0;
    for (double x = 1.0; x < m; ++x) {
        double yCB = x * slopeCB + p;
        double yAB = x * slopeAB;

        /* set y of cb to the point on the line if its very close otherwise the point outside the triangle */
        if (yCB - floor(yCB) > FLT_EPSILON) {
            yCB = floor(yCB) + 1;
        } else {
            yCB = floor(yCB);
        }
        /* set y of ab to the point on the line if its very close otherwise the point outside the triangle */
        if (ceil(yAB) - yAB > FLT_EPSILON) {
            yAB = ceil(yAB) - 1;
        } else {
            yAB = ceil(yAB);
        }

        res += max(0, static_cast<int>(yCB - yAB - 1));
    }

    fout << res << '\n';

    return EXIT_SUCCESS;
}
