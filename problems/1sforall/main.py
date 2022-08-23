import math

dp = [0] * 100001
dp[1] = 1

def sol(n):
    # if n in dp:
    #     return dp[n]

    if n == 1:
        return

    min_com = 100001

    # a c b: O(C)
    if n >= 10000:
        n1 = n % 10000
        n2 = n // 10000
        if n1 >= 1000 and dp[n1] + dp[n2] < min_com:
            min_com = dp[n1] + dp[n2]
    
    if n >= 1000:
        n1 = n % 1000
        n2 = n // 1000
        if n1 >= 100 and dp[n1] + dp[n2] < min_com:
            min_com = dp[n1] + dp[n2]

    if n >= 100:
        n1 = n % 100
        n2 = n // 100
        if n1 >= 10 and dp[n1] + dp[n2] < min_com:
            min_com = dp[n1] + dp[n2]
    
    if n >= 10:
        n1 = n % 10
        n2 = n // 10
        if n1 >= 1 and dp[n1] + dp[n2] < min_com:
            min_com = dp[n1] + dp[n2]

    # a*b: (O(sqrt(n)))
    i = 2
    while (i <= n/i):
        if n % i == 0:
            new_com = dp[i] + dp[n//i]
            if new_com < min_com:
                min_com = new_com
        i += 1

    # a+b: O(n)
    i = 1
    while n-i >= i:
        new_com = dp[i] + dp[n-i]
        if new_com < min_com:
            min_com = new_com
        i += 1
    
    dp[n] = min_com

if __name__ == "__main__":
    n = int(input())
    for i in range(1,n+1):
        sol(i)
    print(dp[n])