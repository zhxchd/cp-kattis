def sol(n):
    max_count = 0
    max_p = None
    for i in range(2, n+1):
        # if i*i > n:
        #     break
        if i > n:
            break
        if n % i == 0:
            count = 0
            while (n % i == 0):
                count += 1
                n = n/i
            if count > max_count:
                max_count = count
                max_p = i
    return max_p


if __name__ == "__main__":
    n = int(input())
    print(sol(n))