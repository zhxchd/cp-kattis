#include <iostream>
#include <map>
#include <vector>
using namespace std;

int n, id1, id2;
string str1, str2;
map<string, int> m;
vector<int> id, sz;

int root(int i) {
    while (i != id[i]) {
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
}

int unite(int p, int q) {
    int i = root(p);
    int j = root(q);
    if (i == j) {
        return sz[i];
    } else if (sz[i] < sz[j]) {
        id[i] = j;
        sz[j] += sz[i];
        return sz[j];
    } else {
        id[j] = i;
        sz[i] += sz[j];
        return sz[i];
    }
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> str1 >> str2;

        if (m.find(str1) == m.end()) {
            id1 = m.size();
            m[str1] = id1;
            id.push_back(id1);
            sz.push_back(1);
        } else {
            id1 = m[str1];
        }
        if (m.find(str2) == m.end()) {
            id2 = m.size();
            m[str2] = id2;
            id.push_back(id2);
            sz.push_back(1);
        } else {
            id2 = m[str2];
        }

        cout << unite(id1, id2) << endl;
    }

    return 0;
}