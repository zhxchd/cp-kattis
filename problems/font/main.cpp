/*
 * https://open.kattis.com/problems/font
 * Author: Xiaochen Zhu, xczhu@proton.me
 * 
 * This solution is brute force and kind of slow. But it AC.
 */

#include <bits/stdc++.h>
using namespace std;

int n, res = 0, words[30] = { 0 }; // there are at most 25 words in total
string str;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> str;
        for (auto c : str) {
            // set (c - 'a')-th bit in words[i] to 1
            words[i] |= (1 << (c - 'a'));
        }
    }

    for (int choice = 0; choice < (1 << n); choice++) {
        int cover = 0;
        for (int i = 0; i < n; i++) {
            if (choice & (1 << i)) {
                // i-th word is chosen
                cover |= words[i];
                if (cover == (1 << 26) - 1) {
                    // cover all letters
                    res += 1;
                    break;
                }
            }
        }
    }

    cout << res << endl;

    return 0;
}