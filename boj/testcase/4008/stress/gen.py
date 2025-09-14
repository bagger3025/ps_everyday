import random

n = random.randrange(1, 20000)
a = random.randrange(-5, 0)
b = random.randrange(-10000000, 10000001)
c = random.randrange(-30000000, 30000001)

xs = [str(random.randrange(1, 101)) for _ in range(n)]

print(n)
print(f"{a} {b} {c}")
print(" ".join(xs))
