def solve():
    a = input()
    s = input()
    print(int(a) + len(set(s)))

t = int(input())
for i in range(t):
    solve()
