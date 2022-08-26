/*
 * https://open.kattis.com/problems/annoyedcoworkers
 * Author: Xiaochen Zhu, xczhu@proton.me
 */

#include <iostream>
#include <queue>
using namespace std;

int h, c;
long long a[100001], d[100001];
long long max_a = 0ll;
// pq contains the costs of the all people if they get asked for help one more time
priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>> > pq;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> h >> c;

    for (int i = 0; i < c; i++) {
        cin >> a[i] >> d[i];
        pq.push(make_pair(a[i] + d[i], i));
        if (a[i] > max_a) {
            max_a = a[i];
        }
    }

    while (h > 0) {
        long long cost = pq.top().first;
        int i = pq.top().second;
        pq.pop();
        // sum += min_cost.first;

        pq.push(make_pair(cost + d[i], i));
        if (cost > max_a) {
            max_a = cost;
        }
        h--;
    }

    cout << max_a << endl;

    return 0;
}