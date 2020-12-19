/*
ID: sketchc1
LANG: C++14
TASK: fact4
*/
#include <bits/stdc++.h>
using namespace std;


int main() {
    // i/o
    ifstream fin("fact4.in");
    ofstream fout("fact4.out");

    int n;
    fin >> n;

    int val = 1;
    for (int i = 1; i <= n; ++i) {
        int temp = i;

        // get rid of zeros at the end
        while (temp % 10 == 0) {
            temp /= 10;
        }

        val *= temp;

        // get rid of zeros at the end
        while (val % 10 == 0) {
            val /= 10;
        }
        // leave as many digits as i will have
        if (i > 1000 && val > 10000) {
            val %= 10000;
        } else if (i > 100 && val > 1000) {
            val %= 1000;
        } else if (i > 10 && val > 100) {
            val %= 100;
        } else {
            val %= 10;
        }
    }
    val %= 10;

    fout << val << '\n';


    return EXIT_SUCCESS;
}
