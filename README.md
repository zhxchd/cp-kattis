- [Competitive Programming Practice](#competitive-programming-practice)
  * [Problem list](#problem-list)
  * [Problem Sources](#problem-sources)
    + [CS3233 AY2021S2 Assignments](#cs3233-ay2021s2-assignments)

# Competitive Programming Practice

This repository is used for me to practice some algorithm and data structure problems on Kattis. I am most proficient in coding with `Java`, but I'm also practising to code with `C++`. Therefore, both programming languages have appeared in this repository. I believe that appropriate comments along the code are sufficient to aid readers to understand the logic, so only the code and relevant testing files will be contained, instead of seperate files explaining my solutions.

Currently, I am following the problem lists of [NUS CS3233 Competitive Programming AY2021S2](https://nus.kattis.com/courses/CS3233/CS3233_S2_AY2021). Sources for problems in this repository are listed [here](#problem-sources).

I'll probably make this repository public when I reach 100 problems.

## Problem list

Newly-solved problems are listed on the top of the table.

| | Problem | Difficulty | Status [Tries] | Solution | Comments |
|-|-|-|-|-|-|
| 31| [Lucky numbers](./problems/luckynumber) | 4.9 | Solved [2] | [C++](./problems/luckynumber/main.cpp) | Brute force when `n` is small, 0 when `n` greater than 25 |
| 30| [The Big Mac Question](./problems/thebigmacquestion) | 6.7 | Working [2], WA | | Looks like a construction problem...|
| 29| [The Sound of Silence](./problems/sound) | 5.0 | Solved [2] | [C++](./problems/sound/main.cpp) | Sliding window that records counts of all internal values, I use `std::map` for simplicity, it's perhaps an overkill and my solution is slow |
| 28| [Music Collection](./problems/musiccollection) | 4.3 | Solved [1] | [C++](./problems/musiccollection/main.cpp) | Just brute force everything |
| 27| [Convoy](./problems/convoy) | 5.7 | Solved [2] | [C++](./problems/convoy/main.cpp) | It is easy to verify whether a given time limit works or not, then binary search the minimum; use `long long` |
| 26| [Bridges and Tunnels](./problems/bridgesandtunnels) | 3.0 | Solved [1] | [C++](./problems/bridgesandtunnels/main.cpp) | A slightly modified version of UFDS |
| 25| [Znanstvenik](./problems/znanstvenik) | 3.9 | Solved [1] | [C++](./problems/znanstvenik/main.cpp) | Complete search, rotate for easier string construction |
| 24| [Parallel Analysis](./problems/parallelanalysis) | 3.7 | Solved [1] | [C++](./problems/parallelanalysis/main.cpp) | Store last written time for each address in a `map`, using `unordered_map` will accelerate the program by a lot |
| 23| [Add 'Em Up!](./problems/addemup) | 4.8 | Solved [1] | [C++](problems/addemup/main.cpp) | Maintain a `map` from values to indices |
| 22| [Bumper-To-Bumper Traffic](./problems/traffic) | 3.9 | Solved [6] | [C++](./problems/traffic/main.cpp) | Just brute force each timestamp |
| 21| [Crashing Robots](./problems/crashingrobots) | 4.2 | Solved [5] | [C++](problems/crashingrobots/main.cpp) | Using BSTs to store all robots in each row and column so that we can easily find the blocking robot, I use `std::set` |
| 20| [Cat Coat Colors](./problems/catcoat) | 3.0 | Haven't Tried [0] | | Looks really tedious, try later |
| 19| [Matchsticks](./problems/matchsticks) | 4.3 | Solved [4] | [C++](problems/matchsticks/main.cpp) | Largest numbers are trivial, brute force small instances for smallest numbers |
| 18| [Canvas Line](./problems/canvasline) | 4.1 | Solved [9] | [C++](problems/canvasline/main.cpp) | Greedily select the rightmost peg if possible, be careful with corner cases |
| 17| [Cake](./problems/cake) | 4.3 | Solved [3] | [C++](problems/cake/main.cpp) | Trivial, process the rectangular line by line |
| 16| [Falcon Dive](./problems/falcondive) | 2.8 | Solved [1] | [C++](problems/falcondive/main.cpp) | Compare the anchor of the two silhouettes |
| 15 | [Andrew the Ant](./problems/andrewant) | 4.8 | Working [6], TLE |  | Probably I try to insert duplicate timestamps to the time queue (which is a `set`) |
| 14| [The Ups and Downs of Investing](./problems/upsanddownsofinvesting) | 3.6 | Solved [1] | [C++](./problems/upsanddownsofinvesting/main.cpp) | Trivial counting |
| 13| [Physical Music](./problems/physicalmusic) | 5.9 | Solved [4] | [C++](./problems/physicalmusic/main.cpp) | If anyone else doing worse than me in single does better than me in downloading: I have CDs, sorted output |
| 12| [Score!](./problems/score) | 3.4 | Solved [1] | [C++](./problems/score/main.cpp) | Trivial |
| 11| [Climbing Stairs](./problems/climbingstairs) | 4.1 | Solved [1] | [C++](./problems/climbingstairs/main.cpp)| Trivial |
| 10| [Martian DNA](./problems/martiandna) | 1.3 - 2.6 | Solved [4] | [C++](./problems/martiandna/main.cpp) | Sliding window and count occurences |
| 9 | [Paths](./problems/paths) | 1.3 - 3.4 | Solved [3] | [Java](./problems/paths/Main.java) | Intuitive dfs is too slow, DP with bitmask (bitmask can avoid duplicate vertices) |
| 8 | [Ninety-nine](./problems/ninetynine) | 1.3 - 2.7 | Solved [4] | [Java](./problems/ninetynine/Main.java)| Mod 3, randomized |
| 7 | [Bridges](./problems/bryr) | 1.4 - 2.6 | Solved [8] | [Java](./problems/bryr/Main.java)| SSSP, memory sensitive |
| 6 | [Birthday Memorization](./problems/fodelsedagsmemorisering) | 1.3 - 1.7 | Solved [5] | [Java](./problems/fodelsedagsmemorisering/Main.java)| Map, sorted output |
| 5 | [Arrangement](./problems/upprodun) | 1.3 - 1.8 | Solved [1] | [Java](./problems/upprodun/Main.java)| Trivial integer division |
| 4 | [Homework](./problems/heimavinna) | 1.1 - 1.4 | Solved [1] | [Java](./problems/heimavinna/Main.java)| Char-by-char process |
| 3 | [Graduation](./problems/skolavslutningen) | 1.2 - 1.9 | Solved [2] | [Java](./probelems/skolavslutningen/Main.java)| Union find |
| 2 | [Keystrokes](./problems/lyklagangriti) | 1.5 - 2.5 | Solved [1] | [Java](./problems/lyklagangriti/Main.java)| Char-by-char process |
| 1 | [Reverse](./problems/ofugsnuid/) | 1.2 - 1.4 | Solved [4] | [Java](./problems/ofugsnuid/Main.java) | Trivial reverse, use fast Java i/o |

## Problem Sources

### CS3233 AY2021S2 Assignments

- [Kattis Set 00 - Competitive Programming Preview](https://nus.kattis.com/sessions/zha3me)
- [Kattis Set 01 - Ad Hoc](https://nus.kattis.com/sessions/ksm5ix)
- [Kattis Set 02 - Data Structures and Libraries](https://nus.kattis.com/sessions/d9ah9a)
- [Kattis Set 03 - Complete Search](https://nus.kattis.com/sessions/jxb6gj)
- [Kattis Set 04 - Dynamic Programming](https://nus.kattis.com/sessions/ekxm7g)
- [Kattis Set 05 - Greedy and Network Flow](https://nus.kattis.com/sessions/mv958o)
- [Kattis Set 06 - CS2040/C/S++ Basic Graph Review](https://nus.kattis.com/sessions/ekmrqt)
- [Midterm Team Contest](https://nus.kattis.com/sessions/ippxni)
- [Kattis Set 07 - Graph Matching and Easier Mathematics](https://nus.kattis.com/sessions/krkia7)
- [Kattis Set 08 - NP-hard Problems + Misc 1](https://nus.kattis.com/sessions/nha2wi)
- [Kattis Set 09 - Harder Mathematics](https://nus.kattis.com/sessions/he8byc)
- [Kattis Set 10 - String Processing and BSTA+Other](https://nus.kattis.com/sessions/ct35ji)
- [Kattis Set 11 - Computational Geometry + Misc 2](https://nus.kattis.com/sessions/sgjgur)
- [Kattis Set 12 - Mix and Match](https://nus.kattis.com/sessions/sghyqk)
- [Final Team Contest](https://nus.kattis.com/sessions/c8r7xp)
