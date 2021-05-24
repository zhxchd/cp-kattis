#include <iostream>
#include <map>
#include <vector>
using namespace std;

int t, n;
string *str;
map<string, vector<int>> m;
vector<int> *v;

bool check(string subs, int i) {
    for (int j = 0; j < n; ++j) {
        if (j != i && str[j].find(subs) != -1) {
            return false;
        }
    }
    return true;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> t;

    for (int i = 0; i < t; ++i) {
        cout << "Case #" << i + 1 << ":" << endl;
        cin >> n;
        str = new string[n];
        v = new vector<int>[n];
        getline(cin, str[0]);
        for (int j = 0; j < n; ++j) {
            m = {};
            getline(cin, str[j]);
            for (int k = 0; k < str[j].length(); ++k) {
                char& c = str[j][k];
                c = toupper(c);
                m[str[j].substr(k)].push_back(k);
            }
            for (auto it = m.begin(); it != m.end(); ++it) {
                v[j].insert(v[j].end(), it->second.begin(), it->second.end());
            }
        }
        if (n == 1) {
            cout << "\"\"" << endl;
        } else {
            for (int j = 0; j < n; ++j) {
                bool found = false;
                for (int l = 1; !found && l <= str[j].length(); ++l) {
                    for (int it : v[j]) {
                        // cout << "Test: " << str[j].substr(it, l) << endl;
                        if (it + l - 1 < str[j].length() && check(str[j].substr(it, l), j)) {
                            cout << "\"" <<  str[j].substr(it, l) << "\"" << endl;
                            found = true;
                            break;
                        }
                    }
                }
                if (!found) {
                    cout << ":(" << endl;
                }
            }
        }
        
    }



    return 0;
}