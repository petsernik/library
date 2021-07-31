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
    deg = 0
    while not u & 1:  # u % 2 == 0
        u >>= 1
        deg += 1
    a = randint(2, n - 2)
    x = pow(a, u, n)
    if x == n - 1 or x == 1:
        return True
    for _ in range(deg - 1):
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


def lcd(x, y):
    return x // gcd(x, y) * y if x or y else 0


class Operation:
    Add, Gcd, Lcd, Min, Max = range(5)


def operate(x, y, op):
    if op == Operation.Add:
        return x + y
    elif op == Operation.Gcd:
        return gcd(x, y)
    elif op == Operation.Lcd:
        return lcd(x, y)
    elif op == Operation.Min:
        return min(x, y)
    elif op == Operation.Max:
        return max(x, y)


MAXN = int(1e6)
t = [0 for _ in range(4 * MAXN)]


# Segment tree
# Build: O(n)
# Get value, update: O(log(n))
# main call: v=1, tl=0, tr=n-1
def build(a, v, tl, tr, op=Operation.Add):
    if tl == tr:
        t[v] = a[tl]
    else:
        tm = (tl + tr) >> 1
        build(a, v << 1, tl, tm, op)
        build(a, (v << 1) + 1, tm + 1, tr, op)
        t[v] = operate(t[v << 1], t[(v << 1) + 1], op)


# main call: v=1, tl=0, tr=n-1
def get(v, tl, tr, l, r, op=Operation.Add):
    if l == tl and r == tr:
        return t[v]
    tm = (tl + tr) >> 1
    if l > tm:
        return get((v << 1) + 1, tm + 1, tr, max(l, tm + 1), r, op)
    if tm + 1 > r:
        return get(v << 1, tl, tm, l, min(r, tm), op)
    x = get(v << 1, tl, tm, l, min(r, tm), op)
    y = get((v << 1) + 1, tm + 1, tr, max(l, tm + 1), r, op)
    return operate(x, y, op)


# main call: v=1, tl=0, tr=n-1
def update(v, tl, tr, pos, new_val, op=Operation.Add):
    while tl != tr:
        tm = (tl + tr) >> 1
        if pos <= tm:
            v <<= 1
            tr = tm
        else:
            v = (v << 1) + 1
            tl = tm + 1
    t[v] = new_val
    while v > 1:
        v >>= 1
        t[v] = operate(t[v << 1], t[(v << 1) + 1], op)


# def update(v, tl, tr, pos, new_val, op=Operation.Add):
#     if tl == tr:
#         t[v] = new_val
#     else:
#         tm = (tl + tr) >> 1
#         if pos <= tm:
#             update(v << 1, tl, tm, pos, new_val, op)
#         else:
#             update((v << 1) + 1, tm + 1, tr, pos, new_val, op)
#         t[v] = operate(t[v << 1], t[(v << 1) + 1], op)


if __name__ == '__main__':
    a = [randint(0, 10), randint(0, 10), randint(0, 10), randint(0, 10)]
    print(a)
    n = len(a)
    v, tl, tr = 1, 0, n - 1
    op = Operation.Lcd
    build(a, v, tl, tr, op)
    print('1-2:', get(v, tl, tr, 1, 2, op))
    pos, value = randint(0, n - 1), randint(-100, 100)
    a[pos] = value
    update(v, tl, tr, pos, value, op)
    print(a)
    print('0-3:', get(v, tl, tr, 0, 3, op))
