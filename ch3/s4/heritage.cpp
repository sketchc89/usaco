/*
ID: sketchc1
LANG: C++14
TASK: heritage
*/
#include <bits/stdc++.h>
using namespace std;

string constructBTree(int inL, int inR, const string& inS, int preL, int preR, const string& preS) {
    // out of range
    if (inL > inR || preL > preR || inL < 0 || preL < 0 || inR >= inS.size() || preR >= preS.size()) {
        return "";
    }
    // first of pre-order is the root, split inorder at that character and record sizes
    // split preorder based on sizes
    char rootChar = preS[preL];
    int rootPos = inS.find(rootChar, inL);
    if (rootPos == string::npos) {
        cerr << "FATAL: root char not found\n";
        abort();
    }
    int lSize = rootPos - inL;
    // int rSize = inR - rootPos + 1;
    return constructBTree(inL, rootPos - 1, inS, preL + 1, preL + lSize, preS)
            + constructBTree(rootPos + 1, inR, inS, preL + lSize + 1, preR, preS) + string(1, rootChar);
}

int main() {
    // i/o
    ifstream fin("heritage.in");
    ofstream fout("heritage.out");

    string inorder, preorder;
    fin >> inorder >> preorder;
    int N = inorder.size();

    string s;
    s = constructBTree(0, N - 1, inorder, 0, N - 1, preorder);
    fout << s << '\n';

    return EXIT_SUCCESS;
}
