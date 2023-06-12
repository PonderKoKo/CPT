import string, random as rd
t = 1000
print(t)
for i in range(t):
    n, k = 10, 5
    print(n, k)
    for j in range(k):
        l = rd.randint(1, n-1)
        r = rd.randint(1, n-1)
        if (r - l) % 2 == 0:
            r += 1
        if r < l:
            l, r = r, l
        print(l, r)


# s = ''.join(choice(string.ascii_lowercase) for i in range(n))
# rd.randint(inc, inc)

# g = nx.random_tree(n)
# e = list(g.edges)
# rd.shuffle(e)