# Problem B — Minimum Meeting Rooms

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
m
s1 e1
s2 e2
...
sm em
```

## Output format
```
rooms
```

## Example
```
$ echo "3
0 30
5 10
15 20" | ./main
2
```

## Tests
See the `tests/` folder. Run `bash tests/run_tests.sh`.
