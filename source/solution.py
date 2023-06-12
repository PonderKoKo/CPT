for _ in range(int(input())):
    n, w, h = map(int, input().split())
    a = [1, 1]
    while a[0]*w+a[1]*h <= n:
        a[a[0]*w+w > a[1]*h+h] += 1
    print(max(a[0]*w, a[1]*h))