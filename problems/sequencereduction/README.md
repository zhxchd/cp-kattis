# Sequence Reduction

[Link](https://open.kattis.com/problems/sequencereduction)

We are given a sequence a1, …, an. We can manipulate this sequence using the operation reduce(i), which replaces elements ai and ai+1 with a single element max(ai,ai+1), resulting in a new shorter sequence. The cost of this operation is max(ai,ai+1).

After n−1 operations reduce(i), we obtain a sequence of length 1. Our task is to compute the cost of the optimal reducing scheme, i.e. the sequence of reduce operations with minimal cost leading to a sequence of length 1.

## Input

The first line contains n (1≤n≤1000000), the length of the sequence. The following n lines contain one integer ai, the elements of the sequence (0≤ai≤1000000000).

## Output

In the first and only line of the output print the minimal cost of reducing the sequence to a single element.

## Scoring

Your solution will be tested on a set of test groups, each worth a number of points. To get the points for a test group you need to solve all test cases in the test group.

| Group | Points | Constraints                |
| ----- | ------ | -------------------------- |
| 1     | 30     | N≤500                      |
| 2     | 20     | N≤20000                    |
| 3     | 50     | No additional constraints. |

## Solution

[main.cpp](main.cpp)