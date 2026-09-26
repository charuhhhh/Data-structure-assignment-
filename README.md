# Assignment 5 — Organisational Hierarchy: Tree Construction, Traversal & Search Comparison

## Problem Statement
A company has the hierarchy:
```
CEO → HR, Finance, IT
IT → Development, Testing
Development → Frontend, Backend
```
Tasks:
- (a) Represent the hierarchy as a tree; display it using level-order traversal.
- (b) Store department names in a searchable structure; compare Linear Search vs Binary Search.
- (c) Analyse tree height, traversal behaviour, search comparisons, and time complexity.

---

## Part (a): Tree Construction & Level-Order Traversal

### Data Structure Used
A **general (N-ary) tree**, where each node holds an array of child pointers, since departments have a variable number of sub-departments (CEO has 3 children, IT has 2, Development has 2, leaf departments have 0).

### Tree Shape
```
                     CEO                        (Level 0)
          ┌───────────┼────────────┐
          HR       Finance         IT            (Level 1)
                                    │
                          ┌─────────┴────────┐
                     Development          Testing (Level 2)
                          │
                   ┌──────┴──────┐
               Frontend       Backend             (Level 3)
```

### Traversal Method
**Level-Order Traversal (Breadth-First Search)** using a FIFO queue:
1. Enqueue the root.
2. While the queue is non-empty: dequeue a node, print it, enqueue all its children.
3. A level-size snapshot (`rear - front`) is taken at the start of each level so nodes print grouped by level.

### Program Output
```
Tree constructed successfully with 8 nodes.

--- Level-Order Traversal (Hierarchy Display) ---
Level 0: CEO
Level 1: HR, Finance, IT
Level 2: Development, Testing
Level 3: Frontend, Backend

--- Structural Analysis ---
Height of tree (root = level 0): 3
Total number of departments (nodes): 8
```

### Trace Table — Level-Order Traversal (Queue Contents)

| Step | Action                     | Node Processed | Queue After Step (front→rear) | Output So Far                  |
|------|-----------------------------|-----------------|--------------------------------|---------------------------------|
| 1    | Enqueue root                | —               | CEO                            | —                                |
| 2    | Dequeue, enqueue children   | CEO             | HR, Finance, IT                | CEO                              |
| 3    | Dequeue, enqueue children   | HR              | Finance, IT                    | CEO, HR                          |
| 4    | Dequeue, enqueue children   | Finance         | IT                              | CEO, HR, Finance                 |
| 5    | Dequeue, enqueue children   | IT              | Development, Testing           | CEO, HR, Finance, IT             |
| 6    | Dequeue, enqueue children   | Development     | Testing, Frontend, Backend     | ... , Development                |
| 7    | Dequeue, enqueue children   | Testing         | Frontend, Backend              | ... , Testing                    |
| 8    | Dequeue (leaf)              | Frontend        | Backend                        | ... , Frontend                   |
| 9    | Dequeue (leaf)              | Backend         | (empty)                        | ... , Backend                    |
| 10   | Queue empty → stop          | —               | —                               | Traversal complete (8 nodes)     |

---

## Part (b): Searchable Representation & Search Comparison

### Data Structure Used
Department names stored in a **sorted array of strings** (`char[8][30]`), sorted alphabetically — this is required as a **precondition for Binary Search**; Linear Search works on it regardless of order.

Sorted array: `Backend, CEO, Development, Finance, Frontend, HR, IT, Testing`

### Program Output
```
Searching for: "HR"
  Linear Search : FOUND (index 5) | Comparisons = 6
  Binary Search : FOUND (index 5) | Comparisons = 2

Searching for: "Backend"
  Linear Search : FOUND (index 0) | Comparisons = 1
  Binary Search : FOUND (index 0) | Comparisons = 3

Searching for: "Testing"
  Linear Search : FOUND (index 7) | Comparisons = 8
  Binary Search : FOUND (index 7) | Comparisons = 4

Searching for: "Marketing"
  Linear Search : NOT FOUND (index -1) | Comparisons = 8
  Binary Search : NOT FOUND (index -1) | Comparisons = 4
```

### Trace Table — Binary Search for "HR" (array indices 0–7)

