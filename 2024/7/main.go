package main

import (
	"fmt"
	"os"
	"strings"
)

func addOps(ops []int, index int, con bool) []int {
	mod := 2
	if con {
		mod = 3
	}
	ops[index] = (ops[index] + 1) % mod
	if ops[index] == 0 {
		return addOps(ops, index+1, con)
	}
	return ops

}

func combine(a uint, b uint) uint {
	var aa string = fmt.Sprintf("%v", a)
	var bb string = fmt.Sprintf("%v", b)
	var target uint
	if _, err := fmt.Sscan(aa+bb, &target); err != nil {
		panic(err)
	}
	return target
}

func bruteForce(nums []uint, target uint, ops []int, con bool) uint {
	sum := nums[0]
	for index, num := range nums[1:] {
		op := ops[index]
		if op == 0 {
			sum *= num
		} else if op == 1 {
			sum += num
		} else {
			sum = combine(sum, num)
		}
	}

	if sum == target {
		return sum
	}

	end := true
	for _, i := range ops {
		if i == 0 {
			end = false
		} else if (i == 1) && con {
			end = false
		}

	}

	if end {
		return 0
	}

	return bruteForce(nums, target, addOps(ops, 0, con), con)

}

func validate(line string, con bool) uint {
	before, after, found := strings.Cut(line, ":")
	if found {
		var target uint
		if _, err := fmt.Sscan(before, &target); err == nil {
			testSubjects := strings.Split(after, " ")
			var nums []uint
			for _, num := range testSubjects {
				if strings.Compare(num, "") == 0 {
					continue
				}
				var i uint
				if _, err := fmt.Sscan(num, &i); err != nil {
					panic(err)
				}
				nums = append(nums, i)
			}
			ops := []int{}
			for range nums {
				ops = append(ops, 0)
			}
			return bruteForce(nums, target, ops, con)

		}

	}
	return 0
}

func main() {
	filename := "input"
	data, err := os.ReadFile(filename)
	if err != nil {
		panic(err)
	}
	input := string(data[:])
	lines := strings.Split(input, "\n")
	var sum uint = 0
	var con uint = 0
	for _, line := range lines {
		sum += validate(line, false)
		con += validate(line, true)
	}
	fmt.Println(sum, con)
}
