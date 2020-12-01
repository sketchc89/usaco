/*
ID: sketchc1
LANG: C++
TASK: ride
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
  constexpr static int MOD = 47;

  // i/o
  ifstream fin("ride.in");
  ofstream fout("ride.out");

  string comet, ufo;
  getline(fin, comet);
  getline(fin, ufo);

  // calculation
  int a = 1, b = 1;
  for (char c : comet) {
    a *= static_cast<int>(c - 'A' + 1);
  }
  for (char c : ufo) {
    b *= static_cast<int>(c - 'A' + 1);
  }
  a %= MOD;
  b %= MOD;

  // output
  string res = a == b ? "GO" : "STAY";
  fout << res << '\n';

  return EXIT_SUCCESS;
}
