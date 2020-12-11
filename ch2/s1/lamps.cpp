/*
ID: sketchc1
LANG: C++14
TASK: lamps
*/
#include <bits/stdc++.h>
using namespace std;


template <size_t N>
inline bool operator<(const std::bitset<N>& lhs, const std::bitset<N>& rhs) {
    if (lhs == rhs) {
        return true;
    }
    for (int i = N - 1; i >= 0; --i) {
        if (lhs[i] ^ rhs[i]) {
            return rhs[i];
        }
    }
    return true;
}

int main() {
    // i/o
    ifstream fin("lamps.in");
    ofstream fout("lamps.out");

    int numLamps, counter, val;
    fin >> numLamps;
    fin >> counter;
    bitset<6> onLamps(0), offLamps(0);
    bitset<6> lamps;
    vector<bitset<6>> buttons(4, 0);
    buttons[0].set();
    lamps.set();
    for (int i = 0; i < buttons[1].size(); i += 2) {
        buttons[1].set(i);
    }
    for (int i = 1; i < buttons[2].size(); i += 2) {
        buttons[2].set(i);
    }
    for (int i = 0; i < buttons[3].size(); i += 3) {
        buttons[3].set(i);
    }
    fin >> val;
    while (val != -1) {
        onLamps.set((val - 1) % 6);  // 0 indexed
        fin >> val;
    }
    fin >> val;
    while (val != -1) {
        offLamps.set((val - 1) % 6);  // 0 indexed
        fin >> val;
    }
    if ((onLamps & offLamps) != 0) {
        fout << "IMPOSSIBLE\n";
        return EXIT_SUCCESS;
    }

    set<unsigned long> s;
    bool possible = false;
    if (counter == 0) {  // try nothin
        if ((onLamps & lamps) == onLamps && (offLamps & ~lamps) == offLamps) {
            possible = true;
            s.insert(lamps.to_ulong());
        }
    } else if (counter == 1) {  // try each button once
        for (int b = 0; b < buttons.size(); ++b) {
            lamps.set();
            lamps ^= buttons[b];
            if ((onLamps & lamps) == onLamps && (offLamps & ~lamps) == offLamps) {
                possible = true;
                s.insert(lamps.to_ulong());
            }
        }
    } else {  // try each combination of buttons
        for (int light = 0; light < (1 << 4); ++light) {
            lamps.set();
            for (int b = 0; b < buttons.size(); ++b) {
                if (light & (1 << b)) {
                    lamps ^= buttons[b];
                }
            }
            if ((onLamps & lamps) == onLamps && (offLamps & ~lamps) == offLamps) {
                possible = true;
                s.insert(lamps.to_ulong());
            }
        }
    }

    if (!possible) {
        fout << "IMPOSSIBLE\n";
    } else {
        set<string> strs;
        for (auto state : s) {
            bitset<6> bs(state);
            string str = "";
            for (int b = 0; b < numLamps; ++b) {
                str.push_back(static_cast<char>('0' + bs[b % 6]));
            }
            strs.insert(str);
        }
        for (auto str : strs) {
            fout << str << '\n';
        }
    }

    return EXIT_SUCCESS;
}
