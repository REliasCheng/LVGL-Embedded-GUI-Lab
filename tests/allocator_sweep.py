"""Run each one-shot allocator failure in a fresh real LVGL process."""

import re
import subprocess
import sys


def run(executable, index):
    proc = subprocess.run(
        [executable, str(index)], capture_output=True, text=True, errors="replace", timeout=8,
    )
    return proc.returncode, proc.stdout + proc.stderr


def sweep(executable):
    rc, out = run(executable, 0)
    print(out, end="")
    match = re.search(r"allocation=0 calls=(\d+) result=usable", out)
    if rc or not match or not int(match[1]):
        return 1
    failures = []
    for index in range(1, int(match[1]) + 1):
        rc, out = run(executable, index)
        if rc:
            failures.append((index, rc))
        print(out, end="")
    if failures:
        print(f"allocator sweep failures: {failures}", file=sys.stderr)
    return bool(failures)


if __name__ == "__main__":
    sys.exit(sweep(sys.argv[1]))
