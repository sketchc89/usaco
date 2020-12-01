/*
ID: sketchc1
LANG: C++14
TASK: friday
*/
#include <bits/stdc++.h>
using namespace std;

bool isLeapYear(int year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

int main() {
    // i/o
    ifstream fin("friday.in");
    ofstream fout("friday.out");

    int years, count = 0;
    fin >> years;
    vector<int> dowCount(7, 0);
    int dayOfWeek = 0;
    vector<int> days{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    while (count < years) {
        for (auto monthDay : days) {
            dowCount[dayOfWeek]++;
            dayOfWeek = (dayOfWeek + monthDay) % 7;
            if (monthDay == 28 && isLeapYear(1900 + count)) {
                dayOfWeek = (dayOfWeek + 1) % 7;
            }
        }
        ++count;
    }
    for (auto i = 0; i < dowCount.size(); ++i) {
        fout << dowCount[i];
        if (i < dowCount.size() - 1) {
            fout << ' ';
        }
    }
    fout << '\n';

    return EXIT_SUCCESS;
}
