# Counting Chocolate

[Open Kattis](https://open.kattis.com/problems/countingchocolate)

Cady’s Chocolate Company just opened down the street! Cady’s chocolate is world famous, and her recipe is top secret. But the company is more renowned for the fact that they sell the chocolate in random quantities. Each box of chocolate may contain anywhere from 1 to 100 pieces.

Bob’s nephews, John and Sam, love Cady’s Chocolate, but Bob has a dilemma. John will get jealous of Sam if he gets more pieces of chocolate, and vice versa. Bob knows how many pieces of chocolate are in each box.

Write a program to help him determine if it is possible to split the boxes between John and Sam such that both get the same number of pieces of chocolate, and such that all boxes of chocolate are used.

## Input

The input consists of a single test case. The first line contains an integer n (1≤n≤1000), the number of boxes of chocolate Bob bought. The next line contains n integers ai representing the number of pieces of chocolate in the ith box (1≤ai≤100).

## Output

If it is possible for Bob to split the boxes such that John and Sam get the same number of pieces of chocolate, output `YES`. Otherwise, output `NO`.

| Sample Input 1     | Sample Output 1 |
| ------------------ | --------------- |
| `6 1 4 3 12 13 1 ` | `YES `          |

| Sample Input 2    | Sample Output 2 |
| ----------------- | --------------- |
| `6 1 1 1 3 4 11 ` | `NO `           |

## Solution

[main.py](main.py)