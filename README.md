# Mini-Lab: Divide & Conquer, Greedy, Dynamic Programming

This repository contains the solution to the three problems of the mini-lab.
Each problem uses a different algorithm design technique, chosen based on
the structure of each problem (it was not stated by the assignment):

| Problem | Name                              | Technique used                        | Time complexity |
|---------|------------------------------------|-----------------------------------------|-------------------|
| A       | Inversion Counter                  | Divide & Conquer (modified merge sort)  | O(n log n) |
| B       | Minimum Meeting Rooms              | Greedy (event sweep)                    | O(m log m) |
| C       | Budgeted Study Plan (0/1 Knapsack) | Dynamic Programming                     | O(n·T)     |

## Repo structure

```
problemA_inversions/
    main.cpp
    README.md
    tests/
problemB_rooms/
    main.cpp
    README.md
    tests/
problemC_knapsack/
    main.cpp
    README.md
    tests/
report.md
README.md
```

## How to compile and run each problem

All problems use C++17, read from `stdin`, and write to `stdout`.

```bash
# Problem A
cd problemA_inversions
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
./main < tests/t1.in

# Problem B
cd ../problemB_rooms
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
./main < tests/t1.in

# Problem C
cd ../problemC_knapsack
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
./main < tests/t1.in
```
or (on each problem)
```bash
Get-Content tests\t1.in | .\main.exe
Get-Content tests\t2.in | .\main.exe
Get-Content tests\t3.in | .\main.exe
```

## Assumptions

- `long long` (64-bit) is used for any value that could exceed the range of
  a 32-bit integer (inversion count, knapsack values).
- In Problem B, it is assumed that if one meeting ends exactly when another
  starts, both can share the same room (they are not considered
  overlapping), as stated in the assignment.
- In Problem C, it is assumed that no module can be taken more than once
  (0/1 knapsack, not fractional or repeatable).

See `report.md` for the detailed explanation, pseudocode, and complexity
analysis of each problem.
