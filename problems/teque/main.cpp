/*
 * https://open.kattis.com/problems/teque
 * Author: Xiaochen Zhu, xczhu@proton.me
 */

#include <bits/stdc++.h>
using namespace std;

int n;
string op;
long long x;
deque<long long> l1, l2;  // len(l1) == len(l2) or len(l2) + 1

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> op >> x;
        if (op[0] == 'g') {
            if (x >= l1.size()) {
                cout << l2.at(x - l1.size()) << endl;
            } else {
                cout << l1.at(x) << endl;
            }
        } else
            switch (op[5]) {
                case 'b':
                    l2.push_back(x);
                    if (l2.size() == l1.size() + 1) {
                        // l2 is too big, move the first in l2 to last in l1
                        l1.push_back(l2.front());
                        l2.pop_front();
                    }
                    break;
                case 'f':
                    l1.push_front(x);
                    if (l1.size() == l2.size() + 2) {
                        l2.push_front(l1.back());
                        l1.pop_back();
                    }
                    break;
                case 'm':
                    l1.push_back(x);
                    if (l1.size() == l2.size() + 2) {
                        l2.push_front(l1.back());
                        l1.pop_back();
                    }
                    break;
            }
    }

    return 0;
}