/*
ID: sketchc1
LANG: C++14
TASK: shopping
*/
#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = 1'000'000'000;
constexpr static int SZ = 6;

struct Offer {
    unordered_map<int, int> prod;
    int price;
};

int main() {
    // i/o
    ifstream fin("shopping.in");
    ofstream fout("shopping.out");

    /* Record all special offers */
    int numOffers;
    fin >> numOffers;
    vector<Offer> offers(numOffers);
    for (int i = 0; i < offers.size(); ++i) {
        int numProducts;
        fin >> numProducts;
        for (int j = 0; j < numProducts; ++j) {
            int prod, qty;
            fin >> prod >> qty;
            offers[i].prod[prod] = qty;
        }
        fin >> offers[i].price;
    }

    /* Record every normal price as an offer of one product */
    int numProducts;
    fin >> numProducts;
    unordered_map<int, int> needs;  // what customer needs to buy
    unordered_map<char, int> sku;   // mapping between dimension of dp and product number
    offers.resize(numProducts + numOffers);
    for (int i = 0; i < numProducts; ++i) {
        int productNumber, productQuantity, productPrice;
        fin >> productNumber >> productQuantity >> productPrice;

        sku['a' + i] = productNumber;
        needs[productNumber] = productQuantity;
        offers[i + numOffers].prod[productNumber] = 1;
        offers[i + numOffers].price = productPrice;
    }

    /* represent the minimum price for a items w/ product number sku['a'] b items w// product number sku['b'], ...*/
    auto dp = array<array<array<array<array<int, SZ>, SZ>, SZ>, SZ>, SZ>{};
    for (int a = 0; a < SZ; ++a) {
        for (int b = 0; b < SZ; ++b) {
            for (int c = 0; c < SZ; ++c) {
                for (int d = 0; d < SZ; ++d) {
                    for (int e = 0; e < SZ; ++e) {
                        dp[a][b][c][d][e] = INF;  // set to high value
                    }
                }
            }
        }
    }
    dp[0][0][0][0][0] = 0;

    // upper bound inclusive for 5d loop
    int qtyA = sku.count('a') ? needs[sku['a']] : 0;
    int qtyB = sku.count('b') ? needs[sku['b']] : 0;
    int qtyC = sku.count('c') ? needs[sku['c']] : 0;
    int qtyD = sku.count('d') ? needs[sku['d']] : 0;
    int qtyE = sku.count('e') ? needs[sku['e']] : 0;

    // note loop is inclusive of upper bound
    for (int a = 0; a <= qtyA; ++a) {
        for (int b = 0; b <= qtyB; ++b) {
            for (int c = 0; c <= qtyC; ++c) {
                for (int d = 0; d <= qtyD; ++d) {
                    for (int e = 0; e <= qtyE; ++e) {
                        for (int i = 0; i < offers.size(); ++i) {
                            int prevA, prevB, prevC, prevD, prevE;
                            // check if product number exists
                            // umap [] will create key with value 0 otherwise
                            if (offers[i].prod.count(sku['a'])) {
                                prevA = a - offers[i].prod[sku['a']];
                            } else {
                                prevA = a;
                            }
                            if (offers[i].prod.count(sku['b'])) {
                                prevB = b - offers[i].prod[sku['b']];
                            } else {
                                prevB = b;
                            }
                            if (offers[i].prod.count(sku['c'])) {
                                prevC = c - offers[i].prod[sku['c']];
                            } else {
                                prevC = c;
                            }
                            if (offers[i].prod.count(sku['d'])) {
                                prevD = d - offers[i].prod[sku['d']];
                            } else {
                                prevD = d;
                            }
                            if (offers[i].prod.count(sku['e'])) {
                                prevE = e - offers[i].prod[sku['e']];
                            } else {
                                prevE = e;
                            }

                            // check that enough products bought for offer
                            if (prevA < 0 || prevB < 0 || prevC < 0 || prevD < 0 || prevE < 0) {
                                continue;
                            }
                            // update if better than previous value
                            if (dp[prevA][prevB][prevC][prevD][prevE] != INF) {
                                dp[a][b][c][d][e] = min(dp[a][b][c][d][e], dp[prevA][prevB][prevC][prevD][prevE] + offers[i].price);
                            }
                        }
                    }
                }
            }
        }
    }

    fout << dp[qtyA][qtyB][qtyC][qtyD][qtyE] << '\n';

    return EXIT_SUCCESS;
}
