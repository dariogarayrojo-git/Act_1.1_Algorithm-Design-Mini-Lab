# Report — Algorithm Design Mini-Lab

---

## Problem A — Inversion Counter for Quality Control

### 1. Problem summary

Given an array `A` of `n` integers, an **inversion** is a pair of indices
`(i, j)` with `i < j` and `A[i] > A[j]`. The task is to count the total
number of inversions. A brute-force approach checks all pairs in `O(n^2)`,
which is too slow for `n` up to `2*10^5`. An approach that exploits a
recursive structure of the problem is needed to bring the complexity down
to `O(n log n)`.

### 2. Algorithm idea

Inversions can be counted with a modified version of **Merge Sort**
(Divide & Conquer):

- The array is recursively split in half.
- Each half is sorted, and the number of inversions **within** each half is
  counted (recursion).
- While **merging** the two already-sorted halves, the **cross**
  inversions are counted (an inversion between the left half and the right
  half): if, during the merge, an element from the right side is taken
  before the left side is exhausted, every remaining element in the left
  half forms an inversion with it (because the left half is sorted in
  ascending order, so if `A[i] > A[j]`, then `A[i+1..mid] > A[j]` too).

Total inversions = inversions in the left half + inversions in the right
half + cross inversions detected during the merge.

**Correctness justification (invariant):** at each recursive call over the
subarray `[l, r]`, when it finishes, the subarray ends up sorted and the
returned value is exactly the number of original inversions within
`[l, r]`. This holds by induction on the subarray size: the base case
(`l >= r`) has 0 inversions; the inductive step assumes the calls on the
two halves correctly count their internal inversions, and the merge counts
exactly the cross inversions because both halves are already sorted at the
time they are merged.

### 3. Pseudocode

```
function sortCount(A, l, r):
    if l >= r: return 0
    mid = (l + r) / 2
    inv = 0
    inv += sortCount(A, l, mid)
    inv += sortCount(A, mid+1, r)
    inv += mergeCount(A, l, mid, r)
    return inv

function mergeCount(A, l, mid, r):
    i = l, j = mid+1, k = l
    inv = 0
    tmp = new array of size r-l+1
    while i <= mid and j <= r:
        if A[i] <= A[j]:
            tmp[k++] = A[i++]
        else:
            inv += (mid - i + 1)   // A[i..mid] all form an inversion with A[j]
            tmp[k++] = A[j++]
    copy the remainder of A[i..mid] and A[j..r] into tmp
    copy tmp back into A[l..r]
    return inv
```

### 4. Worked example

Input: `A = [2, 4, 1, 3, 5]`

- Split into `[2, 4]` and `[1, 3, 5]`.
- `[2, 4]`: already sorted, 0 internal inversions.
- `[1, 3, 5]`: already sorted, 0 internal inversions.
- Merge of `[2, 4]` with `[1, 3, 5]`:
  - Compare 2 vs 1 -> 1 < 2, take 1 (from the right) before 2 and 4 -> adds
    2 inversions ((2,1) and (4,1)).
  - Compare 2 vs 3 -> take 2.
  - Compare 4 vs 3 -> 3 < 4, take 3 before 4 -> adds 1 inversion ((4,3)).
  - Take 4, then 5.
- Total: 2 + 1 = **3 inversions**, matching the expected result
  (`(2,1)`, `(4,1)`, `(4,3)`).

Output: `3` (correct)

### 5. Complexity analysis

**Time:** the algorithm follows the same recurrence as Merge Sort:

```
T(n) = 2*T(n/2) + O(n)
```

By the Master Theorem (case 2, since `a=2, b=2, f(n)=Theta(n)=Theta(n^(log_2 2))`):

```
T(n) = O(n log n)
```

This holds both in the worst case (reverse-sorted array, `n(n-1)/2`
inversions) and the best case (already-sorted array, 0 inversions): the
work done to split and merge is always `O(n log n)` regardless of the
values.

**Space:** an auxiliary array `tmp` of size `n` is used for the merge step
(`O(n)`), plus the recursion stack of depth `O(log n)`. Total auxiliary
space: `O(n)`.

---

## Problem B - Minimum Meeting Rooms (Scheduling)

### 1. Problem summary

Given `m` meetings, each with a start time `s_i` and end time `e_i`, the
task is to find the minimum number of rooms needed so that all meetings can
take place, where a room can host only one meeting at a time. If a meeting
ends exactly when another starts, they are **not** considered to overlap.

### 2. Algorithm idea

The minimum number of rooms needed at any instant equals the **maximum
number of meetings simultaneously active** at any point in time. This is
computed with a **greedy** event-sweep approach:

- Start times and end times are sorted separately.
- Meetings are processed in order of start time. A pointer keeps track of
  the earliest end time that hasn't "freed" its room yet.
- If the next meeting starts **before** the meeting with the earliest end
  finishes (`starts[i] < ends[j]`), a new room is needed.
- If it starts at the same time or after (`starts[i] >= ends[j]`), a room
  that has already been freed is reused.
- The maximum number of simultaneously used rooms during the whole sweep is
  tracked; that maximum is the answer.

