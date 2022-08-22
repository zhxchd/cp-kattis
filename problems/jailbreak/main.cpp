/*
 * https://open.kattis.com/problems/jailbreak
 * Author: Xiaochen Zhu, xczhu@proton.me
 * 
 * Idea:
 * First pad the map with '.' borders so that (0,0) is connected to all borders with no cost.
 * Then, we use SSSP to find the distances from (0,0), p1 and p2 to all locations (door weight 1).
 * Then for all locations (i,j), we find the min of dist(0,0)->(i,j) + dist(p1)->(i,j) + dist(p2)->(i,j)
 * Note that if (i,j) is a door, we need to subtract 2 since we triple count the same door
 */

#include <iostream>
#include <vector>
#include <climits>
#include <deque>
using namespace std;

int t;

vector<pair<int,int>> get_neighbors(pair<int,int> curr, int h, int w, char map[][105]) {
    vector<pair<int,int>> neighbors;
    int x = curr.first;
    int y = curr.second;
    if (x > 0 && map[x-1][y] != '*') {
        neighbors.push_back(make_pair(x-1, y));
    }
    if (y > 0 && map[x][y-1] != '*') {
        neighbors.push_back(make_pair(x, y-1));
    }
    if (x < h+1 && map[x+1][y] != '*') {
        neighbors.push_back(make_pair(x+1, y));
    }
    if (y < w+1 && map[x][y+1] != '*') {
        neighbors.push_back(make_pair(x, y+1));
    }
    return neighbors;
}

void sssp(pair<int,int> start, int h, int w, int dist[][105], char map[][105]) {
    for (int i = 0; i < h+2; i++) {
        for (int j = 0; j < w+2; j++) {
            dist[i][j] = INT_MAX;
        }
    }
    deque<pair<int,int>> frontier;
    dist[start.first][start.second] = 0;
    frontier.push_back(start);

    while(!frontier.empty()) {
        auto curr = frontier.front();
        frontier.pop_front();

        for (auto n : get_neighbors(curr, h, w, map)) {
            if (dist[n.first][n.second] > dist[curr.first][curr.second] + (map[n.first][n.second] == '#')) {
                dist[n.first][n.second] = dist[curr.first][curr.second] + (map[n.first][n.second] == '#');
                if (map[n.first][n.second] != '#') {
                    frontier.push_front(n);
                } else {
                    frontier.push_back(n);
                }
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> t;

    while (t > 0) {
        t--;
        int h, w; // h lines of m characters -> h+2 lines of m+2 characters actually
        char map[105][105]; // four borders are padded '.' chars, max map[h+1][w+1]
        int dist1[105][105]; // distance from map[0][0] to everywhere
        int dist2[105][105]; // distance from first prisoner to everywhere
        int dist3[105][105]; // distance from second prisoner to everywhere
        vector<pair<int,int>> p; // two prisoners

        cin >> h >> w;
        // map[0][0]...map[0][w+1] -> '.'
        for (int i = 0; i < w+2; i++) {
            map[0][i] = '.';
            map[h+1][i] = '.';
        }
        for (int i = 0; i < h; i++) {
            map[i+1][0] = '.';
            map[i+1][w+1] = '.';
            for (int j = 0; j < w; j++) {
                cin >> map[i+1][j+1];
                if (map[i+1][j+1] == '$') {
                    p.push_back(make_pair(i+1,j+1));
                }
            }
        }
        sssp(make_pair(0,0), h, w, dist1, map);
        sssp(p[0], h, w, dist2, map);
        sssp(p[1], h, w, dist3, map);

        int min_dist = INT_MAX;

        for (int i = 1; i < h+1; i++) {
            for (int j = 1; j < w+1; j++) {
                if (map[i][j] == '#') {
                    min_dist = min(min_dist, dist1[i][j] + dist2[i][j] + dist3[i][j] - 2);
                } else {
                    min_dist = min(min_dist, dist1[i][j] + dist2[i][j] + dist3[i][j]);
                }
            }
        }

        cout << min_dist << endl;

    }

    return 0;
}