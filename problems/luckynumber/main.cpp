#include <iostream>
#include <vector>
using namespace std;

int n;
vector<vector<int>> *l;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    if (n > 25) {
        cout << 0 << endl;
        return 0;
    }

    l = new vector<vector<int>>[n + 1];

    for (int i = 1; i < 10; ++i) {
        l[1].push_back(vector<int>(n + 1, i));
    }

    for (int i = 2; i < n + 1; ++i) {
        for (auto it : l[i - 1]) {
            for (int j = 0; j < 10; ++j) {
                if ((it[i] * 10 + j) % i == 0) {
                    vector<int> temp = it;
                    for (int k = 1; k < n + 1; ++k) {
                        temp[k] = (it[k] * 10 + j) % k;
                    }
                    l[i].push_back(temp);
                }
            }
        }
    }

    cout << l[n].size() << endl;

    return 0;
}