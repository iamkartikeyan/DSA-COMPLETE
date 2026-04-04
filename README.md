# 🚀 DSA-COMPLETE — Complete Data Structures & Algorithms in C++

> **Master Data Structures & Algorithms from scratch to advanced — one topic at a time, one file at a time.**

---

## 📖 About This Repository

This is a **complete, hand-curated** DSA learning resource written in **simple, beginner-friendly C++**. Every concept is split into **small, focused files** (never 300+ line monoliths) so you can understand, compile, and run each topic independently.

**✨ What makes this different?**
- 🔹 **Every topic is its own file** — no massive files to scroll through
- 🔹 **Basic C++ only** — no `auto`, no lambdas, no `nullptr`, no `<bits/stdc++.h>` — just clean, readable code
- 🔹 **Each file compiles standalone** — `g++ filename.cpp -o out && ./out`
- 🔹 **Every concept explained with comments** — no topic left behind
- 🔹 **Summary file in every folder** — quick reference before interviews

---

## 📂 Complete Folder Structure

```
DSA/
├── 01_Programming_Fundamentals/
│   ├── 1.1_Language_Basics/
│   ├── 1.2_Memory_and_Pointers/
│   └── 1.3_Recursion_Fundamentals/
│
├── 02_Complexity_Analysis/
│   ├── 2.1_Time_Complexity/          (6 files)
│   ├── 2.2_Space_Complexity/          (5 files)
│   └── 2.3_Amortized_Analysis/        (5 files)
│
├── 03_Basic_Data_Structures/
│   ├── 3.1_Arrays/                    (5 files)
│   ├── 3.2_Strings/                   (5 files)
│   ├── 3.3_Linked_Lists/              (5 files)
│   ├── 3.4_Stacks/                    (5 files)
│   └── 3.5_Queues/                    (5 files)
│
├── 04_Sorting_and_Searching/
│   ├── 4.1_Searching/                 (7 files)
│   ├── 4.2_Sorting_Comparison/        (7 files)
│   ├── 4.3_Sorting_NonComparison/     (4 files)
│   └── 4.4_Advanced_Search/           (5 files)
│
├── 05_Hashing/
│   ├── 5.1_Hash_Tables/               (4 files)
│   ├── 5.2_Hash_Based_Structures/     (8 files)
│   └── 5.3_Advanced_Hashing/          (5 files)
│
├── 06_Trees/
│   ├── 6.1_Binary_Trees/              (7 files)
│   ├── 6.2_Binary_Search_Trees/       (9 files)
│   ├── 6.3_Balanced_BSTs/             (6 files)
│   ├── 6.4_Heaps/                     (9 files)
│   └── 6.5_Advanced_Trees/            (6 files)
│
├── 07_Graphs/
│   ├── 7.1_Graph_Fundamentals/        (5 files)
│   ├── 7.2_Graph_Traversals/          (8 files)
│   ├── 7.3_Shortest_Path/             (6 files)
│   ├── 7.4_Minimum_Spanning_Tree/     (4 files)
│   └── 7.5_Advanced_Graphs/           (7 files)
│
├── 08_Dynamic_Programming/
│   ├── 8.1_DP_Foundations/            (6 files)
│   ├── 8.2_Classic_DP_Patterns/       (6 files)
│   ├── 8.3_Advanced_DP_Patterns/      (5 files)
│   └── 8.4_DP_Optimization/           (3 files)
│
├── 09_Greedy_Algorithms/
│   ├── 9.1_Greedy_Fundamentals/       (5 files)
│   └── 9.2_Classic_Greedy/            (6 files)
│
├── 10_Divide_and_Conquer/
│   ├── 10.1_DC_Framework/             (6 files)
│   └── 10.2_DC_Applications/          (6 files)
│
├── 11_Backtracking/
│   ├── 11.1_Backtracking_Fundamentals/(6 files)
│   └── 11.2_Classic_Problems/         (6 files)
│
├── 12_Bit_Manipulation/
│   ├── 12.1_Bitwise_Operators/        (5 files)
│   └── 12.2_Bit_Applications/         (7 files)
│
├── 13_Two_Pointers_Sliding_Window/
│   ├── 13.1_Two_Pointers/             (8 files)
│   └── 13.2_Sliding_Window/           (10 files)
│
├── 14_Prefix_Sum_Difference_Array/
│   ├── 14.1_Prefix_Sum/               (6 files)
│   └── 14.2_Difference_Array/         (7 files)
│
├── 15_Advanced_Patterns/
│   ├── 15.1_Monotonic_Stack_queue/    (7 files)
│   ├── 15.2_Union_Find/               (6 files)
│   ├── 15.3_TopK_Elements/            (5 files)
│   ├── 15.4_Interval_Problems/        (6 files)
│   └── 15.5_Matrix_Patterns/          (5 files)
│
├── 16_Mathematics_for_DSA/
│   ├── 16.1_Number_Theory/            (6 files)
│   ├── 16.2_Combinatorics/            (4 files)
│   ├── 16.3_Geometry_Basics/          (4 files)
│   └── 16.4_Probability_Statistics/   (4 files)
│
├── 17_Design_Based_Problems/
│   ├── 17.1_DS_Design/                (5 files)
│   └── 17.2_System_Design_Basics/     (5 files)
│
└── 18_Miscellaneous_Advanced/
    ├── 18.1_Advanced_DS/              (4 files)
    ├── 18.2_String_Algorithms/        (4 files)
    └── 18.3_Computational_Geometry/   (4 files)
```

