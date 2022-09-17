/*
 * https://open.kattis.com/problems/continuousmedian
 * Author: Xiaochen Zhu, xczhu@proton.me
 */

#include <bits/stdc++.h>
using namespace std;

int t, n;
bool odd;
long long x, sum;
// len(q1) == len(q2) or len(q2) + 1
priority_queue<long long,vector<long long>,less<long long> > q1; // smaller half, max_heap
priority_queue<long long,vector<long long>,greater<long long> > q2; // greater half, min_heap

void rebalance() {
    if (q1.size() >= q2.size() + 2) {
        // move the largest one in q1 to q2
        q2.push(q1.top());
        q1.pop();
    } else if (q1.size() < q2.size()) {
        // move the smallest one in q2 to q1
        q1.push(q2.top());
        q2.pop();
    }
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> t;
    while (t > 0) {
        t--;
        cin >> n;
        sum = 0ll;
        odd = false;
        q1 = {};
        q2 = {};
        for (int i = 0; i < n; i++) {
            cin >> x;
            if (i == 0) {
                q1.push(x);
            } else if (x <= q1.top()) {
                q1.push(x);
            } else {
                q2.push(x);
            }
            rebalance();
            odd = !odd;
            if (odd) {
                sum += q1.top();
            } else {
                sum += (q1.top() + q2.top())/2ll;
            }
        }
        cout << sum << endl;
    }

    return 0;
}