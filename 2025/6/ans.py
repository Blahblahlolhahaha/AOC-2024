import sys
import math


def main():
    file = sys.argv[1]
    lines = []
    with open(file, "r") as f:
        lines = f.readlines()
    res = 0
    nums = []
    for i in range(len(lines)):
        lines[i] = lines[i].replace("\n", "")
    for i in range(len(lines[0]) - 1, -1, -1):
        num = ""
        for j in range(0, len(lines) - 1):
            num += lines[j][i]
        if num.strip() == "":
            continue
        nums.append(int(num.strip()))
        num = ""
        if lines[-1][i] == "+":
            res += sum(nums)
            nums = []
            i -= 1
        elif lines[-1][i] == "*":
            res += math.prod(nums)
            nums = []
            i -= 1
    print(res)


if __name__ == "__main__":
    main()
