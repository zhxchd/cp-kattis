// reference: https://lcs.ios.ac.cn/~caisw/Code/DynWVC2.zip
// reference: Improving Local Search for Minimum Weight Vertex Cover by Dynamic Strategies, Cai et al, IJCAI-18

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstring>
#include <iostream>
#include <random>

using namespace std;

#define pop(stack) stack[--stack##_fill_pointer]
#define push(item, stack) stack[stack##_fill_pointer++] = item

typedef long long llong;
typedef unsigned int uint;
struct Edge {
    int v1;
    int v2;
};

int max_size_extra_remove;
chrono::steady_clock::time_point start;
llong max_steps;
llong step;
int try_step;
uint seed;
double cutoff_time;

int v_num;
int e_num;

Edge *edge;
int *edge_weight;

int *dscore;
llong *time_stamp;
int *valid_score;

int *v_weight;
int **v_edges;
int **v_adj;
int *v_degree;

int c_size;
int *v_in_c;
int *remove_cand;
int *index_in_remove_cand;
int remove_cand_size;
llong now_weight;

int best_c_size;
int *best_v_in_c;
double best_comp_time;
llong best_step;
llong best_weight;

int *uncov_stack;
int uncov_stack_fill_pointer;
int *index_in_uncov_stack;

int BuildInstance(string);
void ResetRemoveCand();
inline void Uncover(int);
inline void Cover(int);
void Add(int);
void Remove(int);
int UpdateTargetSize();
int ChooseRemoveV1();
int ChooseRemoveV2();
int ChooseAddV(int, int, int);
void UpdateBestSolution();
void RemoveRedundant();
void ConstructVC();
int CheckSolution();
void UpdateEdgeWeight();
void LocalSearch();
double TimeElapsed();

double TimeElapsed() {
    chrono::steady_clock::time_point finish = chrono::steady_clock::now();
    chrono::duration<double> duration = finish - start;
    return duration.count();
}

int BuildInstance() {
    string tmp;
    string sign;
    int v, e;
    int v1, v2;

    cin >> v_num >> e_num;

    edge = new Edge[e_num];
    edge_weight = new int[e_num];
    uncov_stack = new int[e_num];
    index_in_uncov_stack = new int[e_num];
    dscore = new int[v_num + 1];
    valid_score = new int[v_num + 1];
    time_stamp = new llong[v_num + 1];
    v_edges = new int *[v_num + 1];
    v_adj = new int *[v_num + 1];
    v_degree = new int[v_num + 1];
    v_weight = new int[v_num + 1];
    v_in_c = new int[v_num + 1];
    remove_cand = new int[v_num + 1];
    index_in_remove_cand = new int[v_num + 1];
    best_v_in_c = new int[v_num + 1];

    fill_n(v_degree, v_num + 1, 0);
    fill_n(v_in_c, v_num + 1, 0);
    fill_n(dscore, v_num + 1, 0);
    fill_n(time_stamp, v_num + 1, 0);
    fill_n(edge_weight, e_num, 1);
    fill_n(valid_score, v_num + 1, 1000000);

    for (v = 1; v < v_num + 1; v++) {
        cin >> v_weight[v];
    }

    for (e = 0; e < e_num; e++) {
        cin >> v1 >> v2;
        v1++;
        v2++;
        v_degree[v1]++;
        v_degree[v2]++;

        edge[e].v1 = v1;
        edge[e].v2 = v2;
    }
    v_adj[0] = 0;
    v_edges[0] = 0;
    for (v = 1; v < v_num + 1; v++) {
        v_adj[v] = new int[v_degree[v]];
        v_edges[v] = new int[v_degree[v]];
    }

    int *v_degree_tmp = new int[v_num + 1];
    fill_n(v_degree_tmp, v_num + 1, 0);

    for (e = 0; e < e_num; e++) {
        v1 = edge[e].v1;
        v2 = edge[e].v2;

        v_edges[v1][v_degree_tmp[v1]] = e;
        v_edges[v2][v_degree_tmp[v2]] = e;

        v_adj[v1][v_degree_tmp[v1]] = v2;
        v_adj[v2][v_degree_tmp[v2]] = v1;

        v_degree_tmp[v1]++;
        v_degree_tmp[v2]++;
    }
    delete[] v_degree_tmp;

    return 0;
}