**Greedy-choice property:** it is always optimal to reuse a room as soon as
it becomes free (instead of "reserving" it for some future meeting),
because any meeting starting later can use that room just as well;
delaying its reuse never reduces the total number of rooms needed and
could force an unnecessary new room to be opened. Additionally, the
maximum number of simultaneous meetings is an unavoidable lower bound (at
that instant, each of those meetings *needs* a distinct room), so the
algorithm achieves exactly that bound, making it optimal.

### 3. Pseudocode

```
function minRooms(meetings[1..m]):
    starts = sort([s_i for each meeting])
    ends   = sort([e_i for each meeting])
    i = 0, j = 0
    rooms = 0, maxRooms = 0
    while i < m:
        if starts[i] < ends[j]:
            rooms += 1
            i += 1
            maxRooms = max(maxRooms, rooms)
        else:
            rooms -= 1
            j += 1
    return maxRooms
```

### 4. Worked example

Input: meetings `(0,30), (5,10), (15,20)`

- `starts = [0, 5, 15]`, `ends = [10, 20, 30]`
- `i=0`: `starts[0]=0 < ends[0]=10` -> new room. `rooms=1`, `maxRooms=1`
- `i=1`: `starts[1]=5 < ends[0]=10` -> new room. `rooms=2`, `maxRooms=2`
- `i=2`: `starts[2]=15 >= ends[0]=10` -> a room is freed. `rooms=1`, `j=1`
- Now `starts[2]=15 < ends[1]=20` -> new room. `rooms=2`, `maxRooms=2`

Output: `2` (matches expectation: `(0,30)` overlaps with `(5,10)` and
then with `(15,20)`, but `(5,10)` and `(15,20)` never coincide, so 2 rooms
are enough)

### 5. Complexity analysis

**Time:** sorting `starts` and `ends` takes `O(m log m)` each. The
subsequent sweep goes through each array only once (`i` and `j` only move
forward, never backward), so it is `O(m)`. Total: `O(m log m)`.

**Space:** two auxiliary arrays of size `m` are used (`starts`, `ends`), so
the auxiliary space is `O(m)`.

---

## Problem C - Budgeted Study Plan (0/1 Knapsack Variant)

### 1. Problem summary

There are `n` study modules, each with a time cost `time[i]` hours and a
benefit `value[i]`. Given a total time budget of `T` hours, and each module
being usable **at most once**, the goal is to maximize the total value
without exceeding `T`. This is the classic **0/1 knapsack** variant. An
exhaustive subset search is `O(2^n)`, infeasible for `n` up to 2000.

### 2. Algorithm idea

**Dynamic programming** is used. Define:

```
dp[j] = maximum value achievable with a time budget of j,
        using the modules considered so far
```

**Optimal substructure:** the optimal solution for a budget `j`
considering the first `i` modules either does not include module `i` (in
which case the optimal value is the same as with `i-1` modules and budget
`j`), or it includes it (in which case the optimal value is `value[i]`
plus the optimum with `i-1` modules and budget `j - time[i]`). This gives
the recurrence:

```
dp[i][j] = max( dp[i-1][j],  dp[i-1][j - time[i]] + value[i] )   if time[i] <= j
dp[i][j] = dp[i-1][j]                                             if time[i] > j
```

Since each row `i` only depends on row `i-1`, the table can be **compressed
into a 1D array**, as long as `j` is updated in **decreasing order** (from
`T` down to `time[i]`). This prevents a module from being used more than
once within the same iteration `i` (which would happen if updated in
increasing order, degenerating into an unbounded knapsack).

### 3. Pseudocode

```
function knapsack(n, T, time[1..n], value[1..n]):
    dp = array of size T+1, initialized to 0
    for i = 1 to n:
        if time[i] > T: continue
        for j = T down to time[i]:
            dp[j] = max(dp[j], dp[j - time[i]] + value[i])
    return dp[T]
```

### 4. Worked example

Input: `T=10`, modules `(3,4), (4,5), (7,10)`

- After processing module 1 `(t=3, v=4)`: `dp[3..10] = 4` (this module can
  be taken at any budget >= 3).
- After processing module 2 `(t=4, v=5)`: for `j=7`, `dp[7] = max(4,
  dp[3]+5) = max(4, 9) = 9`; for `j=10`, similarly, `dp[10]` rises to 9.
- After processing module 3 `(t=7, v=10)`: for `j=10`, `dp[10] = max(9,
  dp[3] + 10) = max(9, 4+10) = 14`.

Output: `14` (modules 1 and 3 are taken: time `3+7=10`, value `4+10=14`)

### 5. Complexity analysis

**Time:** two nested loops, the outer one iterating over the `n` modules
and the inner one over up to `T` budget values. Each `dp[j]` update is
`O(1)`. Total: `O(n*T)`. With the given bounds (`n <= 2000`, `T <= 5000`),
this is at most `10^7` operations, perfectly feasible.

**Space:** thanks to the 1D compression, only an array `dp[0..T]` is
stored, i.e. `O(T)` (instead of `O(n*T)` that a full 2D table would
require).

---

## Complexity summary

| Problem | Technique | Time | Space |
|---------|-----------|------|-------|
| A - Inversion Counter | Divide & Conquer | O(n log n) | O(n) |
| B - Minimum Meeting Rooms | Greedy | O(m log m) | O(m) |
| C - Budgeted Study Plan | Dynamic Programming | O(n*T) | O(T) |
