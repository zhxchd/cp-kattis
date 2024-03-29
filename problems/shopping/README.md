# Shopping

[Open Kattis](https://open.kattis.com/problems/shopping), difficulty score 6.6.

You have just moved into a new apartment and have a long list of items you need to buy. Unfortunately, to buy this many items requires going to many different stores. You would like to minimize the amount of driving necessary to buy all the items you need.

Your city is organized as a set of intersections connected by roads. Your house and every store is located at some intersection. Your task is to find the shortest route that begins at your house, visits all the stores that you need to shop at, and returns to your house.

## Input

The first line of input contains two integers N and M, the number of intersections and roads in the city, respectively. Each of these integers is between 1 and 100000, inclusive. The intersections are numbered from 0 to N−1. Your house is at the intersection numbered 0. M lines follow, each containing three integers X, Y, and D, indicating that the intersections X and Y (X≠Y) are connected by a bidirectional road of length D (1≤D≤106). The following line contains a single integer S, the number of stores you need to visit, which is between 1 and 10, inclusive. The subsequent S lines each contain one integer indicating the intersection at which each store is located. No two stores are located at the same intersection, and no store is located at intersection 0. It is possible to reach all of the stores from your house.

## Output

Output a line containing a single integer, the length of the shortest possible shopping trip from your house, visiting all the stores, and returning to your house.

| Sample Input 1                                     | Sample Output 1 |
| -------------------------------------------------- | --------------- |
| `4 6 0 1 1 1 2 1 2 3 1 3 0 1 0 2 5 1 3 5 3 1 2 3 ` | `4`             |

## Solution
[main.cpp](main.cpp)