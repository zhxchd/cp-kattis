#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// This is (literally) a 2-SAT problem, we can solve this in linear time by finding strongly connected components.

int n, m, t1, t2; // n is the number of constraints, m is the length of array
vector<int> adj[200005], adj_t[200005]; // for node i (0 <= i <= m-1), 2*i is the var and 2*i+1 is the negation node
stack<int> topo_order;
bool visited1[200005] = {0};
bool visited2[200005] = {0};
int scc[200005];

int get_negate(int x) {
    if (x < 0) {
        // then x is the negate of -x-1, so the negate of x is 2(-x-1)
        return 2*(-x-1);
    } else {
        // x is x-1, so the negate of x-1 is 2(x-1)+1
        return 2*(x-1)+1;
    }
}

int get_node(int x) {
    if (x < 0) {
        // x is the negate of -x-1
        return 2*(-x-1)+1;
    } else {
        // x is x-1
        return 2*(x-1);
    }
}

void dfs(int start) {
    visited1[start] = true;
    for (auto neighbor : adj[start]) {
        if (!visited1[neighbor]) {
            dfs(neighbor);
        }
    }
    topo_order.push(start);
}

void dfs_util(int start, int cid) {
    visited2[start] = true;
    scc[start] = cid;
    for (auto neighbor : adj_t[start]) {
        if (!visited2[neighbor]) {
            dfs_util(neighbor, cid);
        }
    }
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> t1 >> t2;
        // negate of t1 leads to t2
        adj[get_negate(t1)].push_back(get_node(t2));
        adj_t[get_node(t2)].push_back(get_negate(t1));
        // negate of t2 leads to t1
        adj[get_negate(t2)].push_back(get_node(t1));
        adj_t[get_node(t1)].push_back(get_negate(t2));
    }

    for (int i = 0; i < 2*m; i++) {
        if (!visited1[i]) {
            dfs(i);
        }
    }

    int cid = 1;

    while (!topo_order.empty()) {
        int start = topo_order.top();
        topo_order.pop();

        if (!visited2[start]) {
            dfs_util(start, cid);
        }

        cid++;
    }

    for (int i = 0; i < m; i++) {
        if (scc[2*i] == scc[2*i+1]) {
            cout << "NO" << endl;
            return 0;
        }
    }

    cout << "YES" << endl;
    return 0;
}