/*
ID: sketchc1
LANG: C++14
TASK: beads
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // i/o
    ifstream fin("beads.in");
    ofstream fout("beads.out");

    string nstr, beads;
    getline(fin, nstr);  // unneeded
    getline(fin, beads);
    int N = beads.size();
    char curChar = beads[0];
    vector<int> dp(N, 1);
    int nonBlueBeads = 0;
    for (nonBlueBeads = 0; nonBlueBeads < N; ++nonBlueBeads) {
        if (beads[nonBlueBeads] == 'b') {
            break;
        }
    }

    if (nonBlueBeads == N) {
        fout << N << '\n';
        return EXIT_SUCCESS;
    }
    int nonRedBeads = 0;
    for (nonRedBeads = 0; nonRedBeads < N; ++nonRedBeads) {
        if (beads[nonRedBeads] == 'r') {
            break;
        }
    }
    if (nonRedBeads == N) {
        fout << N << '\n';
        return EXIT_SUCCESS;
    }

    int maxBeads = 2;
    int maxBeadPos = 1;
    for (int i = 1; i < N; ++i) {
        if (beads[i] != beads[i - 1]) {
            auto tempI = beads[i];
            auto tempIminus1 = beads[i - 1];
            if (beads[i] == 'w') {
                if (beads[i - 1] == 'r') {
                    beads[i] = 'b';
                } else {
                    beads[i] = 'r';
                }
            } else if (beads[i - 1] == 'w') {
                if (beads[i] == 'r') {
                    beads[i - 1] = 'b';
                } else {
                    beads[i - 1] = 'r';
                }
            }


            int inc = i;
            int dec = i - 1;
            while (beads[inc] == beads[i] || beads[inc] == 'w') {
                // cout << "Increasing: " << i << '-' << inc << '\n';
                inc = (inc + 1) % N;
            }
            auto incBeads = ((inc - i) % N + N) % N;
            while (beads[dec] == beads[i - 1] || beads[dec] == 'w') {
                // cout << "Decreasing: " << i - 1 << '-' << dec << '\n';
                dec = ((dec - 1) % N + N) % N;
            }
            auto decBeads = ((i - 1 - dec) % N + N) % N;
            // cout << "Break position " << i << " increasing beads " << incBeads << " decreasing beads " << decBeads << '\n';
            maxBeads = max(maxBeads, incBeads + decBeads);
            beads[i] = tempI;
            beads[i - 1] = tempIminus1;
        }
    }

    fout << maxBeads << '\n';


    return EXIT_SUCCESS;
}
