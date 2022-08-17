#include <iostream>
#include <vector>
using namespace std;

int t, l, w;
int map[1000][1000]; // max m[w-1][l-1]
int cost[1000][1000]; // cost: number of rounds for a mech to get to here
bool visited[1000][1000]; // visited by godzilla
vector<pair<int,int>> mechs;
pair<int,int> g;
int r = 0, num = 0;

bool in_range() {
    int x = g.first;
    int y = g.second;

    if (cost[x][y] != -1 && cost[x][y] <= r) {
        return true;
    }

    int i = 1;
    while (x+i < w && map[x+i][y] != 1) {
        if (cost[x+i][y] != -1 && cost[x+i][y] <= r) {
            return true;
        }
        i++;
    }
 
    i = 1;
    while (x-i >= 0 && map[x-i][y] != 1) {
        if (cost[x-i][y] != -1 && cost[x-i][y] <= r) {
            return true;
        }
        i++;
    }
    
    i = 1;
    while (y+i < l && map[x][y+i] != 1) {
        if (cost[x][y+i] != -1 && cost[x][y+i] <= r) {
            return true;
        }
        i++;
    }

    i = 1;
    while (y-i >= 0 && map[x][y-i] != 1) {
        if (cost[x][y-i] != -1 && cost[x][y-i] <= r) {
            return true; 
        }
        i++;
    }

    return false;
}

vector<pair<int,int>> neighbors(pair<int,int> v) {
    int x = v.first;
    int y = v.second;
    vector<pair<int,int>> neighbors;
    if (x+1 < w && !map[x+1][y]) {
        neighbors.push_back(make_pair(x+1,y));
    }
    if (y+1 < l && !map[x][y+1]) {
        neighbors.push_back(make_pair(x,y+1));
    }
    if (x-1 >= 0 && !map[x-1][y]) {
        neighbors.push_back(make_pair(x-1,y));
    }
    if (y-1 >= 0 && !map[x][y-1]) {
        neighbors.push_back(make_pair(x,y-1));
    }
    return neighbors;
}

void bfs(vector<pair<int,int>> sources) {
    vector<pair<int,int>> frontiers;
    if (sources.size() == 0) {
        return;
    }
    for (auto s : sources) {
        // only works if the source is accessible for tanks
        if (cost[s.first][s.second] != -1) {
            for (auto n : neighbors(s)) {
                if (cost[n.first][n.second] == -1) {
                    cost[n.first][n.second] = cost[s.first][s.second] + 1;
                    frontiers.push_back(n);
                } else if (cost[n.first][n.second] > cost[s.first][s.second] + 1) {
                    cost[n.first][n.second] = cost[s.first][s.second] + 1;
                    frontiers.push_back(n);
                }
            }
        }

    }
    bfs(frontiers);
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> t;

    char x;

    for (int i = 0; i < t; ++i) {
        r = 0;
        num = 0;
        mechs.clear();
        vector<pair<int,int>> curr;
        cin >> l >> w;
        // cout << "case " << i << ": l=" << l << ", w=" << w << endl; 
        // [0][0] is the north west corner
        // [w-1][l-1] is the south east corner
        // the second coordinate is for east/west
        for (int r = 0; r < w; ++r) {
            for (int c = 0; c < l; ++c) {
                cin >> x;
                cost[r][c] = -1;
                visited[r][c] = false;
                map[r][c] = 0;
                // cout << line[c] << endl;
                switch (x)
                {
                case '.': // nothing
                    break;
                case 'G': // gozilla location
                    g = make_pair(r, c);
                    visited[r][c] = true;
                    break;
                case 'R': // house, map is 1
                    map[r][c] = 1;
                    break;
                case 'M': // mech unit, cost initialized to 0
                    mechs.push_back(make_pair(r,c));
                    cost[r][c] = 0; 
                    break;
                }
            }
        }

        // for (int r = 0; r < w; ++r) {
        //     for (int c = 0; c < l; ++c) {
        //         cout << cost[r][c] << " ";
        //     }
        //     cout << endl;
        // }

        // bfs(mechs);

        // cout << "beginning:" << endl;
        // for (int r = 0; r < w; ++r) {
        //     for (int c = 0; c < l; ++c) {
        //         cout << cost[r][c] << " ";
        //     }
        //     cout << endl;
        // }
        // curr = mechs;
        bfs(mechs);
        do {
            bool destroy = false;
            pair<int,int> to_destroy;
            // North, East, South, West find house to destroy
            if (g.first >= 1 && map[g.first-1][g.second]) {
                // destroy house on the north
                to_destroy = make_pair(g.first-1, g.second);
                g = make_pair(g.first-1, g.second);
                destroy = true;
            } else if (g.second+1 < l && map[g.first][g.second+1]) {
                to_destroy = make_pair(g.first, g.second+1);
                g = make_pair(g.first, g.second+1);
                destroy = true;
            } else if (g.first+1 < w && map[g.first+1][g.second]) {
                to_destroy = make_pair(g.first+1, g.second);
                g = make_pair(g.first+1, g.second);
                destroy = true;
            } else if (g.second >= 1 && map[g.first][g.second-1]) {
                to_destroy = make_pair(g.first, g.second-1);
                g = make_pair(g.first, g.second-1);
                destroy = true;
            }
            
            if (destroy) {
                num++;
                visited[to_destroy.first][to_destroy.second] = true;
                map[to_destroy.first][to_destroy.second] = 0;
                // bfs(mechs);
                bfs(neighbors(to_destroy));
            } else {
                if (g.first >= 1 && !visited[g.first-1][g.second]) {
                    visited[g.first-1][g.second] = true;
                    g.first--;
                } else if (g.second + 1 < l && !visited[g.first][g.second+1]) {
                    visited[g.first][g.second+1] = true;
                    g.second++;
                } else if (g.first+1 < w && !visited[g.first+1][g.second]) {
                    visited[g.first+1][g.second] = true;
                    g.first++;
                } else if (g.second >= 1 && !visited[g.first][g.second-1]) {
                    visited[g.first][g.second-1] = true;
                    g.second--;
                }
            }
            r++;
            // cout << "After round " << r << endl;
            // for (int r = 0; r < w; ++r) {
            //     for (int c = 0; c < l; ++c) {
            //         cout << cost[r][c] << " ";
            //     }
            //     cout << endl;
            // }
            // cout << "Godzilla at " << g.first << ", " << g.second << endl;
        } while (!in_range());


        cout << num << endl;
    }

    return 0;
}