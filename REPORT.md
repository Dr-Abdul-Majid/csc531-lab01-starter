# CSC-531 Lab 01 — Student Report

**Roll No.:*19*  
**Student name:*Abdullah Shams*  
**Section (A/B):*A*  
**GitHub username:*abdullahshams12*  

## 1. Aim and input assumptions

In this lab, we implemented basic static array operations in C++: displaying active elements, inserting an element at a given index, and deleting an element from a given index.

**Relationship among capacity, logical size, and active indices:**
- **Capacity (`cap`):** The total fixed size of the array in memory (`cap = 8`).
- **Logical size (`size`):** How many valid items are currently stored in the array (`0 <= size <= cap`).
- **Active indices:** Valid elements are stored from index `0` to `size - 1`. Indices from `size` to `cap - 1` are empty/unused slots. If `size == 0`, the list is empty. If `size == cap`, the list is full.

## 2. Task A — Array diagram and address calculations

**8 slots with logical size 4:**

```text
Index:     0     1     2     3     4     5     6     7
        +-----+-----+-----+-----+-----+-----+-----+-----+
Array:  | 70  | 80  | 90  | 85  |     |     |     |     |
        +-----+-----+-----+-----+-----+-----+-----+-----+
         <--- Active items --->  <----- Free slots ----->
                                  ^
                        Next append index = 4
```

**1D address worksheet:**  
Formula: `Address(A[i]) = B + i * w` (with `B = 4000`, `w = 4`)
- `A[0] = 4000 + 0 * 4 = 4000`
- `A[3] = 4000 + 3 * 4 = 4012`
- `A[7] = 4000 + 7 * 4 = 4028`

**2D row-major worksheet:**  
Given `M[4][5]`, `B = 2000`, `w = 4` (number of columns `C = 5`):
- **Linear offset for `M[2][3]`:** `(2 * 5) + 3 = 10 + 3 = 13`
- **Address calculation:** `2000 + (13 * 4) = 2000 + 52 = 2052`
- **Why multiply by element width:** Memory addresses count individual bytes, while each integer takes `4` bytes. Multiplying the offset (`13`) by `w` (`4`) gives the exact number of bytes to skip from the base address.

## 3. Task B — Insertion/deletion trace

**1. Inserting `75` at index `2` (initial: `[70, 80, 90, 85]`, `size = 4`, `capacity = 8`):**
- Shift 1: `a[3]` (`85`) moves to `a[4]` -> `[70, 80, 90, 85, 85]`
- Shift 2: `a[2]` (`90`) moves to `a[3]` -> `[70, 80, 90, 90, 85]`
- Insert `75` at `a[2]` -> `[70, 80, 75, 90, 85]`
- Final logical size: `5`

**2. Deleting element at index `1` from `[70, 80, 75, 90, 85]` (`size = 5`):**
- Index `2` (`75`) shifts left to index `1` -> `[70, 75, 75, 90, 85]`
- Index `3` (`90`) shifts left to index `2` -> `[70, 75, 90, 90, 85]`
- Index `4` (`85`) shifts left to index `3` -> `[70, 75, 90, 85, 85]`
- Resulting active values: `[70, 75, 90, 85]` (`size = 4`)

## 4. Task C — Menu demonstration

**How to use the four menu options:**
1. **Display:** Prints the active array elements from `0` to `size - 1` and shows the current logical size.
2. **Insert:** Asks for a position (`0` to `size`) and a value, then inserts it if the array is not full.
3. **Delete:** Asks for a position (`0` to `size - 1`) and removes that element if the array is not empty.
4. **Exit:** Closes the program.

**Sample input/output log:**
```text
=== CSC-531 Lab 01: Static Array Operations ===
Active values (size = 4/8): [70, 80, 90, 85]

Enter choice (1-4): 2
Enter insertion position (0 to 4): 2
Enter integer value to insert: 75
Success: Inserted 75 at index 2.
Active values (size = 5/8): [70, 80, 75, 90, 85]

Enter choice (1-4): 3
Enter deletion position (0 to 4): 1
Success: Deleted element at index 1.
Active values (size = 4/8): [70, 75, 90, 85]

Enter choice (1-4): 2
Enter insertion position (0 to 4): 4
Enter integer value to insert: 10
Success: Inserted 10 at index 4.
Active values (size = 5/8): [70, 75, 90, 85, 10]

Enter choice (1-4): 2
Enter insertion position (0 to 5): 5
Enter integer value to insert: 20
Success: Inserted 20 at index 5.
Active values (size = 6/8): [70, 75, 90, 85, 10, 20]

Enter choice (1-4): 2
Enter insertion position (0 to 6): 6
Enter integer value to insert: 30
Success: Inserted 30 at index 6.
Active values (size = 7/8): [70, 75, 90, 85, 10, 20, 30]

Enter choice (1-4): 2
Enter insertion position (0 to 7): 7
Enter integer value to insert: 40
Success: Inserted 40 at index 7.
Active values (size = 8/8): [70, 75, 90, 85, 10, 20, 30, 40]

Enter choice (1-4): 2
Enter insertion position (0 to 8): 0
Enter integer value to insert: 99
Failure: Cannot insert. Array is at full capacity (8).

Enter choice (1-4): 3
Enter deletion position (0 to 7): 0
Success: Deleted element at index 0.
Active values (size = 7/8): [75, 90, 85, 10, 20, 30, 40]
... (deleted remaining elements until size = 0) ...

Enter choice (1-4): 3
Enter deletion position (0 to 0): 0
Failure: Cannot delete. Array is already empty (size = 0).

Enter choice (1-4): 4
Exiting program. Goodbye!
```

