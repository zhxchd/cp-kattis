# Airports

https://open.kattis.com/problems/airports

An airline company offers flights out of n airports. The flight time between any given pair of airports is known, but may differ on direction due to things like wind or geography. Upon landing at a given airport, a plane must be inspected before it can be flown again. This inspection time is dependent on the airport at which the inspection is taking place.

Given a set of m flights that the airline company must realize, determine the minimum number of planes that the company needs to purchase. The airline may add unscheduled flights to move the airplanes around if that would reduce the total number of planes needed.

## Input

Each input will consist of a single test case. Note that your program may be run multiple times on different inputs. The first line of input contains two integers n and m (2≤n,m≤500). The next line contains n space-separated nonnegative integers less than or equal to 106, where the ith integer denotes the amount of time (in minutes) that an inspection takes at airport i.

Each of the next n lines contains n space-separated nonnegative integers less than or equal to 106. On the ith line, The jth integer indicates the amount of time it takes to fly from airport i to airport j. It takes no time to fly from an airport to itself. Note that the flight time from airport i to j is not necessarily the same as the flight time from airport j to i.

The next m lines contain three space-separated integers, s, f, and t, (1≤s,f≤n, s≠f, 1≤t≤106) indicating that a flight must start at airport s, end at airport f, and fly out from airport s at exactly time t heading directly to airport f.

## Output

Output a single positive integer indicating the minimum number of planes the airline company must purchase in order to realize the m requested flights.

| Sample Input 1                 | Sample Output 1 |
| ------------------------------ | --------------- |
| `2 2 1 1 0 1 1 0 1 2 1 2 1 1 ` | `2 `            |

| Sample Input 2                 | Sample Output 2 |
| ------------------------------ | --------------- |
| `2 2 1 1 0 1 1 0 1 2 1 2 1 3 ` | `1 `            |

| Sample Input 3                                               | Sample Output 3 |
| ------------------------------------------------------------ | --------------- |
| `5 5 72 54 71 94 23 0 443 912 226 714 18 0 776 347 810 707 60 0 48 923 933 373 881 0 329 39 511 151 364 0 4 2 174 2 1 583 4 3 151 1 4 841 4 3 993 ` | `3`             |

## Solution

[main.cpp](main.cpp)