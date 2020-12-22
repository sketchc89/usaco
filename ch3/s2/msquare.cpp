/*
ID: sketchc1
LANG: C++14
TASK: msquare
*/

// NOTE TO SELF: use 4 bits instead of 3 next time
#include <bits/stdc++.h>
using namespace std;

constexpr static int64_t NUM_SQUARES = 8;

int32_t xformA(int32_t num) {
    int rev = 0;
    // flip first and eight
    rev |= (num & 0x7) << 21;
    rev |= (num & 0xE00000) >> 21;
    // flip second and seventh
    rev |= (num & 0x38) << 15;
    rev |= (num & 0x1C0000) >> 15;
    // flip third and sixth
    rev |= (num & 0x1C0) << 9;
    rev |= (num & 0x38000) >> 9;
    // flip fourth and fifth
    rev |= (num & 0xE00) << 3;
    rev |= (num & 0x7000) >> 3;
    return rev;
}

int32_t xformB(int32_t num) {
    int32_t lower = num & 0xFFF;
    int32_t upper = num & 0xFFF000;
    // left rotate first four numbers
    lower <<= 3;
    lower |= (lower & 0x7000) >> 12;
    lower ^= (lower & 0x7000);
    // right rotate second four numbers
    upper >>= 3;
    upper |= (upper & 0xE00) << 12;
    upper ^= (upper & 0xE00);
    num = lower | upper;
    return num;
}

int32_t xformC(int32_t num) {
    int clear = num & 0xE07E07;       // mask numbers we want to swap
    clear |= (0x38 & num) << 3;       // second->third
    clear |= (0x1C0 & num) << 9;      // third->sixth
    clear |= (0x38000 & num) << 3;    // sixth->seventh
    clear |= (0x1C0000 & num) >> 15;  // seventh->second
    return clear;
}

int main() {
    // i/o
    ifstream fin("msquare.in");
    ofstream fout("msquare.out");

    // store array as integers with 3 bits
    int32_t goal = 0, start = 0;
    for (int i = 0; i < NUM_SQUARES; ++i) {
        int val;
        fin >> val;
        --val;
        goal |= val << (3 * i);
        start |= i << (3 * i);
    }

    // use queue and try all combinations
    queue<pair<int, string>> q;
    q.emplace(make_pair(start, ""));
    int count = 0;
    unordered_set<int32_t> visited;
    while (!q.empty()) {
        ++count;
        auto num = q.front().first;
        auto str = q.front().second;
        q.pop();
        if (visited.count(num)) {
            continue;
        } else {
            visited.insert(num);
        }
        if (num == goal) {
            fout << str.size() << '\n' << str << '\n';
            break;
        }

        str.push_back('A');
        q.push({xformA(num), str});
        str.pop_back();

        str.push_back('B');
        q.push({xformB(num), str});
        str.pop_back();

        str.push_back('C');
        q.push({xformC(num), str});
        str.pop_back();
    }

    return EXIT_SUCCESS;
}
