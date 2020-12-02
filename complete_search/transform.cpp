/*
ID: sketchc1
LANG: C++14
TASK: transform
*/
#include <bits/stdc++.h>
using namespace std;

bool isRot90(const vector<vector<char>>& a, const vector<vector<char>>& b) {
    int N = a.size();
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (a[r][c] != b[c][N - r - 1]) {
                return false;
            }
        }
    }
    return true;
}

bool isRot180(const vector<vector<char>>& a, const vector<vector<char>>& b) {
    int N = a.size();
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (a[r][c] != b[N - r - 1][N - c - 1]) {
                return false;
            }
        }
    }
    return true;
}

bool isRot270(const vector<vector<char>>& a, const vector<vector<char>>& b) {
    int N = a.size();
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (a[r][c] != b[N - c - 1][r]) {
                return false;
            }
        }
    }
    return true;
}

bool isReflection(const vector<vector<char>>& a, const vector<vector<char>>& b) {
    int N = a.size();
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (a[r][c] != b[r][N - c - 1]) {
                return false;
            }
        }
    }
    return true;
}

void reflect(vector<vector<char>>& a) {
    int N = a.size();
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N / 2; ++c) {
            swap(a[r][c], a[r][N - c - 1]);
        }
    }
}

bool isSame(const vector<vector<char>>& a, const vector<vector<char>>& b) {
    // no change
    int N = a.size();
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (a[r][c] != b[r][c]) {
                return false;
            }
        }
    }
    return true;
}


int main() {
    // i/o
    ifstream fin("transform.in");
    ofstream fout("transform.out");

    string nStr, rowStr;
    getline(fin, nStr);
    stringstream ss(nStr);
    int N;
    ss >> N;

    vector<vector<char>> a(N, vector<char>(N)), b(N, vector<char>(N));
    for (int r = 0; r < N; ++r) {
        getline(fin, rowStr);
        assert(rowStr.size() == N);
        for (int c = 0; c < N; ++c) {
            a[r][c] = rowStr[c];
        }
    }
    for (int r = 0; r < N; ++r) {
        getline(fin, rowStr);
        assert(rowStr.size() == N);
        for (int c = 0; c < N; ++c) {
            b[r][c] = rowStr[c];
        }
    }

    if (isRot90(a, b)) {
        fout << 1 << '\n';
        return EXIT_SUCCESS;
    }

    if (isRot180(a, b)) {
        fout << 2 << '\n';
        return EXIT_SUCCESS;
    }

    if (isRot270(a, b)) {
        fout << 3 << '\n';
        return EXIT_SUCCESS;
    }

    if (isReflection(a, b)) {
        fout << 4 << '\n';
        return EXIT_SUCCESS;
    }

    reflect(a);
    if (isRot90(a, b) || isRot180(a, b) || isRot270(a, b)) {
        fout << 5 << '\n';
        return EXIT_SUCCESS;
    }
    reflect(a);

    if (isSame(a, b)) {
        fout << 6 << '\n';
        return EXIT_SUCCESS;
    }

    fout << 7 << '\n';
    return EXIT_SUCCESS;
}
