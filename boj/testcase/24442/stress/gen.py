import random

n = random.randrange(1, 20)
# n = 200000
k = random.randrange(1, n + 1)

xs = [str(random.randrange(1, n + 1)) for _ in range(n)]

print(f"{n} {k}")
print(" ".join(xs))
