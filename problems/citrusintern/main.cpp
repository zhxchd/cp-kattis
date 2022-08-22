#include <iostream>
#include <vector>
using namespace std;

int n, t1, t2;
vector<int> children[100001];
vector<int> parent[100001];
int weight[100001];
// long long cost[100001][2]; // 1: included, 0: not included
long long in[100001];     // current node is included, children is not-included and covered
// current node is not included and
// 1: current node is covered by parent, 0: current node is not covered (child must be included)
long long out[100001][2];

long long get_out_covered(int root);
long long get_out_uncovered(int root);

long long get_in(int root) {
    if (in[root] != -1) return in[root];
    in[root] = weight[root];
    for (auto child : children[root]) {
        in[root] += get_out_covered(child);
    }
    return in[root];
}

long long get_out_uncovered(int root) {
    // root is not covered and not included, so at least one of its children must be included
    // first for each child, use min of get_in(child) and get_out_uncovered(child)
    // if all children chooses out, we change the one that increases the cost by the least into in
    if (out[root][0] != -1) return out[root][0];
    // this function should never be called on a leaf
    if (children[root].size() == 0) {
        cout << "Never call get_out_uncovered on leaves!" << endl;
        exit(-1);
    }
    out[root][0] = 0ll;
    bool cover_root = false; // we need to include at least one of its children to cover root
    long long min_increase_to_include_child = -1;

    for (auto child : children[root]) {
        long long in_child_cost = get_in(child);
        long long out_child_cost;
        // if the child has no children, then we must include it
        if (children[child].size() == 0) {
            cover_root = true;
            out[root][0] += in_child_cost;
        } else {
            out_child_cost = get_out_uncovered(child);
            if (in_child_cost <= out_child_cost) {
                out[root][0] += in_child_cost;
                cover_root = true;
            } else {
                out[root][0] += out_child_cost;
                if (min_increase_to_include_child == -1 || in_child_cost - out_child_cost < min_increase_to_include_child) {
                    min_increase_to_include_child = in_child_cost - out_child_cost;
                }
            }
        }
    }

    if (!cover_root) {
        out[root][0] += min_increase_to_include_child;
    }

    return out[root][0];
}

long long get_out_covered(int root) {
    // root is covered and not included, so its children can be either included or not included
    if (out[root][1] != -1) return out[root][1];
    out[root][1] = 0ll;
    for (auto child : children[root]) {
        long long in_child_cost = get_in(child);
        // if the child has no children, then we must include it
        if (children[child].size() == 0) {
            out[root][1] += in_child_cost;
        } else {
            out[root][1] += min(in_child_cost, get_out_uncovered(child));
        }
    }
    return out[root][1];
}

int find_root() {
    for (int i = 0; i < n; i++) {
        if (parent[i].size() == 0) {
            return i;
        }
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    for (int i = 0; i < n; i++) {
        in[i] = -1;
        out[i][0] = -1;
        out[i][1] = -1;
        cin >> weight[i] >> t1;
        for (int j = 0; j < t1; ++j) {
            cin >> t2;
            children[i].push_back(t2);
            parent[t2].push_back(i);
        }
    }

    int root = find_root();

    // cout << root << endl;

    if (children[root].size() == 0) {
        cout << weight[root] << endl;
    } else {
        // cout << get_in(root) << endl;
        // cout << get_out_uncovered(root) << endl;
        cout << min(get_in(root), get_out_uncovered(root)) << endl;
    }
    

    return 0;
}