## 5. Validation test table

| Test case | Initial state / input | Expected result | Actual result | Pass/Fail |
|---|---|---|---|---|
| Insert in middle | `[70, 80, 90, 85]`, insert `75` at `pos=2` | Returns `true`, `[70, 80, 75, 90, 85]`, `size=5` | Returns `true`, `[70, 80, 75, 90, 85]`, `size=5` | Pass |
| Delete first | `[70, 75, 90, 85]`, delete `pos=0` | Returns `true`, `[75, 90, 85]`, `size=3` | Returns `true`, `[75, 90, 85]`, `size=3` | Pass |
| Delete middle | `[70, 80, 75, 90, 85]`, delete `pos=1` | Returns `true`, `[70, 75, 90, 85]`, `size=4` | Returns `true`, `[70, 75, 90, 85]`, `size=4` | Pass |
| Delete last | `[75, 90, 85]`, delete `pos=2` | Returns `true`, `[75, 90]`, `size=2` | Returns `true`, `[75, 90]`, `size=2` | Pass |
| Insert when full | 8 elements (`size=8`), insert `99` at `pos=0` | Returns `false`, rejected, `size=8` | Returns `false`, rejected, `size=8` | Pass |
| Delete when empty | `[]` (`size=0`), delete `pos=0` | Returns `false`, rejected, `size=0` | Returns `false`, rejected, `size=0` | Pass |
| Invalid negative index | `[70, 80, 90, 85]`, insert/delete `pos=-1` | Returns `false`, rejected | Returns `false`, rejected | Pass |
| Invalid index == size | `[70, 80, 90, 85]`, delete `pos=4` | Returns `false`, rejected | Returns `false`, rejected | Pass |
| Append at end (`pos == size`) | `[70, 80, 90, 85]`, insert `50` at `pos=4` | Returns `true`, `[70, 80, 90, 85, 50]`, `size=5` | Returns `true`, `[70, 80, 90, 85, 50]`, `size=5` | Pass |

## 6. Complexity and limitations

- **Number of shifts:** For `n` active elements and target position `p`, insertion takes `n - p` shifts. Deletion takes `(n - 1) - p` shifts.
- **Worst-case time complexity:** `O(n)` for both insertion and deletion, which happens when `p = 0` (inserting or deleting at the very front requires shifting all elements).
- **Auxiliary space complexity:** `O(1)` because shifting happens in-place inside the existing array without allocating extra memory.
- **Assumptions and restrictions:** The array has a fixed capacity of `8` and cannot grow dynamically. It only stores integers, and indices outside `[0, size - 1]` contain uninitialized/stale values that must not be read.

## 7. Reflection and viva preparation

1. **How many shifts are required to insert at position `p` into an active list of `n` elements?**  
   It requires `n - p` shifts (moving elements from index `n - 1` down to `p` one position to the right).

2. **Why does insertion shift backward while deletion shift forward?**  
   Insertion shifts backward (from right to left) so elements move into free space first without overwriting values that haven't been moved yet. Deletion shifts forward (from left to right) so each element overwrites the deleted slot without erasing elements further down the array.

3. **Which workload favors arrays: frequent indexed access or frequent front insertion? Explain.**  
   Frequent indexed access favors arrays because contiguous memory lets us jump directly to any index in `O(1)` time (`B + i * w`). Frequent front insertion is slow (`O(n)`) because every insert has to shift all existing elements to the right.

**One bug I encountered:**  
In `deleteAt`, I initially wrote `i < size` in the loop condition instead of `i < size - 1`.

**How I detected it:**  
When deleting from a full array (`size = 8`), `a[i + 1]` tried to read `a[8]`, which is out of bounds.

**What I changed:**  
Changed the loop condition to `i < size - 1` so it stops at `size - 2` and never reads `a[size]`.

**External/AI assistance disclosed, if applicable:**  
Used AI assistance to help verify edge-case conditions and format the markdown report table.