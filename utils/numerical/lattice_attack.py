import flint


def collide(moduli, bases, sigma, c=100, n=1):
    assert sigma >= 8, "Lattice Reduction Attack doesn't work well for small alphabets"
    assert len(moduli) == len(bases)
    m = flint.fmpz_mat([
        [0] * i + [1] + [0] * (n - i - 1) + [c * pow(b, i, m) for m, b in zip(moduli, bases)]
        for i in range(n)
    ]).lll().tolist()
    return next(filter(lambda x: not any(x[-len(moduli):]) and max(map(abs, x)) < sigma, m), None) \
        or collide(moduli, bases, sigma, c, n + 1)


def collide_strings(alpha, collision):
    return tuple(''.join(chr(ord(alpha) + max(0, sign * c)) for c in collision) for sign in [-1, 1])


def h(s, modulus, base):
    return sum(ord(c) * pow(base, i, modulus) for i, c in enumerate(s)) % modulus


def main():
    alpha, sigma = 'a', 26
    moduli = [993019889, 997084241]
    bases = [307] * 2
    col = collide(moduli, bases, sigma, 8)
    s, t = collide_strings(alpha, col[:-1])
    print(s, t)
    for m, b in zip(moduli, bases):
        assert h(s, m, b) == h(t, m, b), "String Hashes should match"


if __name__ == "__main__":
    main()
