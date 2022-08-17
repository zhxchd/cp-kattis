import sys

arr = []
t = {}

def can_split(begin, target):
    if (begin, target) in t:
        return t[(begin, target)]
    if target < 0:
        return False
    if begin == len(arr) - 1:
        t[(begin, target)] = target == arr[begin]
    else:
        t[(begin, target)] = can_split(begin+1, target-arr[begin]) or can_split(begin+1, target)
    return t[(begin, target)]

if __name__ == "__main__":
    input()
    arr = [int(x) for x in input().split()]
    s = sum(arr)
    if s % 2 != 0 or (not can_split(0, s/2)):
        print("NO")
    else:
        print("YES")
