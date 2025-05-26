import flint


def collide(mbs, sigma, c, n=1):
    m = flint.fmpz_mat([
        [j == i for j in range(n)] + [c * pow(b, i, m) for m, b in mbs]
        for i in range(n)
    ]).lll().tolist()
    return next(filter(lambda x: not any(x[-len(mbs):]) and max(map(abs, x)) < sigma, m), None) \
        or collide(mbs, sigma, c, n + 1)


def collide_strings(alpha, collision):
    return tuple(''.join(chr(ord(alpha) + max(0, sign * c)) for c in collision) for sign in [-1, 1])


def h(s, modulus, base):
    return sum(ord(c) * pow(base, i, modulus) for i, c in enumerate(s)) % modulus


def main():
    alpha, sigma = 'a', 26
    mbs = [(993019889, 307), (997084241, 307)]
    col = collide(mbs, sigma, 8)
    s, t = collide_strings(alpha, col[:-1])
    print(s, t)
    assert all(h(s, m, b) == h(t, m, b) for m, b in mbs), "String Hashes should match"


if __name__ == "__main__":
    main()
