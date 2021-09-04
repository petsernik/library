from random import randint
import time


# checking for prime
# p(fp)=1/4
# complexity: O(log(n))
def miller_rabin(n):
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n & 1 == 0:
        return False
    u = n - 1
    deg = 0
    while u & 1 == 0:
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
    elif op == Operation.Min:
        return min(x, y)
    elif op == Operation.Max:
        return max(x, y)
    # elif op == Operation.Gcd:
    #     return gcd(x, y)
    # elif op == Operation.Lcd:
    #     return lcd(x, y)


MaxN = int(1e6)
t = [0 for _ in range(4 * MaxN)]


# Segment tree
# Build: O(n)
# Get value, update: O(log(n))
# main call: v=1, tl=0, tr=n-1
def build(a, v, tl, tr, op=Operation.Add):
    if tl == tr:
        t[v] = a[tl]
    else:
        tm = (tl + tr) // 2
        build(a, 2 * v, tl, tm, op)
        build(a, 2 * v + 1, tm + 1, tr, op)
        t[v] = operate(t[2 * v], t[2 * v + 1], op)


# main call: v=1, tl=0, tr=n-1
def get(v, tl, tr, left, right, op=Operation.Add):
    if left == tl and right == tr:
        return t[v]
    tm = (tl + tr) // 2
    if left > tm:
        return get(2 * v + 1, tm + 1, tr, max(left, tm + 1), right, op)
    if tm + 1 > right:
        return get(2 * v, tl, tm, left, min(right, tm), op)
    x = get(2 * v, tl, tm, left, min(right, tm), op)
    y = get(2 * v + 1, tm + 1, tr, max(left, tm + 1), right, op)
    return operate(x, y, op)


# main call: v=1, tl=0, tr=n-1
def update(v, tl, tr, pos, new_val, op=Operation.Add):
    while tl != tr:
        tm = (tl + tr) // 2
        if pos <= tm:
            v *= 2
            tr = tm
        else:
            v = 2 * v + 1
            tl = tm + 1
    t[v] = new_val
    while v > 1:
        v //= 2
        t[v] = operate(t[2 * v], t[2 * v + 1], op)


# def update(v, tl, tr, pos, new_val, op=Operation.Add):
#     if tl == tr:
#         t[v] = new_val
#     else:
#         tm = (tl + tr) // 2
#         if pos <= tm:
#             update(2 * v, tl, tm, pos, new_val, op)
#         else:
#             update(2 * v + 1, tm + 1, tr, pos, new_val, op)
#         t[v] = operate(t[2 * v], t[2 * v + 1], op)


def quicksort(a, n, x):
    if n - a >= 2:
        i = partition(a, n, x)
        quicksort(a, i, x)
        quicksort(i + 1, n, x)


def partition(a, n, x):
    # n >= 2
    p = randint(a, n - 1)
    y = x[p]
    x[p], x[n - 1] = x[n - 1], x[p]
    i = a
    j = n - 1
    while i < j:
        if x[i] < y:
            i += 1
        elif x[j] >= y:
            j -= 1
        else:
            x[i], x[j] = x[j], x[i]
    if x[i] < y:
        i += 1
    x[i], x[n - 1] = x[n - 1], x[i]
    return i


def time_of_work():
    for deg in range(2):
        n = pow(10, deg)
        x = [randint(0, 10) for _ in range(n)]
        t0 = time.time()
        print(x)
        quicksort(0, len(x), x)
        print(x)
        # sorted(x)
        t1 = time.time()
        print(f'n = 10^{deg}, ms={int(1000 * (t1 - t0))}')


if __name__ == '__main__':
    time_of_work()
