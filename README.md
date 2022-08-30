# Competitive Programming Practice

This repository is used for me to practice some algorithm and data structure problems on [Kattis](https://open.kattis.com/). Most of the code is in `C++`. I believe that appropriate comments along the code are sufficient to aid readers to understand the logic, so only the code and relevant testing files will be contained, instead of seperate files explaining my solutions.

I'll probably make this repository public when I reach 100 problems.

## Problem list

Newly-AC problems are listed on the top of the table.

| | Problem | Difficulty | Status [Tries] | Solution | Comments |
|-|-|-|-|-|-|
| 55| [Font](./problems/font/) | 4.1 | AC [2] | [C++](./problems/font/main.cpp) | I simply brute force using bitmasking and got AC. Kind of slow. |
| 54| [Tree Shopping](./problems/treeshopping/) | 3.0 | AC [1] | [C++](./problems/treeshopping/main.cpp) | Maintain max and min of slicing window. I use `map`, this is not the most efficient (nlogk, while O(n) is possible). |
| 53| [Annoyed Coworkers](./problems/annoyedcoworkers/) | 3.3 | AC [1] | [C++](./problems/annoyedcoworkers/main.cpp) | Greedily choose the coworker who will be least annoyed after being asked for help. Use a min heap for that. |
| 52| [Social Advertising](./problems/socialadvertising) | 4.6 | AC [1] | [C++](./problems/socialadvertising/main.cpp) | Since n is small, brute force and verify all the 2^n choices, find the one with the fewest vertices. AC but kind of slow.| 
| 51| [1's For All](./problems/1sforall/) | 7.1 | AC [5] | [Python](./problems/1sforall/main.py) | DP, enumerate all ways to form n (via +, * or c). Python string operations are slow, don't use them to split numbers. |
| 50| [Perfect Skyline](./problems/perfectskyline/) | 4.3 | AC [1] | [C++](./problems/perfectskyline/main.cpp) | N and S are small, first enumerate all ways to build, then search a consistent solution with backtracking. |
| 49| [Jailbreak](./problems/jailbreak/) | 4.8 | AC [1] | [C++](./problems/jailbreak/main.cpp) | SSSP from outside, prisoner 1 and presoner 2, find the location l where outside->l + p1->l + p2->l is minimized. |
| 48| [Buried Treasure](./problems/buriedtreasure2/) | 5.3 | AC [1] | [C++](./problems/buriedtreasure2/main.cpp) | Literally 2-SAT. Poly time solvable by finding strongly connected components. |
| 47| [The Cirtrus Intern](./problems/citrusintern/) | 3.5 | AC [4] | [C++](./problems/citrusintern/main.cpp) | DP. Each node has three states: included, not included but covered by parent, or not included and not covered by parent.|
| 46| [Exits in Excess](./problems/exitsinexcess/) | 5.6 | AC [1] | [C++](./problems/exitsinexcess/main.cpp) | If a directed graph only contains edges from u to v where u is smaller than v, then the graph is acyclic. |
| 45| [Simple Arithmetic](./problems/simplearithmetic/) | 1.2 - 4.8 | AC (100) [3] | [Java](./problems/simplearithmetic/Main.java) | Use `BigDecimal` in `Java`. I tried `long double` in `C++` and only got 75/100. |
| 44| [Sequence Reduction](./problems/sequencereduction/) | 4.5 - 5.8 | AC (100) [4] | [C++](./problems/sequencereduction/main.cpp) | Reduce sequences to the left and right of maximum first, then finally reduce max. |
| 43| [Counting Chocolate](./problems/countingchocolate/) | 4.4 | AC [2] | [Python](./problems/countingchocolate/main.py) | Simple recursion, but with memorization. |
| 42| [Godzilla](./problems/godzilla/) | 5.4 | AC [12] | [C++](./problems/godzilla/main.cpp) |APSP from all mechs through BFS. | 
| 41| [Red/Blue Spanning Tree](./problems/redbluetree/) | 5.6 | AC [9] | [C++](./problems/redbluetree/main.cpp) | Find STs with at min/max number of blue edges. |
| 40| [Using Digits](./problems/usingdigits/) | 4.9 | AC [4] | [C++](./problems/usingdigits/main.cpp) | SSSP considering the code, note that cannot read code into an int since it's too long. My solution is slow but passes. |
| 39| [Predicting GME](./problems/predictinggme/) | 6.2 | AC [7] | [C++](./problems/predictinggme/main.cpp) | Use DP to enumerate all cases. |
| 38| [ReMorse](./problems/remorse/) |  2.7 | AC [1] | [C++](./problems/remorse/main.cpp) | Greedily use shortest code for most frequent letters. |
| 37| [Word Ladder](./problems/wordladder2) | 6.9 | WA [21] | | |
| 36| [Bell Ringing](./problems/bells) | 4.6 | AC [2] | [C++](./problems/bells/main.cpp) | Recursively generate `n` from `n - 1` case|
| 35| [Peculiar primes](./problems/primes) | 6.0 |AC [3]|[C++](./problems/primes/main.cpp)| Just do power set of all powers, stop at each iteration when greater than `Y`; don't bother to tell if `int` overflows, just use `long long` |
| 34| [Draughts](./problems/draughts) | 3.3 | AC [1] | [C++](./problems/draughts/main.cpp) | Trivial, I just did dfs on all white pieces to try all options |
| 33| [Grade Curving](./problems/gradecurving) | 4.5 | AC [1] | [C++](./problems/gradecurving/main.cpp) | Trivial, just try `k` one after one |
| 32| [Lucky numbers](./problems/luckynumber) | 4.9 | AC [2] | [C++](./problems/luckynumber/main.cpp) | Brute force when `n` is small, 0 when `n` greater than 25 |
| 31| [Chocolates](./problems/chocolates) | 5.0 | AC [1] | [C++](./problems/chocolates/main.cpp) | Complete search all combinitions (as the search space is small), a polygon needs to be connected and its complement must be open |
| 30| [The Big Mac Question](./problems/thebigmacquestion) | 6.7 | WA [2] | | Looks like a construction problem...|
| 29| [The Sound of Silence](./problems/sound) | 5.0 | AC [2] | [C++](./problems/sound/main.cpp) | Sliding window that records counts of all internal values, I use `std::map` for simplicity, it's perhaps an overkill and my solution is slow |
| 28| [Music Collection](./problems/musiccollection) | 4.3 | AC [1] | [C++](./problems/musiccollection/main.cpp) | Just brute force everything |
| 27| [Convoy](./problems/convoy) | 5.7 | AC [2] | [C++](./problems/convoy/main.cpp) | It is easy to verify whether a given time limit works or not, then binary search the minimum; use `int` |
| 26| [Bridges and Tunnels](./problems/bridgesandtunnels) | 3.0 | AC [1] | [C++](./problems/bridgesandtunnels/main.cpp) | A slightly modified version of UFDS |
| 25| [Znanstvenik](./problems/znanstvenik) | 3.9 | AC [1] | [C++](./problems/znanstvenik/main.cpp) | Complete search, rotate for easier string construction |
| 24| [Parallel Analysis](./problems/parallelanalysis) | 3.7 | AC [1] | [C++](./problems/parallelanalysis/main.cpp) | Store last written time for each address in a `map`, using `unordered_map` will accelerate the program by a lot |
| 23| [Add 'Em Up!](./problems/addemup) | 4.8 | AC [1] | [C++](problems/addemup/main.cpp) | Maintain a `map` from values to indices |
| 22| [Bumper-To-Bumper Traffic](./problems/traffic) | 3.9 | AC [6] | [C++](./problems/traffic/main.cpp) | Just brute force each timestamp |
| 21| [Crashing Robots](./problems/crashingrobots) | 4.2 | AC [5] | [C++](problems/crashingrobots/main.cpp) | Using BSTs to store all robots in each row and column so that we can easily find the blocking robot, I use `std::set` |
| 20| [Cat Coat Colors](./problems/catcoat) | 3.0 | [0] | | Looks really tedious, try later |
| 19| [Matchsticks](./problems/matchsticks) | 4.3 | AC [4] | [C++](problems/matchsticks/main.cpp) | Largest numbers are trivial, brute force small instances for smallest numbers |
| 18| [Canvas Line](./problems/canvasline) | 4.1 | AC [9] | [C++](problems/canvasline/main.cpp) | Greedily select the rightmost peg if possible, be careful with corner cases |
| 17| [Cake](./problems/cake) | 4.3 | AC [3] | [C++](problems/cake/main.cpp) | Trivial, process the rectangular line by line |
| 16| [Falcon Dive](./problems/falcondive) | 2.8 | AC [1] | [C++](problems/falcondive/main.cpp) | Compare the anchor of the two silhouettes |
| 15 | [Andrew the Ant](./problems/andrewant) | 4.8 | AC [10] | [C++](problems/andrewant/main.cpp)  | Two important invariants: the number of ants going left at first is the number of ants falling from left; if an ant starts at `p` going left, then after `p` seconds, an ant will fall on the left |
| 14| [The Ups and Downs of Investing](./problems/upsanddownsofinvesting) | 3.6 | AC [1] | [C++](./problems/upsanddownsofinvesting/main.cpp) | Trivial counting |
| 13| [Physical Music](./problems/physicalmusic) | 5.9 | AC [4] | [C++](./problems/physicalmusic/main.cpp) | If anyone else doing worse than me in single does better than me in downloading: I have CDs, sorted output |
| 12| [Score!](./problems/score) | 3.4 | AC [1] | [C++](./problems/score/main.cpp) | Trivial |
| 11| [Climbing Stairs](./problems/climbingstairs) | 4.1 | AC [1] | [C++](./problems/climbingstairs/main.cpp)| Trivial |
| 10| [Martian DNA](./problems/martiandna) | 1.3 - 2.6 | AC (100) [4] | [C++](./problems/martiandna/main.cpp) | Sliding window and count occurences |
| 9 | [Paths](./problems/paths) | 1.3 - 3.4 | AC (100) [3] | [Java](./problems/paths/Main.java) | Intuitive dfs is too slow, DP with bitmask (bitmask can avoid duplicate vertices) |
| 8 | [Ninety-nine](./problems/ninetynine) | 1.3 - 2.7 | AC (100) [4] | [Java](./problems/ninetynine/Main.java)| Mod 3, randomized |
| 7 | [Bridges](./problems/bryr) | 1.4 - 2.6 | AC (100) [8] | [Java](./problems/bryr/Main.java)| SSSP, memory sensitive |
| 6 | [Birthday Memorization](./problems/fodelsedagsmemorisering) | 1.3 - 1.7 | AC (100) [5] | [Java](./problems/fodelsedagsmemorisering/Main.java)| Map, sorted output |
| 5 | [Arrangement](./problems/upprodun) | 1.3 - 1.8 | AC (100) [1] | [Java](./problems/upprodun/Main.java)| Trivial integer division |
| 4 | [Homework](./problems/heimavinna) | 1.1 - 1.4 | AC (100) [1] | [Java](./problems/heimavinna/Main.java)| Char-by-char process |
| 3 | [Graduation](./problems/skolavslutningen) | 1.2 - 1.9 | AC (100) [2] | [Java](./probelems/skolavslutningen/Main.java)| Union find |
| 2 | [Keystrokes](./problems/lyklagangriti) | 1.1 - 5.9 | AC (100) [6] | [C++](./problems/lyklagangriti/main.cpp)| Char-by-char process, Java `StringBuilder` is too slow for this, `C++` `vector` also too slow, need to use a linked list for all the iterator and add/remove operations. |
| 1 | [Reverse](./problems/ofugsnuid/) | 1.2 - 1.4 | AC (100) [4] | [Java](./problems/ofugsnuid/Main.java) | Trivial reverse, use fast Java i/o |
