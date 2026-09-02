# Problem C — Budgeted Study Plan (0/1 Knapsack)

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
n T
t1 v1
t2 v2
...
tn vn
```

## Output format
```
best
```

## Example
```
$ echo "3 10
3 4
4 5
7 10" | ./main
14
```

## Tests
See the `tests/` folder. Run `bash tests/run_tests.sh`.
