# Programming Team Selection

[Link](https://open.kattis.com/problems/programmingteamselection)

You are a coach for a competitive learning program. It’s time for the regional competition and you have to group your students into teams. Every team needs exactly three members and every student needs to be on a team.

While choosing your teams, you must keep in mind whether particular students work well together. During the weeks and weeks of practice leading up to the competition, you have carefully observed your students working in pairs. You have made notes of which pairs work well together and which ones don’t. You are only willing to make a team of students a, b and c if a and b are known to work well together, b and c are known to work well together, and a and c are known to work well together.

## Input

Input contains up to 10 test cases. Each test case starts with an integer 1≤m≤105, the number of pairs that work well together. This is followed by m lines, each containing space-separated names of two different students that work well together. A student name is a sequence of up to 20 upper- and lower-case letters (a–z). Each student has a unique name and every student name occurs in at least one pair. There are at most 15 students in a test case, and the sequence of test cases ends with value of zero for m.

## Output

For every test case, output “possible” if it’s possible to group the students into teams the way you want to. If not, output “impossible”.

| Sample Input 1                                               | Sample Output 1       |
| ------------------------------------------------------------ | --------------------- |
| `8 Greg Doug Greg Chiam Chiam Doug Doug Danny Jonathan Chiam David Danny Danny Jonathan Jonathan David 8 David Doug Doug Greg Chiam Doug David Greg Jonathan David Chiam David Danny Jonathan David Danny 0 ` | `possible impossible` |

## Solution

[main.cpp](main.cpp)