#include <iostream>
using namespace std;

int n, k, r;
int *arr, *least, *num;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> k >> r;

    arr = new int[n], least = new int[k], num = new int[k];

    for (int i = 0; i < k; i++) {
        least[i] = 0;
        num[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    int min_num = 0;
    for (int i = 0; i < r; ++i) {
        int b, q;
        cin >> b >> q;
        least[b] = q;
        min_num += q;
    }

    // inclusive, sliding window from start to end
    int start = 0, len, min_len;

    for (len = 1; len <= n; len++) {
        num[arr[len - 1]]++;
        if (num[arr[len - 1]] == least[arr[len - 1]]) r--;
        if (r == 0) break;
    }

    if (r != 0) {
        cout << "impossible" << endl;
        return 0;
    }

    min_len = len;

    if (min_len == min_num) {
        cout << min_len << endl;
        return 0;
    }

    if (n == 1) {
        cout << min_len << endl;
        return 0;
    }

    len--;
    for (start = 1; start + len - 1 < n; start++, len--) {
        int removed = arr[start - 1];
        num[removed]--;
        if (num[removed] < least[removed]) {
            if (start + len >= n) break;
            for (len = len + 1; start + len - 1 < n; len++) {
                num[arr[start + len - 1]]++;
                if (removed == arr[start + len - 1]) break;
            }
        }
        if (len < min_len) {
            min_len = len;
        }
        if (min_len == min_num) {
            cout << min_len << endl;
            return 0;
        }
    }

    cout << min_len << endl;

    return 0;
}