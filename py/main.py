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
    if x == n - 1 or x == 1:
        return True
    for _ in range(t - 1):
        x = (x * x) % n
        if x == n - 1:
            return True
        if x == 1:
            return False
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
