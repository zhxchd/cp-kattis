#include <iostream>
// #include <vector>

using namespace std;
// vector<long> arr;
int n;

// Idea: for max numbers, it will be reduced the last,
// hence, the optimal cost is the optimal cost of reducing the sequence to its left,
// adding the optimal cost of reducing the sequence to its right, adding itself twice
// long reduce(int left, int right) {
//     // only one element
//     if (left == right) {
//         return 0l;
//     } 
//     int max_id = left;
//     for (int i = left; i <= right; i++) {
//         if (arr[i] > arr[max_id]) {
//             max_id = i;
//         }
//     }
//     if (max_id == left) {
//         return reduce(left+1, right) + arr[left];
//     } else if (max_id == right) {
//         return reduce(left, right-1) + arr[right];
//     } else {
//         return reduce(left, max_id - 1) + reduce(max_id+1, right) + arr[max_id] * 2;
//     }
// }

// long long reduce() {
//     long long res = 0;
//     for (int i = 0; i < n; ++i) {
//         if (i != n - 1) {
//             res += max(arr[i], arr[i+1]);
//         }
//     }
//     return res;
// }

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    long long res = 0;
    long prev_val, val;

    cin >> prev_val;

    for (int i = 1; i < n; ++i) {
        long val;
        cin >> val;
        res += max(val, prev_val);
        prev_val = val;
    }

    cout << res << endl;

    return 0;
}