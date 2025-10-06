import random
import sys
import subprocess

from typing import List

EXECUTABLE = "./e"

subprog = subprocess.Popen(
    EXECUTABLE, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True
)

sys.stdin = subprog.stdout
sys.stdout = subprog.stdin

n = random.randrange(1, 1000)
print(n, file=subprog.stdin)


def get_skyscrape(idx_list: List[int], answer_list: List[int]) -> List[int]:
    ans = [idx_list[0]]
    maxval = answer_list[idx_list[0] - 1]
    for idx in idx_list[1:]:
        if answer_list[idx - 1] > maxval:
            maxval = answer_list[idx - 1]
            ans.append(idx)

    return ans


def print_error(answer_list, user_list):
    answer_str = ", ".join([str(t) for t in answer_list])
    user_str = ", ".join([str(t) for t in user_list])
    print(
        f"ERROR! Answer list = [{answer_str}], but user answered [{user_str}]",
        file=sys.stderr,
    )


for _ in range(n):
    x = random.randrange(1, 100)
    print(x)
    print(x, file=sys.stderr)
    answer_list = [i for i in range(1, x * x + 2)]
    random.shuffle(answer_list)

    while True:
        user_input = input()
        if user_input[0] == "?":
            user_input = user_input[2:]
            user_list = list(map(int, user_input.split()))
            user_list = user_list[1:]

            ans = get_skyscrape(user_list, answer_list)
            print(f"{len(ans)} {' '.join([str(t) for t in ans])}")
        elif user_input[0] == "!":
            user_input = user_input[2:]
            user_list = list(map(int, user_input.split()))

            curval = answer_list[user_list[0] - 1]
            increasing = 0
            for i in range(1, x):
                user_val = answer_list[user_list[i] - 1]
                if user_val > curval:
                    if increasing == -1:
                        print_error(answer_list, user_list)
                        exit(1)
                    else:
                        increasing = 1
                        curval = user_val
                else:
                    if increasing == 1:
                        print_error(answer_list, user_list)
                        exit(1)
                    else:
                        increasing = -1
                        curval = user_val
            break