---

## 🗺️ Detailed Topic List

### 01 — Programming Fundamentals
Variables, data types, operators, control flow, functions, scope, pointers, references, dynamic memory, stack vs heap, recursion basics.

### 02 — Complexity Analysis
- **Time Complexity**: Big O, all common complexities, loop analysis, recursive complexity, best/avg/worst case
- **Space Complexity**: Auxiliary vs input space, in-place vs extra space, recursion stack
- **Amortized Analysis**: Aggregate method, accounting method, potential method, dynamic array resizing

### 03 — Basic Data Structures
- **Arrays**: 1D, 2D, 3D, operations, vector (dynamic array)
- **Strings**: C-strings, C++ std::string, pattern matching, palindrome, anagram, reverse words
- **Linked Lists**: Singly, Doubly, Circular, cycle detection (Floyd's), reverse
- **Stacks**: Array implementation, parenthesis matching, postfix evaluation, function call stack
- **Queues**: Simple queue, circular queue, deque (double-ended), priority queue

### 04 — Sorting & Searching
- **Searching**: Linear, Binary (iterative + recursive), Ternary, Jump, Interpolation, Exponential
- **Comparison Sorts**: Bubble, Selection, Insertion, Merge, Quick, Heap — all with stability analysis
- **Non-Comparison Sorts**: Counting Sort, Radix Sort, Bucket Sort
- **Advanced Search**: Rotated sorted array, 2D matrix search, peak element, mountain array

### 05 — Hashing
- **Hash Tables**: Chaining, Open Addressing (Linear Probing), load factor, rehashing
- **Hash-Based Structures**: Hash Set, Hash Map, frequency counting, Two Sum, subarray sum problems
- **Advanced Hashing**: Rolling Hash (Rabin-Karp), Double Hashing, Bloom Filter, Consistent Hashing

### 06 — Trees
- **Binary Trees**: Node structure, traversals (inorder, preorder, postorder, level order), tree properties, tree types
- **BST**: Search, insert, delete, min/max, successor/predecessor, validate BST, LCA
- **Balanced BSTs**: AVL (rotations, insert), Red-Black Trees (properties), B-Trees (concepts)
- **Heaps**: Basics, heapify up/down, insert/extract, build heap, heap sort, K-th element, merge K sorted, top K frequent
- **Advanced Trees**: Trie (insert, search, autocomplete), Segment Tree (range sum, update), Fenwick Tree (BIT)

### 07 — Graphs ⭐
- **Fundamentals**: Terminology, Adjacency Matrix, Adjacency List, Edge List, representation comparison
- **Traversals**: BFS, DFS (recursive + iterative), shortest path (unweighted), connected components, cycle detection (directed + undirected)
- **Shortest Path**: Dijkstra (with path reconstruction), Bellman-Ford, negative cycle detection, Floyd-Warshall (all-pairs)
- **MST**: Prim's Algorithm, Kruskal's Algorithm, Union-Find (DSU), MST properties
- **Advanced**: Topological Sort (Kahn's + DFS), Kosaraju's SCC, Articulation Points, Bridges, Bipartite Check

### 08 — Dynamic Programming ⭐
- **Foundations**: What is DP, memoization vs tabulation, Fibonacci, Climbing Stairs, House Robber, Min Coins, LIS, 5-step DP framework
- **Classic Patterns**: Grid paths, 0/1 Knapsack, LCS, Edit Distance, Coin Change (min + ways), Subset Sum, Partition
- **Advanced Patterns**: Palindrome DP, Matrix Chain Multiplication, DP on Trees (diameter, max path sum), Bitmask DP (TSP)
- **Optimization**: Space optimization (O(n²) → O(n)), rolling arrays, iteration direction tricks

### 09 — Greedy Algorithms
- **Fundamentals**: Greedy choice property, optimal substructure, when greedy works vs fails, Activity Selection, Fractional Knapsack, Greedy vs DP comparison
- **Classic Problems**: Huffman Coding, Job Sequencing with Deadlines, Minimum Platforms, Interval Merging, Assign Cookies

### 10 — Divide and Conquer
- **Framework**: D&C paradigm, Master Theorem (all 3 cases), power (x^n), binary search, Fibonacci (bad D&C example)
- **Applications**: Merge Sort, Quick Sort, Closest Pair of Points, Inversion Count, Strassen's Matrix Multiplication concept

### 11 — Backtracking
- **Fundamentals**: Backtracking paradigm (choice-constraint-goal-prune), subset generation, permutations, combinations, combination sum, pruning
- **Classic Problems**: N-Queens, Sudoku Solver, Rat in Maze, Word Search, Palindrome Partitioning

### 12 — Bit Manipulation
- **Operators**: AND, OR, XOR, NOT, Left Shift, Right Shift, bit tricks (n&(n-1), n&(-n))
- **Applications**: Find unique element, find two uniques, missing number, XOR swap, bitmask subsets, advanced tricks (abs without branching, next power of 2)

### 13 — Two Pointers & Sliding Window
- **Two Pointers**: Pair sum, three sum, container with most water, remove duplicates, move zeroes, merge sorted arrays, intersection
- **Sliding Window**: Fixed window (max sum, first negative), variable window (longest subarray sum, longest unique substring, K distinct), Kadane's, minimum window substring, count anagrams

### 14 — Prefix Sum & Difference Array
- **Prefix Sum**: 1D prefix sum, 2D prefix sum (summed area table), subarray sum equals K, Fenwick Tree (BIT)
- **Difference Array**: Basic diff array, flight booking, range addition, car pooling, 2D difference array

### 15 — Advanced Patterns
- **Monotonic Stack/Queue**: Next greater element, previous greater, stock span, largest rectangle in histogram, sliding window maximum
- **Union-Find**: Basic DSU, path compression, union by rank, applications (connected components, cycle detection, Kruskal's)
- **Top K Elements**: Kth largest, Kth smallest, top K frequent (heap, quickselect, bucket sort)
- **Interval Problems**: Merge intervals, insert interval, non-overlapping intervals, minimum meeting rooms
- **Matrix Patterns**: Spiral traversal, matrix search, rotate matrix, island patterns (DFS/BFS)

### 16 — Mathematics for DSA
- **Number Theory**: Sieve of Eratosthenes, GCD (Euclidean), extended GCD, modular arithmetic, prime factorization
- **Combinatorics**: Factorial, permutations (nPr), combinations (nCr), Pascal's triangle, Catalan numbers
- **Geometry Basics**: Point distance, line intersection, polygon area (shoelace formula)
- **Probability & Statistics**: Basic probability, expected value, mean/median/mode

### 17 — Design Based Problems
- **DS Design**: Design Stack, Design Queue, Design Min Stack (O(1) getMin), Design LRU Cache
- **System Design Basics**: Scalability, horizontal vs vertical scaling, load balancing, caching strategies

### 18 — Miscellaneous Advanced
- **Advanced DS**: Trie (delete, autocomplete), Segment Tree (range min query), Sparse Table (RMQ)
- **String Algorithms**: KMP (prefix function), Z-Algorithm, Manacher's (longest palindromic substring)
- **Computational Geometry**: Cross product, convex hull (Graham scan), line segment intersection

---

## 🛠️ How to Use

### Compile & Run Any File
```bash
cd 07_Graphs/7.2_Graph_Traversals
g++ 01_BFS_Traversal.cpp -o bfs && ./bfs
```

### Compile All Files in a Folder
```bash
cd 08_Dynamic_Programming/8.1_DP_Foundations
for f in *.cpp; do g++ "$f" -o "${f%.cpp}" && echo "✅ $f"; done
```

### Recommended Learning Path
1. Read the concept file first (`01_What_Is_*.cpp`)
2. Study the implementation files
3. Run each file to see output
4. Read the summary file for quick revision
5. Move to the next topic

---

## 📊 Statistics

| Metric | Count |
|--------|-------|
| **Major Sections** | 18 |
| **Sub-folders** | 50+ |
| **Total C++ Files** | 350+ |
| **Total Lines of Code** | 30,000+ |
| **Topics Covered** | Every DSA topic for interviews |
| **Language** | Basic C++ (beginner-friendly) |

---

## 🎯 Who Is This For?

- **Students** preparing for placements & campus interviews
- **Competitive Programmers** building a strong DSA foundation
- **Self-learners** who want clean, readable code examples
- **Interview preppers** who need quick revision with summary files
- **Beginners** who are scared by complex C++ code

---

## 📝 C++ Coding Standards Used

All files follow these rules for maximum readability:

| Rule | Applied |
|------|---------|
| No `nullptr` | ✅ Uses `NULL` |
| No range-based for loops | ✅ Index-based `for` loops |
| No `<bits/stdc++.h>` | ✅ Specific headers (`<iostream>`, `<vector>`, etc.) |
| No `auto` keyword | ✅ Explicit types |
| No lambdas | ✅ Named functions |
| No structured bindings | ✅ Simple variables |
| No ternary in complex expressions | ✅ Simple `if-else` |
| Standalone compilable | ✅ Every file has `main()` |

---

## 🔒 Copyright & License

```
Copyright © 2025 Kartikeyan Sahani. All Rights Reserved.

This repository and all its contents are the exclusive intellectual 
property of Kartikeyan Sahani.

RESTRICTIONS:
1. No part of this repository may be copied, reproduced, distributed, 
   or transmitted in any form without explicit prior written permission.
2. Creating derivative works, forks for public use, or repackaging 
   this content in any form is STRICTLY PROHIBITED.
3. Using this code for commercial purposes, tutorials, courses, 
   books, or any monetized content is STRICTLY PROHIBITED.
4. Plagiarism of this content — in whole or in part — is a violation 
   of intellectual property rights and will be pursued legally.

PERMITTED:
- Personal learning and study
- Private, non-public reference

For licensing inquiries, contact: iamkartikeyan

All violations will be reported under applicable intellectual 
property laws.
```

---

## ⭐ If You Found This Helpful

Consider giving this repository a ⭐ star — it helps others discover it!

---

> **Built with ❤️ for the DSA community — one file at a time.**
