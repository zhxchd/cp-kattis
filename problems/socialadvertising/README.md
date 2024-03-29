# Social Advertising

You have decided to start up a new social networking company. Other existing popular social networks already have billions of users, so the only way to compete with them is to include novel features no other networks have.

Your company has decided to market to advertisers a cheaper way to charge for advertisements (ads). The advertiser chooses which users’ “wall” the ads would appear on, and only those ads are charged. When an ad is posted on a user’s wall, all of his/her friends (and of course the user himself/herself) will see the ad. In this way, an advertiser only has to pay for a small number of ads to reach many more users.

You would like to post ads to a particular group of users with the minimum cost. You already have the “friends list” of each of these users, and you want to determine the smallest number of ads you have to post in order to reach every user in this group. In this social network, if A is a friend of B, then B is also a friend of A for any two users A and B.

## Input

The input consists of multiple test cases. The first line of input is a single integer, not more than 10, indicating the number of test cases to follow. Each case starts with a line containing an integer n (1≤n≤20) indicating the number of users in the group. For the next n lines, the i-th line contains the friend list of user i (users are labelled 1,…,n). Each line starts with an integer d (0≤d<n) followed by d labels of the friends. No user is a friend of himself/herself.

## Output

For each case, display on a line the minimum number of ads needed to be placed in order for them to reach the entire group of users.

| Sample Input 1                                               | Sample Output 1 |
| ------------------------------------------------------------ | --------------- |
| `2 5 4 2 3 4 5 4 1 3 4 5 4 1 2 4 5 4 1 2 3 5 4 1 2 3 4 5 2 4 5 2 3 5 1 2 2 1 5 3 1 2 4 ` | `1 2`           |

## Solution

[main.cpp](main.cpp)