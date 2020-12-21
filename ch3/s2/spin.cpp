/*
ID: sketchc1
LANG: C++14
TASK: spin
*/
#include <bits/stdc++.h>
using namespace std;

struct Wheel {
    int speed;
    vector<int> openings;
    vector<int> endings;
};

void inputWheel(Wheel& w, ifstream& fin) {
    int numOpenings;
    fin >> w.speed;
    fin >> numOpenings;
    for (int i = 0; i < numOpenings; ++i) {
        int start, end, ext;
        fin >> start >> ext;
        end = (start + ext) % 360;
        w.openings.push_back(start);
        w.endings.push_back(end);
    }
}

void incrementWheel(Wheel& w) {
    for (int i = 0; i < w.openings.size(); ++i) {
        w.openings[i] = (w.openings[i] + w.speed) % 360;
        w.endings[i] = (w.endings[i] + w.speed) % 360;
    }
}

bool linedUp(vector<Wheel>& wheels) {
    map<int, int> open;
    for (auto& w : wheels) {
        for (int i = 0; i < w.openings.size(); ++i) {
            if (w.openings[i] < w.endings[i]) {
                open[w.openings[i]]++;
                open[(w.endings[i] + 1) % 360]--;
            } else {
                open[0]++;
                open[w.openings[i]]++;
                open[(w.endings[i] + 1) % 360]--;
            }
        }
    }
    int numLinedUp = 0;
    for (auto&& kv : open) {
        numLinedUp += kv.second;
        if (numLinedUp == 5) {
            return true;
        }
    }
    return false;
}


int main() {
    // i/o
    ifstream fin("spin.in");
    ofstream fout("spin.out");

    vector<Wheel> wheels(5);
    for (auto& w : wheels) {
        inputWheel(w, fin);
    }
    int t = 0;
    // would be better to check for a cycle,
    // or that every wheel is back at its starting position with LCM
    // but i am le tired
    while (t < 10000) {
        if (linedUp(wheels)) {
            break;
        }
        for (auto& w : wheels) {
            incrementWheel(w);
        }
        ++t;
    }
    if (t == 10000) {
        fout << "none\n";
    } else {
        fout << t << '\n';
    }

    return EXIT_SUCCESS;
}
