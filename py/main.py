from random import randint
import time


# @log
def log(func):
    def log_func(*args, **kwargs):
        t0 = time.time()
        func(*args, **kwargs)
        t1 = time.time()
        print(f'time: {int(1000 * (t1 - t0))}\n')
        return func(*args, **kwargs)

    return log_func

def prefix_function(_s):
    p = [0 for _ in range(len(_s))]
    for i in range(1, len(_s)):
        j = p[i - 1]
        while j > 0 and _s[j] != _s[i]:
            j = p[j - 1]
        if _s[j] == _s[i]:
            p[i] = j + 1
    return p


def count_in(_t, _s):
    cnt = 0
    w = _t + '#' + _s
    tl = len(_t)
    p = prefix_function(w)
    for i in range(tl, len(w)):
        if p[i] == tl:
            cnt += 1
    return cnt

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


def get(v, tl, tr, left, right, op=Operation.Add):
    """main call: v=1, tl=0, tr=n-1"""
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


def update(v, tl, tr, pos, new_val, op=Operation.Add):
    """main call: v=1, tl=0, tr=n-1"""
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
#     """main call: v=1, tl=0, tr=n-1"""
#     if tl == tr:
#         t[v] = new_val
#     else:
#         tm = (tl + tr) // 2
#         if pos <= tm:
#             update(2 * v, tl, tm, pos, new_val, op)
#         else:
#             update(2 * v + 1, tm + 1, tr, pos, new_val, op)
#         t[v] = operate(t[2 * v], t[2 * v + 1], op)


def quicksort(a, b, x):
    if b - a >= 2:
        i = partition(a, b, x)
        quicksort(a, i, x)
        quicksort(i + 1, b, x)


def partition(a, b, x):
    p = randint(a, b - 1)
    y = x[p]
    x[p], x[b - 1] = x[b - 1], x[p]
    i = a
    j = b - 1
    while i < j:
        if x[i] < y:
            i += 1
        elif x[j] >= y:
            j -= 1
        else:
            x[i], x[j] = x[j], x[i]
    x[i], x[b - 1] = x[b - 1], x[i]
    return i


def ans_gcs(a, b):
    ans = [[0 for _ in range(len(b) + 1)] for _ in range(len(a) + 1)]
    for i in range(1, len(a) + 1):
        for j in range(1, len(b) + 1):
            if a[i - 1] == b[j - 1]:
                ans[i][j] = ans[i - 1][j - 1] + 1
            else:
                ans[i][j] = max(ans[i - 1][j], ans[i][j - 1])
    return ans


def gcs(a, b):
    n, m = len(a), len(b)
    ans = ans_gcs(a, b)
    x = ans[n][m]
    s = ''
    while x:
        if a[n - 1] == b[m - 1]:
            s += a[n - 1]
            n -= 1
            m -= 1
            x -= 1
        elif ans[n - 1][m] == x:
            n -= 1
        else:
            m -= 1
    return s[::-1]


if __name__ == '__main__':
    print(gcs("abd", "bcd"))
