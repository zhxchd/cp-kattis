#include <iostream>
#include <unordered_map>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;

int len[26] = {1,3,3,5,5,5,7,7,7,7,7,9,9,9,9,9,9,9,9,11,11,11,11,11,11,11};

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string str;
    unordered_map<char, int> cc; // char_count
    int length = 0;

    getline(cin, str);

    for (auto it = str.begin(); it != str.end(); ++it) {
        if (isalpha(*it)) {
            char c = tolower(*it);
            cc[c]++;
            length++;
        }
    }

    vector<int> ccv; //char_count_vector

    for(auto kv : cc) {
        ccv.push_back(kv.second);  
    }

    sort(ccv.begin(), ccv.end(), greater<int>());

    int res = 3*(length - 1);
    int i = 0;

    for (auto v : ccv) {
        res += v * len[i];
        i++;
    }

    cout << res << endl;

    return 0;
}