#include <iostream>
#include <vector>
using namespace std;

int n;

void output(vector<vector<int>> x) {
    for (auto l : x) {
        int first = 1;
        for (int i : l) {
            if (first) {
                cout << i;
                first = 0;
            } else {
                cout << ' ' << i;
            }
        }
        cout << endl;
    }
}

vector<vector<int>> solve(int x) {
    if (x == 1) {
        return {{1}};
    } else if (x == 2) {
        return {{1, 2}, {2, 1}};
    }
    vector<vector<int>> prev = solve(x - 1);
    vector<vector<int>> result;
    int i = x - 1, d;
    for (auto l : prev) {
        if (i == 0) {
            d = 1;
        } else {
            d = -1;
        }
        for (int j = 0; j < x; ++j) {
            vector<int> copy(l);
            copy.insert(copy.begin() + i, x);
            result.push_back(copy);
            i += d;
        }
        i -= d;
    }
    return result;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    output(solve(n));

    return 0;
}