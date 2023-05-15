import string, random as rd
t = 10000
print(t)
for i in range(t):
    print(rd.randint(2, 10**9))

# s = ''.join(choice(string.ascii_lowercase) for i in range(n))
# rd.randint(inc, inc)

# g = nx.random_tree(n)
# e = list(g.edges)
# rd.shuffle(e)