void ResetRemoveCand() {
    int v, degree, i;
    int j = 0;

    for (v = 1; v < v_num + 1; v++) {
        if (v_in_c[v] == 1) { // if v is in C
            remove_cand[j] = v; // v can be removed
            index_in_remove_cand[v] = j; // v is j-th vertex in removed candidate set
            j++;

            valid_score[v] = -v_weight[v];
            degree = v_degree[v];
            for (i = 0; i < degree; i++) {
                if (v_in_c[v_adj[v][i]] == 0) {
                    valid_score[v] += v_weight[v_adj[v][i]];
                }
            }
        } else { // if v is not in C, it is not in remove candidate
            index_in_remove_cand[v] = 0;
        }
    }

    remove_cand_size = j;
}

inline void Uncover(int e) {
    index_in_uncov_stack[e] = uncov_stack_fill_pointer;
    push(e, uncov_stack);
}

inline void Cover(int e) {
    int index, last_uncov_edge;
    last_uncov_edge = pop(uncov_stack);
    index = index_in_uncov_stack[e];
    uncov_stack[index] = last_uncov_edge;
    index_in_uncov_stack[last_uncov_edge] = index;
}

void Add(int v) {
    int i, e, n;
    int edge_count = v_degree[v];

    v_in_c[v] = 1;
    c_size++;
    dscore[v] = -dscore[v];
    now_weight += v_weight[v];
    valid_score[v] = -v_weight[v];

    remove_cand[remove_cand_size] = v;
    index_in_remove_cand[v] = remove_cand_size++;

    for (i = 0; i < edge_count; i++) {
        e = v_edges[v][i];
        n = v_adj[v][i];

        if (v_in_c[n] == 0) {
            dscore[n] -= edge_weight[e];
            Cover(e);
            valid_score[v] += v_weight[n];
        } else {
            dscore[n] += edge_weight[e];
            valid_score[n] -= v_weight[v];
            if (valid_score[n] == -v_weight[n]) {
                Remove(n);
            }
        }
    }
}

void Remove(int v) {
    int i, e, n;
    int edge_count = v_degree[v];

    v_in_c[v] = 0;
    c_size--;
    dscore[v] = -dscore[v];
    valid_score[v] = 1000000;

    int last_remove_cand_v = remove_cand[--remove_cand_size];
    int index = index_in_remove_cand[v];
    remove_cand[index] = last_remove_cand_v;
    index_in_remove_cand[last_remove_cand_v] = index;
    index_in_remove_cand[v] = 0;

    now_weight -= v_weight[v];

    for (i = 0; i < edge_count; i++) {
        e = v_edges[v][i];
        n = v_adj[v][i];

        if (v_in_c[n] == 0) {
            dscore[n] += edge_weight[e];
            Uncover(e);
        } else {
            dscore[n] -= edge_weight[e];
            valid_score[n] += v_weight[v];
        }
    }
}

int UpdateTargetSize() {
    int v;
    int best_remove_v;
    double best_dscore;
    double dscore_v;

    best_remove_v = remove_cand[0];
    best_dscore = (double)(v_weight[best_remove_v]) / (double)abs(dscore[best_remove_v]);

    if (dscore[best_remove_v] != 0) {
        for (int i = 1; i < remove_cand_size; i++) {
            v = remove_cand[i];
            if (dscore[v] == 0) break;
            dscore_v = (double)(v_weight[v]) / (double)abs(dscore[v]);
            if (dscore_v > best_dscore) {
                best_dscore = dscore_v;
                best_remove_v = v;
            }
        }
    }
    Remove(best_remove_v);
    return best_remove_v;
}

int ChooseRemoveV1() {
    int i, v;
    int remove_v = remove_cand[0];
    int improvement_remove = valid_score[remove_v], improvement_v;
    for (i = 1; i < remove_cand_size; i++) {
        v = remove_cand[i];
        improvement_v = valid_score[v];
        if (improvement_v > improvement_remove) {
            continue;
        }
        if (improvement_v < improvement_remove) {
            remove_v = v;
            improvement_remove = improvement_v;
        } else if (time_stamp[v] < time_stamp[remove_v]) {
            remove_v = v;
            improvement_remove = improvement_v;
        }
    }
    return remove_v;
}

