from random import randint


# checking for prime
# p(fp)=1/4
# complexity: O(log(n))
def miller_rabin(n):
    if n <= 1:
        return False
    if n <= 3:
        return True
    if not n & 1:
        return False
    u = n - 1
    t = 0
    while not u & 1:
        u >>= 1
        t += 1
    a = randint(2, n - 2)
    x = pow(a, u, n)
    for _ in range(t):
        y = (x * x) % n
        if y == 1:
            return x == 1 or x == n - 1
        x = y
    return False


# greatest common divisor
# complexity: O(log(n)), n=min(x,y)
def gcd(x, y):
    while y:
        x %= y
        x, y = y, x
    return x


if __name__ == '__main__':
    for i in range(1, 3000):
        print(f"{i}: {randint(1, 2)}")
