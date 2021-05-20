#include <iostream>
#include <map>
#include <set>
using namespace std;

int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
map<char, int> dir_map = {{'N', 0}, {'E', 1}, {'S', 2}, {'W', 3}};
map<char, int> rot_map = {{'L', -1}, {'R', 1}};

set<int> *rows, *cols;
int k, a, b, n, m, *x, *y, *d, s, e, nx, ny, f;
int bot, r;
char act, temp;

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> k;

    for (int i = 0; i < k; i++) {
        bool c = false;
        cin >> a >> b >> n >> m;

        x = new int[n];
        y = new int[n];
        d = new int[n];
        cols = new set<int>[a];
        rows = new set<int>[b];
        int rect[a][b];

        for (int j = 0; j < n; j++) {
            cin >> x[j] >> y[j] >> temp;
            x[j]--, y[j]--;
            d[j] = dir_map[temp];
            cols[x[j]].insert(y[j]);
            rows[y[j]].insert(x[j]);
            rect[x[j]][y[j]] = j;
        }

        for (int j = 0; j < m; j++) {
            cin >> bot >> act >> r;
            if (!c) {
                bot--;
                if (act == 'F') {
                    nx = x[bot] + dir[d[bot]][0] * r;
                    ny = y[bot] + dir[d[bot]][1] * r;
                    if (d[bot] == 0 || d[bot] == 2) {
                        if (ny > y[bot]) {
                            auto fp = cols[nx].upper_bound(y[bot]);
                            f = *fp;
                            if (fp != cols[nx].end() && f <= ny) c = true;
                        } else {
                            auto fp = cols[nx].find(y[bot]);
                            if (fp != cols[nx].begin()) {
                                f = *prev(fp);
                                if (f >= ny) {
                                    c = true;
                                }
                            }
                        }
                        if (c) {
                            cout << "Robot " << bot + 1 << " crashes into robot " << rect[nx][f] + 1 << endl;
                        } else if (ny < 0 || ny >= b) {
                            c = true;
                            cout << "Robot " << bot + 1 << " crashes into the wall" << endl;
                        } else {
                            cols[nx].erase(y[bot]);
                            rows[y[bot]].erase(nx);
                            y[bot] = ny;
                            cols[nx].insert(ny);
                            rows[ny].insert(nx);
                            rect[nx][ny] = bot;
                        }
                    } else {
                        if (nx > x[bot]) {
                            auto fp = rows[ny].upper_bound(x[bot]);
                            f = *fp;
                            if (fp != rows[ny].end() && f <= nx) c = true;
                        } else {
                            auto fp = rows[ny].find(x[bot]);
                            if (fp != rows[ny].begin()) {
                                f = *prev(fp);
                                if (f >= nx) {
                                    c = true;
                                }
                            }
                        }
                        if (c) {
                            cout << "Robot " << bot + 1 << " crashes into robot " << rect[f][ny] + 1 << endl;
                        } else if (nx < 0 || nx >= a) {
                            c = true;
                            cout << "Robot " << bot + 1 << " crashes into the wall" << endl;
                        } else {
                            rows[ny].erase(x[bot]);
                            cols[x[bot]].erase(ny);
                            x[bot] = nx;
                            rows[ny].insert(nx);
                            cols[nx].insert(ny);
                            rect[nx][ny] = bot;
                        }
                    }
                } else {
                    d[bot] = ((d[bot] + r *  rot_map[act]) % 4 + 4) % 4;
                }
            }
        }

        if (!c) {
            cout << "OK" << endl;
        }
    }

    return 0;
}