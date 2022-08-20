#include <iostream>
#include <vector>
using namespace std;

// m is the number of corridors, n is the number of rooms
int m, n, u, v;
vector<int> c1, c2;

/*
Idea:
If a directed graph only contains edges from u to v where u is smaller than v,
then the graph is acyclic.
*/

void print(vector<int> c) {
    cout << c.size() << endl;
    for (auto i : c) {
        cout << i << endl;
    }
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        if (u > v) {
            c1.push_back(i+1);
        } else {
            c2.push_back(i+1);
        }
    }

    if (c1.size() > c2.size()) {
        print(c2);
    } else {
        print(c1);
    }

    return 0;
}