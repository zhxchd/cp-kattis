# Simple Arithmetic

[Link](https://open.kattis.com/problems/simplearithmetic)

You are given three integers a,b,c (1≤a,b,c≤109). Compute a⋅b/c, with an *absolute* precision of 10−6.

## Input

The first and only line of input contains the three integers a,b,c separated by a single space.

## Output

Output a single floating point number. It must differ from a⋅b/c by at most 10−6 in absolute value, i.e., it should obey |x−a⋅b/c|≤10−6.

## Constraints

Your solution will be tested on a set of test groups, each worth a number of points. Each test group contains a set of test cases. To get the points for a test group you need to solve all test cases in the test group. Your final score will be the maximum score of a single submission.

| Group | Points | Limits        |
| ----- | ------ | ------------- |
| 1     | 25     | 1≤a,b,c≤10    |
| 2     | 25     | 1≤a,b,c≤10000 |
| 3     | 25     | 1≤a,b≤109,c=1 |
| 4     | 25     | 1≤a,b,c≤109   |

| Sample Input 1 | Sample Output 1         |
| -------------- | ----------------------- |
| `3 5 7 `       | `2.142857142857142857 ` |

| Sample Input 2 | Sample Output 2 |
| -------------- | --------------- |
| `9999 9876 1 ` | `98750124 `     |

| Sample Input 3           | Sample Output 3                          |
| ------------------------ | ---------------------------------------- |
| `123456789 987654321 1 ` | `121932631112635269.000000000000000000 ` |

| Sample Input 4           | Sample Output 4                         |
| ------------------------ | --------------------------------------- |
| `123456789 987654321 7 ` | `17418947301805038.428571428571428571 ` |

## Solution

[Main.java](Main.java)