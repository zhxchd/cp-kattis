# Continuous Median

In Statistics, the median of an array A of N integers is a value which divides array A into two equal parts: the higher half and the lower half.

In the case when N is odd, the median is clearly defined: the middle value of the sorted version of array A. In the case when N is even, the median is the average of the two middle values, **rounded down** so that we always have an integer median.

In this problem, your task is to compute median values as integers are added into array A one by one. Since this is an incremental process, we call these “continuous medians”. To simplify this problem, you just need to output the sum of the medians of A at the end.

## Input

The first line of input contains an integer T, denoting the number of test cases (1≤T≤100). Each test case consists of two lines and the first line contains just one integer N (1≤N≤105). This is followed by N integers of array A in the next line. Each integer in A is non-negative and is not more than 109.

*Note: For all input, there will be at most 400000 integers.*

## Output

For each test case, output *the sum* of the continuous medians of A in one line.

## Solution

[main.cpp](./main.cpp)