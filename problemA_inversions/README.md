# Problem A — Inversion Counter

## Compile
```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
```

## Run
```bash
./main < input.txt
```

## Input format
```
n
a1 a2 ... an
```

## Output format
```
inv
```

## Example
```
$ echo "5
2 4 1 3 5" | ./main
3
```

## Tests
See the `tests/` folder (3 cases: the example from the assignment, a sorted
array, a reverse-sorted array). Run `bash tests/run_tests.sh`.
