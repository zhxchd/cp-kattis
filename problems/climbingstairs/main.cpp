#include <iostream>
#include <cmath>
using namespace std;

int n, r, l;

int next_even (int x) {
    if (x % 2 == 0) return x;
    else return x + 1;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> r >> l;
    if (r > l) {
        if (n <= r) {
            cout << r + r << endl;
            return 0;
        } else {
            cout << r + next_even(n - r) + r << endl;
            return 0;
        }
    } else {
        if (n <= l + (l - r)) {
            cout << l + l << endl;
            return 0;
        } else {
            cout << l + l + next_even(n - l - l + r) << endl;
            return 0;
        }
    }
    return 0;
}