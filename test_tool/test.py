import os
from os import listdir
from os.path import isfile, join

STRESS_TEST = 500

TEST_DIR = "../boj/testcase/4008"
STRESS_DIR = "../boj/testcase/4008/stress"

GENERATE_EXEC = "python3 ../boj/testcase/4008/stress/gen.py"

REF = "../boj/ref"
EXEC = "../boj/e4008"


def run_test():
    files = [
        f
        for f in listdir(TEST_DIR)
        if isfile(join(TEST_DIR, f)) and f.startswith("input")
    ]

    for f in files:
        postfix = f[5:]
        input_file = f"{TEST_DIR}/input{postfix}"
        ref_file = f"{TEST_DIR}/output{postfix}"
        output_file = f"{TEST_DIR}/out.txt"

        os.system(f"{EXEC} < {input_file} > {output_file}")

        with open(ref_file, "r") as f:
            ref_str = "\\n".join(f.readlines()).strip()
        with open(output_file, "r") as f:
            out_str = "\\n".join(f.readlines()).strip()

        if ref_str != out_str:
            print(f"Expected [{ref_str}], but got [{out_str}]! Check {output_file}")
            exit(1)

        os.system(f"rm -f {output_file}")

    print("Passed predefined Test!")


def stress_test():
    for i in range(STRESS_TEST):
        if i > 0 and i % (STRESS_TEST / 10) == 0:
            print(f"{i}/{STRESS_TEST}")
        stress_input_file = f"{STRESS_DIR}/input{i}"
        stress_output_file = f"{STRESS_DIR}/output{i}"
        stress_ref_file = f"{STRESS_DIR}/ref{i}"

        os.system(f"{GENERATE_EXEC} > {stress_input_file}")
        os.system(f"{EXEC} < {stress_input_file} > {stress_output_file}")
        os.system(f"{REF} < {stress_input_file} > {stress_ref_file}")

        with open(stress_ref_file, "r") as f:
            ref_str = "\\n".join(f.readlines()).strip()
        with open(stress_output_file, "r") as f:
            out_str = "\\n".join(f.readlines()).strip()

        if ref_str != out_str:
            print(f"Expected [{ref_str}], but got [{out_str}]! Check {STRESS_DIR}")
            exit(1)

        os.system(f"rm -f {stress_input_file} {stress_output_file} {stress_ref_file}")
    print("STRESS TEST passed!")


if __name__ == "__main__":
    run_test()
    stress_test()
