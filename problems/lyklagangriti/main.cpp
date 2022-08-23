/*
 * https://open.kattis.com/problems/lyklagangriti
 * Author: Xiaochen Zhu, xczhu@proton.me
 */

#include <iostream>
#include <list>
using namespace std;

list<char> s;
string str;
list<char>::iterator offset = s.begin();

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> str;

    for (char t : str) {
        switch (t)
        {
        case 'L':
            offset--;
            break;
        case 'R':
            offset++;
            break;
        case 'B':
            offset--;
            offset = s.erase(offset);
            break;
        default:
            offset = s.insert(offset, t);
            offset++;
            break;
        }
    }

    for (char c : s) {
        cout << c;
    }

    cout << endl;

    return 0;
}