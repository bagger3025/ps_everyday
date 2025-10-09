import os
from os import listdir
from os.path import isfile, isdir, join, abspath, dirname
import subprocess

STRESS_TEST = 500
OVERHEAD_TEST = 100

PROBLEM_NUM = "c"
CODE_RELPATH = "../codeforces/2145_Educational_Codeforces_Round_183"


CUR_DIR = dirname(abspath(__file__))
CODE_PATH = f"{CUR_DIR}/{CODE_RELPATH}"
TEST_DIR = f"{CODE_PATH}/testcase/{PROBLEM_NUM}"
EXEC = f"{CODE_PATH}/e_{PROBLEM_NUM}"
REF = f"{CODE_PATH}/w_{PROBLEM_NUM}"

STRESS_DIR = f"{TEST_DIR}/stress"
GENERATE_FILE = f"{STRESS_DIR}/gen.py"
OVERHEAD_GENERATE_FILE = f"{STRESS_DIR}/gen_overhead.py"
GENERATE_EXEC = f"python3 {GENERATE_FILE}"


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
        output_file = f"{TEST_DIR}/out{postfix}"

        os.system(f"{EXEC} < {input_file} > {output_file}")

        with open(ref_file, "r") as f:
            ref_str = (
                "\n".join([line.strip() for line in f.readlines()])
                .strip()
                .replace("\n", "\\n")
            )
        with open(output_file, "r") as f:
            out_str = (
                "\n".join([line.strip() for line in f.readlines()])
                .strip()
                .replace("\n", "\\n")
            )

        if ref_str != out_str:
            print(f"Expected [{ref_str}], but got [{out_str}]! Check {output_file}")
            exit(1)

        os.system(f"rm -f {output_file}")

    print("Passed predefined Test!")


def check_if_file_exists():
    if not isdir(STRESS_DIR):
        print("STRESS_DIR not exists, skip moving")
        return
    files = [
        f
        for f in listdir(STRESS_DIR)
        if isfile(join(STRESS_DIR, f)) and not f.endswith(".py")
    ]

    if len(files) % 3 != 0:
        print("Manually organize files, or files will be rewritten")
        print(f"Check: {STRESS_DIR.replace(CODE_PATH, '.')}")
        exit(1)

    max_num = (
        max(
            [
                int(f[5:-4])
                for f in listdir(TEST_DIR)
                if isfile(join(TEST_DIR, f)) and f.startswith("input")
            ]
        )
        + 1
    )
    print("max_num will be", max_num)

    inputs = [f for f in files if f.startswith("input")]
    outputs = [f for f in files if f.startswith("out")]
    refs = [f for f in files if f.startswith("ref")]

    if len(inputs) != len(outputs) or len(outputs) != len(refs):
        print("Manually organize files, or files will be rewritten")
        print(f"Check: {STRESS_DIR.replace(CODE_PATH, '.')}")
        exit(1)

    for f in inputs:
        num_f = f[5:]
        print(
            f"move {STRESS_DIR.replace(CODE_PATH, '.')}/"
            + "{input,ref}"
            + f"{num_f} => "
            + "{input,output}"
            + f"{max_num}.txt, delete {STRESS_DIR.replace(CODE_PATH, '.')}/output{num_f}"
        )
        os.system(f"mv {STRESS_DIR}/input{num_f} {TEST_DIR}/input{max_num}.txt")
        os.system(f"mv {STRESS_DIR}/ref{num_f} {TEST_DIR}/output{max_num}.txt")
        os.system(f"rm {STRESS_DIR}/output{num_f}")
        max_num += 1


def stress_test():
    if not isdir(STRESS_DIR):
        print("STRESS_DIR not set, skip stress test")
        return
    if not isfile(GENERATE_FILE):
        print("GENERATE_FILE is not file, so skipping stress test")
        return

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
            ref_str = (
                "\n".join([line.strip() for line in f.readlines()])
                .strip()
                .replace("\n", "\\n")
            )
        with open(stress_output_file, "r") as f:
            out_str = (
                "\n".join([line.strip() for line in f.readlines()])
                .strip()
                .replace("\n", "\\n")
            )

        if ref_str != out_str:
            print(
                f"Expected [{ref_str}], but got [{out_str}]! Check {STRESS_DIR.replace(CUR_DIR, '.')}"
            )
            exit(1)

        os.system(f"rm -f {stress_input_file} {stress_output_file} {stress_ref_file}")
    print("STRESS TEST passed!")


def overhead_test():
    print("Overhead test Started")
    for i in range(OVERHEAD_TEST):
        if i % (OVERHEAD_TEST // 10) == 0:
            print(f"{i} / {OVERHEAD_TEST}")

        input_file = f"{STRESS_DIR}/input{i}"
        output_file = f"{STRESS_DIR}/output{i}"

        # make input file
        os.system(f"python3 {OVERHEAD_GENERATE_FILE} > {input_file}")

        # < stress/input{i} > stress/my_output
        try:
            process = subprocess.Popen(
                EXEC,
                stdin=open(input_file, "r"),
                stdout=open(output_file, "w"),
                text=True,
            )
            _, _ = process.communicate(timeout=1)
        except subprocess.TimeoutExpired:
            print("Overhead Test Timeout")
            exit(1)

        os.system(f"rm {input_file} {output_file}")


if __name__ == "__main__":
    if not isfile(EXEC):
        print(f"{EXEC} is not file, exit!")
        exit(1)

    check_if_file_exists()
    run_test()
    # stress_test()
    overhead_test()