int ChooseRemoveV2() {
    int i, v;
    double dscore_v, dscore_remove_v;
    int remove_v = remove_cand[rand() % remove_cand_size];
    int to_try = 50;

    for (i = 1; i < to_try; i++) {
        v = remove_cand[rand() % remove_cand_size];
        dscore_v = (double)v_weight[v] / (double)abs(dscore[v]);
        dscore_remove_v = (double)v_weight[remove_v] / (double)abs(dscore[remove_v]);
        if (dscore_v < dscore_remove_v) {
            continue;
        }
        if (dscore_v > dscore_remove_v) {
            remove_v = v;
        } else if (time_stamp[v] < time_stamp[remove_v]) {
            remove_v = v;
        }
    }
    return remove_v;
}

int ChooseAddFromV() {
    int v;
    int add_v = 0;
    double improvemnt = 0.0;
    double dscore_v;

    for (v = 1; v < v_num + 1; v++) {
        if (v_in_c[v] == 1) {
            continue;
        }
        dscore_v = (double)dscore[v] / (double)(v_weight[v]);
        if (dscore_v > improvemnt) {
            improvemnt = dscore_v;
            add_v = v;
        } else if (dscore_v == improvemnt) {
            if (time_stamp[v] < time_stamp[add_v]) {
                add_v = v;
            }
        }
    }
    return add_v;
}

int ChooseAddV(int update_v, vector<int> all_remove_v) {
    int i, v;
    int add_v = 0;
    double improvemnt = 0.0;
    double dscore_v;

    int tmp_degree = v_degree[update_v];
    int *adjp = v_adj[update_v];

    for (i = 0; i < tmp_degree; i++) {
        v = adjp[i];
        if (v_in_c[v] == 1) {
            continue;
        }
        dscore_v = (double)dscore[v] / (double)(v_weight[v]);
        if (dscore_v > improvemnt) {
            improvemnt = dscore_v;
            add_v = v;
        } else if (dscore_v == improvemnt) {
            if (time_stamp[v] < time_stamp[add_v]) {
                add_v = v;
            }
        }
    }

    for (int remove_v : all_remove_v) {
        if (remove_v != 0) {
            tmp_degree = v_degree[remove_v];
            adjp = v_adj[remove_v];
            for (i = 0; i < tmp_degree; i++) {
                v = adjp[i];
                if (v_in_c[v] == 1) {
                    continue;
                }
                dscore_v = (double)dscore[v] / (double)(v_weight[v]);
                if (dscore_v > improvemnt) {
                    improvemnt = dscore_v;
                    add_v = v;
                } else if (dscore_v == improvemnt) {
                    if (time_stamp[v] < time_stamp[add_v]) {
                        add_v = v;
                    }
                }
            }
        }
    }

    return add_v;
}

void UpdateBestSolution() {
    int v;

    if (now_weight < best_weight) {
        for (v = 1; v < v_num + 1; v++) {
            best_v_in_c[v] = v_in_c[v];
        }
        best_weight = now_weight;
        best_c_size = c_size;
        best_comp_time = TimeElapsed();
        best_step = step;
    }
}

void RemoveRedundant() {
    int v;
    for (int i = 0; i < remove_cand_size; i++) {
        v = remove_cand[i];
        if (v_in_c[v] == 1 && dscore[v] == 0) {
            Remove(v);
            i--;
        }
    }
}

