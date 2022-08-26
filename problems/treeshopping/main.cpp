/*
 * https://open.kattis.com/problems/treeshopping
 * Author: Xiaochen Zhu, xczhu@proton.me
 */

#include <iostream>
#include <map>
using namespace std;

int n, k, d = 200000, a[200001];
map<int, int> value_count;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i < k) {
            if (value_count.find(a[i]) == value_count.end()) {
                value_count[a[i]] = 0;
            }
            value_count[a[i]] += 1;
        }
        if (i == k-1) {
            int min_v = (*value_count.begin()).first;
            int max_v = (*prev(value_count.end())).first;
            d = min(d, max_v - min_v);
        }
        if (i >= k) {
            // remove (i-k)-th element
            if (value_count[a[i-k]] == 1) {
                value_count.erase(a[i-k]);
            } else {
                value_count[a[i-k]]--;
            }
            // add i-th element
            if (value_count.find(a[i]) == value_count.end()) {
                value_count[a[i]] = 0;
            }
            value_count[a[i]] += 1;
            int min_v = (*value_count.begin()).first;
            int max_v = (*prev(value_count.end())).first;
            d = min(d, max_v - min_v);
        }
    }

    cout << d << endl;
    
    return 0;
}