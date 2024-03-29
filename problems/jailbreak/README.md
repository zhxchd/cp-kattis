# Jailbreak

John is on a mission to get two people out of prison. This particular prison is a one-story building. He has managed to get hold of a detailed floor plan, indicating all the walls and doors. He also knows the locations of the two people he needs to set free. The prison guards are not the problem – he has planned a diversion that should leave the building practically void.

The doors are his main concern. All doors are normally opened remotely from a control room, but John can open them by other means. Once he has managed to open a door, it remains open. However, opening a door takes time, which he does not have much of, since his diversion will only work for so long. He therefore wants to minimize the number of doors he needs to open. Can you help him plan the optimal route to get to the two prisoners?

## Input

On the first line one positive number: the number of test cases, at most 100. After that per test case:

- one line with two space-separated integers h and w (2≤h,w≤100): the width and height of the map.
- h lines with w characters describing the prison building:
  - ‘`.`’ is an empty space.
  - ‘`*`’ is an impenetrable wall.
  - ‘`#`’ is a door.
  - ‘`$`’ is one of the two people to be liberated.

John can freely move around the outside of the building. There are exactly two people on the map. For each person, a path from the outside to that person is guaranteed to exist.

## Output

Per test case:

- one line with a single integer: the minimum number of doors John needs to open in order to get to both prisoners.

| Sample Input 1                                               | Sample Output 1 |
| ------------------------------------------------------------ | --------------- |
| `3 5 9 ****#**** *..#.#..* ****.**** *$#.#.#$* ********* 5 11 *#********* *$*...*...* *$*.*.*.*.* *...*...*.* *********.* 9 9 *#**#**#* *#**#**#* *#**#**#* *#**.**#* *#*#.#*#* *$##*##$* *#*****#* *.#.#.#.* ********* ` | `4 0 9`         |

## Solution

[main.cpp](main.cpp)