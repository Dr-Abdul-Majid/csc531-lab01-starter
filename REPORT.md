  CSC-531 — Lab 01 Report: Arrays, Address Calculations and Safe Insertion/Deletion
	
Name	Ehsam Goher
Roll No	24
Department / Semester	CS / 3rd
Course	CSC-531 Data Structures & Algorithms (UAJK)
Language	C++17
---
Task A — Array representation and address worksheet
A.1 Indexed 8-slot array with logical size 4
Allocated capacity (`CAP`) = 8 slots. Logical size (`size`) = 4 active elements.
`-` marks an unused slot (its content is not part of the array, so it is never read).
```
 Index:     0     1     2     3     4     5     6     7
         +-----+-----+-----+-----+-----+-----+-----+-----+
 Value:  | 10  | 20  | 30  | 40  |  -  |  -  |  -  |  -  |
         +-----+-----+-----+-----+-----+-----+-----+-----+
 Address: 4000  4004  4008  4012  4016  4020  4024  4028
          |<---- active (0..3) ---->|<--- unused (4..7) --->|
                                    ^
                      next append position = index 4 (= size)
```
Active elements: indices 0, 1, 2, 3 (values 10, 20, 30, 40).
Unused slots: indices 4, 5, 6, 7 (4 free slots = `CAP - size`).
Next append position: index 4, which is equal to `size`.
The array is full only when `size == CAP` (here, 8).
A.2 One-dimensional addresses (B = 4000, w = 4)
Formula: `address(A[i]) = B + i × w`
Element	Calculation	Address
A[0]	4000 + 0 × 4 = 4000 + 0	4000
A[3]	4000 + 3 × 4 = 4000 + 12	4012
A[7]	4000 + 7 × 4 = 4000 + 28	4028
A.3 Row-major two-dimensional address: M[4][5], M[2][3] (B = 2000, w = 4)
M has 4 rows and 5 columns (20 elements). In row-major order, whole rows are stored one after another.
Formula: `address(M[i][j]) = B + (i × columns + j) × w`
```
address(M[2][3]) = 2000 + (2 × 5 + 3) × 4
                 = 2000 + 13 × 4
                 = 2000 + 52
                 = 2052
```
Explanation of the offset: before M[2][3] there are 2 complete rows (rows 0 and 1) of 5 elements each = 10 elements. Inside row 2 there are 3 more elements before column 3 (columns 0, 1, 2). So 10 + 3 = 13 elements come before M[2][3]. The offset is 13 elements × 4 bytes = 52 bytes, so the address is 2000 + 52 = 2052.
> These are conceptual calculations using the given hypothetical values of B and w. They do not assume that `sizeof(int) == 4` on every platform.
---
Implementation summary (Tasks B and C)
`insertAt(int a[], int& size, int cap, int pos, int x)` rejects an invalid position (`pos < 0` or `pos > size`) and a full array (`size >= cap`). Otherwise it shifts elements right (starting from the last active element), stores `x` at `pos` and increases `size`.
`deleteAt(int a[], int& size, int pos)` rejects an invalid index (`pos < 0` or `pos >= size`) and an empty array. Otherwise it shifts elements left (never reading beyond index `size - 1`) and decreases `size`.
On a failed operation both functions return `false` before changing anything, so neither `size` nor the array contents are modified.
No `std::vector`, `std::list` or ready-made STL insertion/deletion algorithms are used.
`main.cpp` provides a four-option menu (Display, Insert, Delete, Exit). `size` (logical size) is a separate variable from `CAP` (= 8). Input is read line by line, so non-numeric input is rejected and asked again.
---
Annotated step-by-step trace
Start: `a = {10, 20, 30, 40, -, -, -, -}`, `size = 4`, `CAP = 8`.
Trace 1 — `insertAt(a, size, 8, 2, 25)`
Step	Action	Array (active part)	size
0	Start	{10, 20, 30, 40}	4
1	Check: `size (4) < cap (8)` and `0 <= pos (2) <= size (4)` — valid, continue	{10, 20, 30, 40}	4
2	`i = 4`: `a[4] = a[3]` (copy 40 right into the free slot)	{10, 20, 30, 40, 40}	4
3	`i = 3`: `a[3] = a[2]` (copy 30 right)	{10, 20, 30, 30, 40}	4
4	`i = 2`: loop condition `i > pos` is false, so the loop stops. Slot 2 is now a free gap	{10, 20, 30, 30, 40}	4
5	`a[2] = 25` (store the new value in the gap)	{10, 20, 25, 30, 40}	4
6	`++size`, return `true`	{10, 20, 25, 30, 40}	5
Trace 2 — `deleteAt(a, size, 1)` on the result of Trace 1
Step	Action	Array	size
0	Start	{10, 20, 25, 30, 40}	5
1	Check: `size (5) > 0` and `0 <= pos (1) < size (5)` — valid, continue	{10, 20, 25, 30, 40}	5
2	`i = 1`: `a[1] = a[2]` (copy 25 left over the deleted 20)	{10, 25, 25, 30, 40}	5
3	`i = 2`: `a[2] = a[3]` (copy 30 left)	{10, 25, 30, 30, 40}	5
4	`i = 3`: `a[3] = a[4]` (copy 40 left; this reads index 4 = the last active element)	{10, 25, 30, 40, 40}	5
5	`i = 4`: loop condition `i < size - 1` (4 < 4) is false, so the loop stops. Nothing beyond index 4 is read	{10, 25, 30, 40, 40}	5
6	`--size`, return `true`. Index 4 still holds a stale 40 but it is no longer active	{10, 25, 30, 40}	4
Trace 3 — failed operation: `insertAt` on a full array (`size = 8`, `cap = 8`)
Step	Action	Result
1	Check: `size (8) >= cap (8)` is true	the array is full
2	Return `false` immediately	no shifting, no write, `size` stays 8
---
Test table (expected vs. actual)
All tests start from `{10, 20, 30, 40}` with `cap = 8` unless another starting array is shown. For every `false` result the test also checks that the whole array and `size` are unchanged. Tests were run with a small separate test program (not part of the submission) and the program was also built with AddressSanitizer/UBSan, which reported no errors.
ID	Starting array	Call	Expected	Actual	Result
T1	{10, 20, 30, 40}	`insertAt(a, size, 8, 2, 25)`	true, {10, 20, 25, 30, 40}, size 5	true, {10, 20, 25, 30, 40}, size 5	PASS
T2	{10, 20, 30, 40}	`insertAt(a, size, 8, 0, 5)`	true, {5, 10, 20, 30, 40}, size 5	true, {5, 10, 20, 30, 40}, size 5	PASS
T3	{10, 20, 30, 40}	`insertAt(a, size, 8, 4, 50)`	true, {10, 20, 30, 40, 50}, size 5	true, {10, 20, 30, 40, 50}, size 5	PASS
T4	{10, 20, 30, 40}	`insertAt(a, size, 8, 5, 99)`	false, {10, 20, 30, 40}, size 4	false, {10, 20, 30, 40}, size 4	PASS
T5	{10, 20, 30, 40}	`insertAt(a, size, 8, -1, 99)`	false, {10, 20, 30, 40}, size 4	false, {10, 20, 30, 40}, size 4	PASS
T6	{1, 2, 3, 4, 5, 6, 7, 8}	`insertAt(a, size, 8, 3, 99)`	false, {1, 2, 3, 4, 5, 6, 7, 8}, size 8	false, {1, 2, 3, 4, 5, 6, 7, 8}, size 8	PASS
T7	{}	`insertAt(a, size, 8, 0, 99)`	true, {99}, size 1	true, {99}, size 1	PASS
T8	{1, 2, 3, 4, 5, 6, 7}	`insertAt(a, size, 8, 7, 8)`	true, {1, 2, 3, 4, 5, 6, 7, 8}, size 8	true, {1, 2, 3, 4, 5, 6, 7, 8}, size 8	PASS
T9	{10, 20, 30, 40}	`deleteAt(a, size, 1)`	true, {10, 30, 40}, size 3	true, {10, 30, 40}, size 3	PASS
T10	{10, 20, 30, 40}	`deleteAt(a, size, 0)`	true, {20, 30, 40}, size 3	true, {20, 30, 40}, size 3	PASS
T11	{10, 20, 30, 40}	`deleteAt(a, size, 3)`	true, {10, 20, 30}, size 3	true, {10, 20, 30}, size 3	PASS
T12	{10, 20, 30, 40}	`deleteAt(a, size, 4)`	false, {10, 20, 30, 40}, size 4	false, {10, 20, 30, 40}, size 4	PASS
T13	{10, 20, 30, 40}	`deleteAt(a, size, -1)`	false, {10, 20, 30, 40}, size 4	false, {10, 20, 30, 40}, size 4	PASS
T14	{}	`deleteAt(a, size, 0)`	false, {}, size 0	false, {}, size 0	PASS
T15	{77}	`deleteAt(a, size, 0)`	true, {}, size 0	true, {}, size 0	PASS
T16	{10, 20, 30, 40}	insert(1,15), delete(3), insert(4,50), delete(0)	true, {15, 20, 40, 50}, size 4	true, {15, 20, 40, 50}, size 4	PASS
Result: 16 / 16 tests passed. T1–T3 and T9–T11 are normal cases (middle, front, end), T4–T5 and T12–T13 are invalid positions, T6 is insertion into a full array, T14 is deletion from an empty array, T7–T8 and T15 are boundary sizes, and T16 checks repeated updates.
Menu demonstration output (`main.cpp`)
Compiled with `g++ -std=c++17 -Wall -Wextra -pedantic main.cpp lab01.cpp -o main` (no warnings). The menu text is shortened below to show only the prompts and results.
Normal cases and bad menu input (non-number `abc` and out-of-range choice `7` are rejected; insert 25 at position 2, then delete index 1):
```
Enter choice (1-4): Invalid input. Please enter a whole number.
Enter choice (1-4): Invalid choice. Please enter 1, 2, 3 or 4.
Enter choice (1-4):
size = 4, CAP = 8
Index:   [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]
Value:    10   20   30   40    -    -    -    -
Next append position: 4
Enter choice (1-4): Enter position (0 to 4): Enter value to insert: Inserted 25 at position 2.
Enter choice (1-4):
size = 5, CAP = 8
Index:   [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]
Value:    10   20   25   30   40    -    -    -
Next append position: 5
Enter choice (1-4): Enter index to delete: Deleted the element at index 1.
Enter choice (1-4):
size = 4, CAP = 8
Index:   [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]
Value:    10   25   30   40    -    -    -    -
Next append position: 4
```
Insertion when the array is full (four appends fill the array, then a fifth insert is rejected and the array is unchanged):
```
Enter choice (1-4): Enter position (0 to 4): Enter value to insert: Inserted 50 at position 4.
Enter choice (1-4): Enter position (0 to 5): Enter value to insert: Inserted 60 at position 5.
Enter choice (1-4): Enter position (0 to 6): Enter value to insert: Inserted 70 at position 6.
Enter choice (1-4): Enter position (0 to 7): Enter value to insert: Inserted 80 at position 7.
Enter choice (1-4):
size = 8, CAP = 8
Index:   [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]
Value:    10   20   30   40   50   60   70   80
Array is full: no append position available.
Enter choice (1-4): Enter position (0 to 8): Enter value to insert: Insert failed: array is full (size == CAP == 8). Nothing was changed.
Enter choice (1-4):
size = 8, CAP = 8
Index:   [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]
Value:    10   20   30   40   50   60   70   80
Array is full: no append position available.
```
Deletion when the array is empty (four deletions empty the array, then a fifth delete is rejected):
```
Enter choice (1-4): Enter index to delete: Deleted the element at index 0.
Enter choice (1-4): Enter index to delete: Deleted the element at index 0.
Enter choice (1-4): Enter index to delete: Deleted the element at index 0.
Enter choice (1-4): Enter index to delete: Deleted the element at index 0.
Enter choice (1-4):
size = 0, CAP = 8
Index:   [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]
Value:     -    -    -    -    -    -    -    -
Next append position: 0
Enter choice (1-4): Enter index to delete: Delete failed: array is empty. Nothing was changed.
```
Invalid positions (all four rejected, array still `{10, 20, 30, 40}`, size 4):
```
Insert failed: invalid position 9 (valid range is 0 to 4). Nothing was changed.
Insert failed: invalid position -1 (valid range is 0 to 4). Nothing was changed.
Delete failed: invalid index 4 (valid range is 0 to 3). Nothing was changed.
Delete failed: invalid index -2 (valid range is 0 to 3). Nothing was changed.
```
---
Worst-case time and auxiliary-space complexity
Let n be the current logical size (`size`).
Function	Worst case	Why	Worst-case time	Auxiliary space
`insertAt`	Insert at position 0	all n active elements are shifted one place right	O(n)	O(1)
`deleteAt`	Delete at index 0	the remaining n − 1 elements are shifted one place left	O(n)	O(1)
Best case for both is O(1): inserting at the end (`pos == size`) or deleting the last element needs no shifting.
The failed cases (invalid position, full or empty array) only do a few comparisons, so they take O(1) time.
Auxiliary space is O(1) because the functions only use a loop counter; the shifting is done in place inside the given array and no extra array is created.
---
One bug found and fixed
Bug: in my first version of `insertAt` the shifting loop ran from the insert position forwards (left to right):
```cpp
for (int i = pos; i < size; ++i) {   // WRONG: forward shift
    a[i + 1] = a[i];
}
```
Symptom: for `{10, 20, 30, 40}`, `size = 4`, `insertAt(..., pos = 2, x = 25)` I expected `{10, 20, 25, 30, 40}` but the program printed:
```
size = 5, array = {10, 20, 25, 30, 30}
```
The value 40 was lost and 30 was duplicated.
Cause: copying forwards overwrites the next element before it has been copied. At `i = 2`, `a[3]` was overwritten with 30 (so the old 30 was copied, but the old `a[3] = 40` was destroyed). At `i = 3`, `a[4] = a[3]` then copied that same 30 again. When shifting right, each element must be moved into a slot that is already free or already copied.
Fix: shift backwards, starting from the last active element and moving down to `pos + 1`:
```cpp
for (int i = size; i > pos; --i) {   // CORRECT: backward shift
    a[i] = a[i - 1];
}
```
After the fix the same call gives `{10, 20, 25, 30, 40}` (test T1 and Trace 1). Deletion works in the opposite direction: it shifts forwards (left), which is safe because each element is copied into a slot that was already freed.
---
Reflection
1. What is the difference between an array's capacity and its logical size, and why does the program keep them separate?
The capacity (`CAP = 8`) is the number of slots allocated in memory and it never changes. The logical size (`size`) is the number of slots that currently hold valid data. Only indices 0 to `size − 1` are active. They must be kept separate because the array can be partly filled: `size` tells the functions where the data ends and where the next append goes, while `CAP` tells them when the array is full. If they were mixed up, the program might treat unused slots as real data, or it might not notice that the array is full and write outside it.
2. Why does insertion shift elements from the end but deletion shift from the deleted position, and what is the cost?
Insertion makes a gap by moving elements one place to the right. This must start with the last active element, otherwise the next element is overwritten before it is copied (my bug above). Deletion closes a gap by moving elements one place to the left, which starts at the deleted position and stops at `size − 2`, so nothing beyond the final active element is read. Both may move almost all n elements, so the worst case is O(n) time with O(1) extra space. This is the main disadvantage of arrays: inserting or deleting at the end is O(1), but near the front it is O(n).
3. Why must a failed insertion or deletion leave the array and `size` unchanged, and why is a successful compile not enough to show correctness?
A caller must be able to rely on the array staying valid after an error. If a function changed `size` or shifted elements before discovering that the position was invalid, the data would be corrupted without any warning. Writing at an index outside the array (for example inserting into a full array) is undefined behaviour and can overwrite other memory. For this reason both functions check all conditions first and return `false` before touching anything. Compiling only shows that the syntax and types are correct; it does not show that boundary cases work. That is why I tested valid operations, invalid positions, a full array, an empty array and repeated updates.