| Step | low | high | mid | arr[mid]     | Comparison Result   | Action           |
|------|-----|------|-----|--------------|----------------------|------------------|
| 1    | 0   | 7    | 3   | Finance      | Finance < HR         | low = mid+1 = 4  |
| 2    | 4   | 7    | 5   | HR           | Match found          | return index 5   |

**Total comparisons = 2**

### Trace Table — Linear Search for "HR"

| Step | i | arr[i]      | Comparison Result | Action       |
|------|---|-------------|--------------------|--------------|
| 1    | 0 | Backend     | ≠ HR               | continue     |
| 2    | 1 | CEO         | ≠ HR               | continue     |
| 3    | 2 | Development | ≠ HR               | continue     |
| 4    | 3 | Finance     | ≠ HR               | continue     |
| 5    | 4 | Frontend    | ≠ HR               | continue     |
| 6    | 5 | HR          | Match found        | return index 5 |

**Total comparisons = 6**

### Search Comparison Summary Table

| Search Key   | Result     | Linear Search Comparisons | Binary Search Comparisons |
|--------------|------------|----------------------------|-----------------------------|
| HR           | Found      | 6                           | 2                            |
| Backend      | Found      | 1                           | 3                            |
| Testing      | Found      | 8                           | 4                            |
| Marketing    | Not Found  | 8                           | 4                            |

**Observation:** Linear Search is cheapest only when the target is near the start of the array (e.g., "Backend" — 1 comparison), but degrades badly for elements near the end or absent (up to 8 comparisons). Binary Search stays bounded at ⌈log₂ 8⌉ = 3–4 comparisons regardless of the key's position, making it far more consistent and scalable.

---

## Part (c): Analysis

### 1. Tree Height
- Height = 3 (root at level 0, deepest leaves — Frontend/Backend — at level 3).
- Height reflects the depth of organisational reporting lines; a shallow, wide tree (as here) is efficient to traverse and search top-down.

### 2. Traversal Behaviour
- **Level-order (BFS)** naturally mirrors an organisational chart — it prints the hierarchy exactly rank-by-rank (CEO, then direct reports, then their reports, etc.), which is exactly how reporting structures are usually visualised.
- It requires a queue and visits every node exactly once: O(n) time, O(w) auxiliary space, where w = maximum width of the tree (here, 3, at Level 1).

### 3. Search Comparisons
- Linear Search comparisons grow linearly with the position of the key (1 to n).
- Binary Search comparisons grow logarithmically and never exceed ⌈log₂ n⌉ + 1 (here, at most 4 for n = 8).
- Binary Search's advantage grows sharply as the number of departments increases (e.g., for n = 1000, worst case is ~10 comparisons for Binary Search vs up to 1000 for Linear Search).

### 4. Time and Space Complexity

| Operation                          | Time Complexity        | Space Complexity |
|-------------------------------------|--------------------------|--------------------|
| Tree construction (n nodes)         | O(n)                      | O(n)                |
| Level-order traversal               | O(n)                      | O(w) — w = max width (queue storage) |
| Linear Search                       | Best: O(1), Worst/Avg: O(n) | O(1)              |
| Binary Search (on sorted array)     | Best: O(1), Worst/Avg: O(log n) | O(1) iterative / O(log n) recursive |
| Sorting the array (prerequisite for Binary Search) | O(n log n) (one-time cost) | O(1)–O(n) depending on algorithm |

---

## Conclusion

- The **general tree with level-order (BFS) traversal** is a natural and efficient representation for organisational hierarchies: it captures parent-child reporting relationships directly and displays them rank-by-rank in O(n) time, matching how org charts are read in practice.
- For **department searching**, **Binary Search on a sorted array is the more suitable approach** whenever the department list is largely static (departments don't change every second) and lookups are frequent, since it guarantees O(log n) comparisons versus Linear Search's O(n). Linear Search is only preferable for very small, unsorted, or frequently-changing datasets where the overhead of keeping the array sorted (O(n log n) per re-sort, or O(n) per insertion into a sorted array) outweighs its search-time benefit.
- **Overall suitability:** the tree (for structure/hierarchy display) combined with a sorted array + Binary Search (for fast lookups) together form a suitable and efficient dual representation for organisational reporting and department searching, at the modest, one-time cost of keeping the search array sorted.