void ConstructVC() {
    int e;
    int v1, v2;
    double v1dd, v2dd;

    uncov_stack_fill_pointer = 0;
    c_size = 0;
    best_weight = (int)(~0U >> 1);
    now_weight = 0;

    int e_index[e_num];

    for (int i = 0; i < e_num; i++) {
        e_index[i] = i;
    }

    int t = 50;

    while (t >= 0) {
        t--;
        random_shuffle(&e_index[0], &e_index[e_num]);
        v_in_c = new int[v_num+1];
        fill_n(v_in_c, v_num+1, 0);
        now_weight = 0;
        c_size = 0;
        for (int i = 0; i < e_num; i++) {
            int v1 = edge[e_index[i]].v1;
            int v2 = edge[e_index[i]].v2;
            if (!v_in_c[v1] && !v_in_c[v2]) {
                v1dd = (double)v_degree[v1] / (double)v_weight[v1];
                v2dd = (double)v_degree[v2] / (double)v_weight[v2];
                if (v1dd > v2dd) {
                    v_in_c[v1] = 1;
                    now_weight += v_weight[v1];
                    c_size += 1;
                } else {
                    v_in_c[v2] = 1;
                    now_weight += v_weight[v2];
                    c_size += 1;
                }
            }
        }

        if (now_weight < best_weight) {
            best_weight = now_weight;
            best_c_size = c_size;
            memcpy(best_v_in_c, v_in_c, sizeof(int) * (v_num+1));
        }
    }

    memcpy(v_in_c, best_v_in_c, sizeof(int) * (v_num+1));
    now_weight = best_weight;
    c_size = best_c_size;

    for (e = 0; e < e_num; e++) {
        v1 = edge[e].v1;
        v2 = edge[e].v2;

        if (v_in_c[v1] == 1 && v_in_c[v2] == 0) {
            dscore[v1] -= edge_weight[e];
        } else if (v_in_c[v2] == 1 && v_in_c[v1] == 0) {
            dscore[v2] -= edge_weight[e];
        }
    }

    ResetRemoveCand();
    for (int v = 1; v < v_num + 1; v++) {
        if (v_in_c[v] == 1 && dscore[v] == 0) {
            Remove(v);
        }
    }
    UpdateBestSolution();
}

int CheckSolution() {
    int e, v;

    for (e = 0; e < e_num; ++e) {
        if (best_v_in_c[edge[e].v1] != 1 && best_v_in_c[edge[e].v2] != 1) {
            cout << ", uncovered edge " << e;
            return 0;
        }
    }
    return 1;
}

void UpdateEdgeWeight() {
    int i, e;

    for (i = 0; i < uncov_stack_fill_pointer; i++) {
        e = uncov_stack[i];
        edge_weight[e] += 1;
        dscore[edge[e].v1] += 1;
        dscore[edge[e].v2] += 1;
    }

}

void LocalSearch() {
    int add_v, update_v = 0;
    vector<int> all_remove_v;
    int noimprovement = 0, dyn_count = 0, temp_weight;
    step = 1;
    try_step = 25;
    int remove_degree = 0;

    while (true) {
        temp_weight = now_weight;
        UpdateBestSolution();
        update_v = UpdateTargetSize();
        time_stamp[update_v] = step;
        if (step % try_step == 0) {
            if (TimeElapsed() >= cutoff_time) {
                return;
            }
        }
        if (noimprovement < 5) {
            int remove_v = ChooseRemoveV1();
            Remove(remove_v);
            time_stamp[remove_v] = step;
            all_remove_v.push_back(remove_v);
        } else {
            if (noimprovement == 5) {
                dyn_count = 2;
            }
            if (dyn_count == 1) {
                noimprovement = 0;
            }
            int remove_v = ChooseRemoveV2();
            Remove(remove_v);
            time_stamp[remove_v] = step;
            all_remove_v.push_back(remove_v);
            dyn_count--;
        }
        remove_degree = v_degree[update_v] + v_degree[all_remove_v[0]];
        while (all_remove_v.size() < max_size_extra_remove && remove_degree < (1+all_remove_v.size()) * e_num / v_num) {
            int remove_v = ChooseRemoveV2();
            Remove(remove_v);
            time_stamp[remove_v] = step;

            all_remove_v.push_back(remove_v);
            remove_degree += v_degree[remove_v];
        }

        while (uncov_stack_fill_pointer > 0) {
            add_v = ChooseAddV(update_v, all_remove_v);
            Add(add_v);
            UpdateEdgeWeight();
            time_stamp[add_v] = step;
        }
        step++;
        all_remove_v.clear();
        if (now_weight >= temp_weight) {
            noimprovement += 1;
        }
        remove_degree = 0;
    }
}

int main(int argc, char *argv[]) {
    uint seed = 0;
    cutoff_time = 1.75;

    max_size_extra_remove = 4; // 1 if only allow one more vertex to remove

    BuildInstance();

    srand(seed);

    start = chrono::steady_clock::now();

    ConstructVC();
    LocalSearch();

    cout << best_weight << endl;
    bool first = true;
    for (int i = 1; i < v_num + 1; i++) {
        if (best_v_in_c[i]) {
            if (first) {
                cout << i - 1;
                first = false;
            } else {
                cout << " " << i - 1;
            }
        }
    }
    cout << endl;

    return 0;
}
