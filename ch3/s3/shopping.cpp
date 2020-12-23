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
    Offer()
            : prod{}
            , price{} {}

    Offer(unordered_map<int, int> _prod, int _price)
            : prod{_prod}
            , price{_price} {}

    unordered_map<int, int> prod;
    int price;
};

int main() {
    // i/o
    ifstream fin("shopping.in");
    ofstream fout("shopping.out");

    int numOffers;
    fin >> numOffers;
    vector<Offer> offers(numOffers);
    // cout << "offers: " << offers.size() << '\n';
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

    int numProducts;
    fin >> numProducts;
    unordered_map<int, int> needs;
    unordered_map<char, int> sku;
    offers.resize(numProducts + numOffers);
    // cout << "offers: " << offers.size() << '\n';
    for (int i = 0; i < numProducts; ++i) {
        int productNumber, productQuantity, productPrice;
        fin >> productNumber >> productQuantity >> productPrice;
        sku['a' + i] = productNumber;
        needs[productNumber] = productQuantity;
        // cout << productNumber << '\t' << productQuantity << '\t' << productPrice << '\n';
        offers[i + numOffers].prod[productNumber] = 1;
        offers[i + numOffers].price = productPrice;
    }

    // for (int i = 0; i < offers.size(); ++i) {
    //     cout << "Offer# " << i << '\t' << "$" << offers[i].price << '\t';
    //     for (auto&& kv : offers[i].prod) {
    //         cout << "prod: " << kv.first << " quantity; " << kv.second << '\t';
    //     }
    //     cout << '\n';
    // }

    // for (auto&& kv : sku) {
    //     cout << static_cast<char>(kv.first) << ':' << kv.second << '\n';
    // }


    auto dp = array<array<array<array<array<int, SZ>, SZ>, SZ>, SZ>, SZ>{};
    for (int a = 0; a < SZ; ++a) {
        for (int b = 0; b < SZ; ++b) {
            for (int c = 0; c < SZ; ++c) {
                for (int d = 0; d < SZ; ++d) {
                    for (int e = 0; e < SZ; ++e) {
                        dp[a][b][c][d][e] = INF;
                    }
                }
            }
        }
    }
    dp[0][0][0][0][0] = 0;

    int qtyA = sku.count('a') ? needs[sku['a']] : 0;
    int qtyB = sku.count('b') ? needs[sku['b']] : 0;
    int qtyC = sku.count('c') ? needs[sku['c']] : 0;
    int qtyD = sku.count('d') ? needs[sku['d']] : 0;
    int qtyE = sku.count('e') ? needs[sku['e']] : 0;

    // cout << "Quantity: " << qtyA << ' ' << qtyB << ' ' << qtyC << ' ' << qtyD << ' ' << qtyE << '\n';
    for (int a = 0; a <= qtyA; ++a) {
        for (int b = 0; b <= qtyB; ++b) {
            for (int c = 0; c <= qtyC; ++c) {
                for (int d = 0; d <= qtyD; ++d) {
                    for (int e = 0; e <= qtyE; ++e) {
                        for (int i = 0; i < offers.size(); ++i) {
                            // cout << "Offer: " << i << '\n';
                            int prevA, prevB, prevC, prevD, prevE;
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
                            // cout << "Previous " << prevA << ',' << prevB << ',' << prevC << ',' << prevD << ',' << prevE <<
                            // '\n';
                            if (prevA < 0 || prevB < 0 || prevC < 0 || prevD < 0 || prevE < 0) {
                                continue;
                            }
                            if (dp[prevA][prevB][prevC][prevD][prevE] != INF) {
                                // cout << "Found a price for " << a << ',' << b << ',' << c << ',' << d << ',' << e << '\t';
                                dp[a][b][c][d][e] = min(dp[a][b][c][d][e], dp[prevA][prevB][prevC][prevD][prevE] + offers[i].price);
                                // cout << "previously " << setw(3) << dp[prevA][prevB][prevC][prevD][prevE] << '\t';
                                // cout << "price " << setw(3) << offers[i].price << '\t';
                                // cout << "now " << setw(3) << dp[a][b][c][d][e] << '\n';
                            }
                        }
                    }
                }
            }
        }
    }
    fout << dp[qtyA][qtyB][qtyC][qtyD][qtyE] << '\n';


    // int bestRes = minPrice(0, needs, offers);
    return EXIT_SUCCESS;
}
