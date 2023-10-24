# Buried Treasure

Buried treasure can be found using treasure maps. There are m different locations numbered from 1 to m. Each location contains either treasure or a trap.

Joey gives you n treasure maps. Each treasure map has two markers m1,m2. For i∈{1,2}, if mi<0, then the map is claiming that location |mi| contains a trap. If mi>0, then the map is claiming that location |mi| contains treasure.

We say that a treasure map is *reasonable* if at least one of the claims it makes is correct. For example, if a map claims that location 1 contains treasure and location 2 contains a trap, while in reality location 1 contains a trap and location 2 contains treasure, then the map is *not* reasonable.

Joey asserts that every treasure map that he has given you is reasonable. Can you check whether this is possible, i.e. whether there exists an assignment of locations 1 through m to either treasure or trap such that each map makes at least one correct claim?

## Input

The first line of input contains two space-separated integers n, the number of treasure maps you have, and m, the number of possible locations on the treasure maps (1≤n≤105,1≤m≤105).

The next n lines of input each contain 2 integers. For 1≤j≤n, the jth line contains two integers m1,m2 (−m≤m1,m2≤m, and m1,m2≠0) which represent the two locations marked by map j.

## Output

If it’s possible for every map to be reasonable, print YES. Otherwise, print NO.

## Sample Explanation

In Sample Input 1, there is no assignment of locations to either treasure or trap to make all maps reasonable. If for example we say that location 1 and 2 both contain treasure, then map 4 will not be reasonable, while if we say that location 1 contains a trap and location 2 contains treasure, then map 3 will not be reasonable. The other cases are similar.

In Sample Input 2, if location 1 contains a trap and location 2 contains treasure, then all 3 maps will be reasonable.

| Sample Input 1             | Sample Output 1 |
| -------------------------- | --------------- |
| `4 2 1 2 2 -1 1 -2 -1 -2 ` | `NO `           |

| Sample Input 2        | Sample Output 2 |
| --------------------- | --------------- |
| `3 2 1 2 2 -1 -1 -2 ` | `YES`           |

## Solution

[main.cpp](main.cpp)