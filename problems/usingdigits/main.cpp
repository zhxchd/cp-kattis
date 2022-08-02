// Slow but passes

#include <iostream>
#include <map>
#include <queue>
#include <tuple>
using namespace std;

int w, h;
int g[100][100];
char temp;

vector<tuple<int,int,string>> get_neighbor(tuple<int,int,string> u) {
    int x = get<0>(u);
    int y = get<1>(u);
    string cost = get<2>(u);
    vector<tuple<int,int,string>> n;

    // usuall neighbors
    if (x+1 < w) {
        n.push_back(make_tuple(x+1,y,cost));
    }
    if (y+1 < h) {
        n.push_back(make_tuple(x,y+1,cost));
    }

    if (cost.length() >= 1) {
        int f = cost[0] - '0';
        string c1 = cost.substr(1);
        if (x+f+1 < w) {
            n.push_back(make_tuple(x+f+1,y,c1));
        }
    
        if (y+f+1 < h) {
            n.push_back(make_tuple(x,y+f+1,c1));
        }

    }

    return n;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string c;

    cin >> w >> h >> c;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cin >> temp;
            g[j][h-1-i] = temp - '0';
        }
    }

    // following is a SSSP
    map<tuple<int, int, string>, int> dist; // [x, y, c] -> dist
    // set<tuple<int,int,int>> visited;
    priority_queue<pair<int, tuple<int,int,string>>, vector<pair<int, tuple<int,int,string>>>, greater<pair<int, tuple<int,int,string>>>> pq;
    pq.push(make_pair(g[0][0], make_tuple(0,0,c)));
    dist[make_tuple(0,0,c)] = g[0][0];

    while (!pq.empty()) {
        auto u = pq.top();
        // visited.insert(u.second);
        pq.pop();
        if (u.first != dist[u.second]) {
            continue;
        }
        if (get<0>(u.second) == w-1 && get<1>(u.second) == h-1) {
            cout << u.first << endl;
            return 0;
        }
        for (auto n : get_neighbor(u.second)) {
            int alt = u.first + g[get<0>(n)][get<1>(n)];
            if (dist.find(n) == dist.end() || dist[n] > alt) {
                dist[n] = alt;
                pq.push(make_pair(dist[n], n));
            }
        }
    }

    return 0;
}