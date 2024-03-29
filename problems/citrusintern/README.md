# Problem B The Citrus Intern

[Link](https://open.kattis.com/problems/citrusintern)

The summer is closing in and you have set your eyes on a summer internship with your favourite fruit confederacy, Citrus. What you *really* want is to take over the entire organisation on your way to world fruit domination, but getting an internship is a nice first step.

You know that there is a single person in Citrus deciding who gets the internship, but unfortunately, you don’t know who that person is. Thus, you decide to infiltrate the entire organization by bribing some subset of members, so that you are guaranteed to get the internship. You have already gathered the organization map, as well as estimated the amount of money each member would require to aid your candidacy. The only thing remaining is deciding who to recruit.

When you bribe a Citrus member, that member will be able to manipulate both their superior as well as their direct subordinates to support your candidacy. In this way it is not necessary to bribe everyone in Citrus, as long as everyone in the organisation is either bribed or manipulated by someone who is.

In addition, you want to take an extra precaution. You do not want two different people to both be bribed if they ever talk to each other; then they might realize what your final plan is, and start blackmailing you. Citrus protocol dictates that nobody should ever discuss anything with anyone who is not their immediate boss or subordinate, so you figure your scheme will be sufficiently safe as long as you avoid bribing the immediate superior of someone else you bribe.

To initiate the infiltration you are to write a program that given the organizational map of Citrus as well as the cost of recruiting each of its members, outputs the minimum amount of money required to complete the task. Because Citrus is so well-organized, every member has exactly one immediate supervisor, except the one and only *most sour excellence*, who has only subordinates.

## Input

The first line consists of an integer 1≤N≤100000, the number of members in Citrus. Then follows N lines, each describing a member, beginning with member 0 and ending with member N−1. The line describing member i begins with two integers 0≤Ci≤1000000 and 0≤Ui<N, the cost of recruiting member i and the number of immediate subordinates of member i respectively. Then follows Ui numbers on the same line, the identification numbers of the subordinates. Note that all identification numbers are between 0 and N−1.

## Output

The minimum cost of infiltrating the entire organization while adhering to the restrictions above. Observe that the answer might very well be larger than 232.

| Sample Input 1                                       | Sample Output 1 |
| ---------------------------------------------------- | --------------- |
| `8 2 2 1 2 4 0 3 0 20 1 6 20 1 3 3 2 0 4 5 1 7 1 0 ` | `15 `           |

## Solution

[main.cpp](main.cpp)