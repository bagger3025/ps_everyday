import random
import string

n = random.randrange(100, 300)
s = "".join([random.choice(string.ascii_uppercase) for _ in range(n)])

q = random.randrange(100, 200)
print(f"{n} {q}")
print(s)
for _ in range(q):
    x = random.randrange(1, 3)
    if n == 0:
        x = 1
    if x == 1:
        ch = random.choice(string.ascii_uppercase)
        idx = random.randrange(1, n + 2)
        print(f"{x} {ch} {idx}")
        n += 1
    else:
        lidx = random.randrange(1, n + 1)
        ridx = random.randrange(lidx, n + 1)
        print(f"{x} {lidx} {ridx}")
        n -= ridx - lidx + 1
