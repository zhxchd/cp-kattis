#include <iostream>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;

int x1, x2, n1, n2, *t1, *t2, t, i, j, *d1, *d2;
float d;

void output() {
    if (abs(d) <= 4.4) {
       cout << "bumper tap at time " << round(t - (4.4 - abs(d))) << endl;
       exit(0);
    }
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> x1 >> x2;

    cin >> n1;
    t1 = new int[n1 + 1];
    t1[0] = 0;
    d1 = new int[n1 + 1];
    d1[0] = x1;

    for (i = 1; i < n1 + 1; i++) {
        cin >> t1[i];
        if (i % 2 == 0) {
            d1[i] = d1[i - 1] + t1[i] - t1[i - 1];
        } else {
            d1[i] = d1[i - 1];
        }
    }

    cin >> n2;
    t2 = new int[n2 + 1];
    t2[0] = 0;
    d2 = new int[n2 + 1];
    d2[0] = x2;

    for (i = 1; i < n2 + 1; i++) {
        cin >> t2[i];
        if (i % 2 == 0) {
            d2[i] = d2[i - 1] + t2[i] - t2[i - 1];
        } else {
            d2[i] = d2[i - 1];
        }
    }

    i = 1, j = 1;

    while (i < n1 + 1 && j < n2 + 1) {
        if (t1[i] < t2[j]) {
            t = t1[i];
            if (j % 2 == 0) {
                d = (t - t2[j - 1] + d2[j - 1]) - d1[i];
            } else {
                d = d2[j - 1] - d1[i];
            }
            output();
            ++i;
        } else if (t1[i] > t2[j]) {
            t = t2[j];
            if (i % 2 == 0) {
                d = d2[j] - (t - t1[i - 1] + d1[i - 1]);
            } else {
                d = d2[j] - d1[i - 1];
            }
            output();
            ++j;
        } else {
            t = t1[i];
            d = d2[j] - d1[i];
            output();
            ++i, ++j;
        }
    }

    while (i < n1 + 1) {
        t = t1[i];
        if (n2 % 2 == 1) {
            d = (d2[n2] + t - t2[n2]) - d1[i];
        } else {
            d = d2[n2] - d1[i];
        }
        output();
        ++i;
    }

    while (j < n2 + 1) {
        t = t2[j];
        if (n1 % 2 == 1) {
            d = d2[j] - (d1[n1] + t - t1[n1]);
        } else {
            d = d2[j] - d1[n1];
        }
        output();
        ++j;
    }

    if ((n1 + n2) % 2 == 1 && ((d > 0 && n1 % 2 == 1) || (d < 0 && n2 % 2 == 1))) {
        cout << "bumper tap at time " << round(t + abs(d) - 4.4) << endl;
        return 0;
    }

    cout << "safe and sound" << endl;
    return 0;
}