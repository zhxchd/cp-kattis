
#include <iostream>
#include <vector>
#include <deque>
// #include <unordered_set>
using namespace std;

int n, l, d[1000][2];
string dic[1000];
vector<int> neighbors[1000];
vector<pair<pair<int, int>, string>> insertions;
// unordered_set<string> dic_set;

// auto sort_path = 
//     [](const pair<int, string>& a, const pair<int, string>& b) {
//         if (b.first == -1) {
//             return false;
//         } else if (a.first == -1) {
//             return true;
//         } else if (a.first != b.first) {
//             return b.first < a.first;
//         } else {
//             return b.second < a.second;
//         }
//     };

pair<int, string> distance(int a, int b) {
    string x = dic[a], y = dic[b], m = dic[a];
    int to_return = 0, done = 0;
    for (int i = 0; i < l; ++i) {
        if (x[i] != y[i]) {
            to_return++;
            if (to_return >= 3) {
                return make_pair(3, "");
            }
            if (to_return == 1) {
                if (x[i] > y[i]) {
                    m[i] = y[i];
                    done = 1;
                }
            } else {
                if (!done) {
                    m[i] = y[i];
                }
            }
        }
    }
    if (to_return == 1) {
        return make_pair(1, "");
    } else {
        return make_pair(2, m);
    }
}

void bfs(int s) {
    bool visited[1000] = {0};
    int h = 0;
    deque<int> q = {};
    visited[s] = 1;
    q.push_back(s);
    while (!q.empty()) {
        int v = q.front();
        d[v][s] = h;
        h++;
        q.pop_front();
        for (auto i : neighbors[v]) {
            if (!visited[i]) {
                visited[i] = 1;
                q.push_back(i);
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> dic[i];
        // dic_set.insert(dic[i]);
        d[i][0] = -1;
        d[i][1] = -1;
    }
    l = dic[0].length();

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            auto d = distance(i, j);
            if (d.first == 1) {
                neighbors[i].push_back(j);
                neighbors[j].push_back(i);
            } else if (d.first == 2) {
                insertions.push_back(make_pair(make_pair(i, j), d.second));
            }
        }
    }

    bfs(0), bfs(1);

    pair<int, string> result = make_pair(d[0][1], "0");
    for (auto it : insertions) {
        int i = it.first.first, j = it.first.second;
        int f = -1;
        if (d[i][0] != -1 && d[j][1] != -1) {
            f = d[i][0] + d[j][1] + 2;
        }
        if (d[j][0] != -1 && d[i][1] != -1) {
            if (f == -1) {
                f = d[j][0] + d[i][1] + 2;
            } else {
                f = min(f, d[j][0] + d[i][1] + 2);
            }
        }
        if (f != -1) {
            if (result.first == -1) {
                result = make_pair(f, it.second);
            } else if (f < result.first) {
                result = make_pair(f, it.second);
            } else if (f == result.first) {
                result.second = min(result.second, it.second);
            }
        }
    }

    cout << result.second << endl;
    cout << result.first << endl;

    return 0;
}
