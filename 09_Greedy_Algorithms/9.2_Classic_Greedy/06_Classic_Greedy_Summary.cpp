/*
 * Classic Greedy Algorithms - Complete Summary
 *
 * This file provides a comprehensive summary of all classic
 * greedy algorithms covered in this folder.
 */

#include <iostream>

/*
 * ============================================================
 * ALGORITHM SUMMARY
 * ============================================================
 *
 * Algorithm                  | Idea                      | Time     | Space
 * ---------------------------|---------------------------|----------|-------
 * Huffman Coding             | Merge two smallest freq   | O(nlogn) | O(n)
 * Job Sequencing w/ Deadl.   | Sort by profit, latest slot| O(n^2)  | O(n)
 * Minimum Platforms          | Sort arrivals & departures| O(nlogn) | O(1)
 * Interval Merging           | Sort by start, merge if overlap | O(nlogn) | O(1)
 * Assign Cookies             | Sort both, satisfy least greedy first | O(glogs + slogs) | O(1)
 */

/*
 * ============================================================
 * WHEN TO USE EACH ALGORITHM
 * ============================================================
 *
 * 1. HUFFMAN CODING
 *    Use when: Building optimal prefix-free binary codes.
 *    Input   : Characters with frequencies.
 *    Output  : Binary codes where frequent chars get short codes.
 *    Greedy  : Always merge two nodes with smallest frequencies.
 *
 * 2. JOB SEQUENCING WITH DEADLINES
 *    Use when: Scheduling unit-time jobs with deadlines and profits.
 *    Input   : Jobs with deadlines and profits.
 *    Output  : Maximum total profit achievable.
 *    Greedy  : Pick highest-profit jobs, assign to latest free slot.
 *
 * 3. MINIMUM PLATFORMS
 *    Use when: Finding peak simultaneous resource usage.
 *    Input   : Arrival and departure times.
 *    Output  : Minimum resources needed to handle all events.
 *    Greedy  : Sort both arrays, sweep with two pointers.
 *
 * 4. INTERVAL MERGING
 *    Use when: Simplifying overlapping ranges.
 *    Input   : A list of [start, end] intervals.
 *    Output  : Non-overlapping intervals covering the same ranges.
 *    Greedy  : Sort by start, merge overlapping adjacent intervals.
 *
 * 5. ASSIGN COOKIES
 *    Use when: Maximizing matches between two sorted lists.
 *    Input   : Requirements (greed) and resources (cookies).
 *    Output  : Maximum number of satisfied requirements.
 *    Greedy  : Sort both, match smallest resource to smallest requirement.
 */

/*
 * ============================================================
 * COMMON PATTERNS IN GREEDY ALGORITHMS
 * ============================================================
 *
 * Pattern 1: SORT + GREEDY PICK
 *   Sort by some criterion, then greedily pick in order.
 *   Examples: Activity Selection, Fractional Knapsack,
 *             Huffman Coding, Job Sequencing
 *
 * Pattern 2: TWO-POINTER SWEEP
 *   Sort multiple arrays, then sweep with two pointers.
 *   Examples: Minimum Platforms, Assign Cookies
 *
 * Pattern 3: GREEDY MERGE
 *   Sort, then iteratively merge/combine adjacent items.
 *   Examples: Interval Merging, Huffman Coding
 *
 * Pattern 4: GREEDY ASSIGNMENT
 *   Sort both sides, match smallest to smallest.
 *   Examples: Assign Cookies
 */

/*
 * ============================================================
 * HOW TO RECOGNIZE A GREEDY PROBLEM
 * ============================================================
 *
 * Signs that a problem might be solvable with greedy:
 *
 * 1. The problem asks to MAXIMIZE or MINIMIZE something.
 *
 * 2. You can make a LOCAL choice that seems obviously "best"
 *    (e.g., earliest finish, highest ratio, smallest value).
 *
 * 3. Making that choice reduces the problem to a SMALLER
 *    version of itself.
 *
 * 4. The problem does NOT require looking back or revisiting
 *    previous choices.
 *
 * 5. There is no complex trade-off between choices
 *    (or the trade-off has a simple structure like a matroid).
 *
 * IF ALL OF THE ABOVE -> try a greedy approach.
 * IF UNSURE -> test greedy on small examples, compare with
 *              brute force to check correctness.
 */

int main() {
    std::cout << "================================================" << std::endl;
    std::cout << "   CLASSIC GREEDY ALGORITHMS - COMPLETE SUMMARY" << std::endl;
    std::cout << "================================================" << std::endl;

    std::cout << std::endl;
    std::cout << "=== ALGORITHM TABLE ===" << std::endl;
    std::cout << std::endl;
    std::cout << "Algorithm                | Time     | Space | Greedy Choice" << std::endl;
    std::cout << "-------------------------|----------|-------|------------------" << std::endl;
    std::cout << "Huffman Coding           | O(nlogn) | O(n)  | Merge 2 smallest" << std::endl;
    std::cout << "Job Sequencing           | O(n^2)   | O(n)  | Highest profit" << std::endl;
    std::cout << "Minimum Platforms        | O(nlogn) | O(1)  | Sweep sorted events" << std::endl;
    std::cout << "Interval Merging         | O(nlogn) | O(1)  | Merge if overlap" << std::endl;
    std::cout << "Assign Cookies           | O(nlogn) | O(1)  | Satisfy least first" << std::endl;

    std::cout << std::endl;
    std::cout << "=== COMMON PATTERNS ===" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Sort + Greedy Pick:" << std::endl;
    std::cout << "   Activity Selection, Fractional Knapsack," << std::endl;
    std::cout << "   Huffman Coding, Job Sequencing" << std::endl;
    std::cout << std::endl;
    std::cout << "2. Two-Pointer Sweep:" << std::endl;
    std::cout << "   Minimum Platforms, Assign Cookies" << std::endl;
    std::cout << std::endl;
    std::cout << "3. Greedy Merge:" << std::endl;
    std::cout << "   Interval Merging, Huffman Coding" << std::endl;
    std::cout << std::endl;
    std::cout << "4. Greedy Assignment:" << std::endl;
    std::cout << "   Assign Cookies" << std::endl;

    std::cout << std::endl;
    std::cout << "=== FILES IN THIS FOLDER ===" << std::endl;
    std::cout << std::endl;
    std::cout << "9.1_Greedy_Fundamentals:" << std::endl;
    std::cout << "  01_What_Is_Greedy.cpp" << std::endl;
    std::cout << "  02_Activity_Selection.cpp" << std::endl;
    std::cout << "  03_Fractional_Knapsack.cpp" << std::endl;
    std::cout << "  04_Greedy_vs_DP.cpp" << std::endl;
    std::cout << "  05_Greedy_Summary.cpp" << std::endl;
    std::cout << std::endl;
    std::cout << "9.2_Classic_Greedy:" << std::endl;
    std::cout << "  01_Huffman_Coding.cpp" << std::endl;
    std::cout << "  02_Job_Sequencing_Deadlines.cpp" << std::endl;
    std::cout << "  03_Minimum_Platforms.cpp" << std::endl;
    std::cout << "  04_Interval_Merging.cpp" << std::endl;
    std::cout << "  05_Assign_Cookies.cpp" << std::endl;
    std::cout << "  06_Classic_Greedy_Summary.cpp (this file)" << std::endl;

    std::cout << std::endl;
    std::cout << "=== NEXT STEPS ===" << std::endl;
    std::cout << std::endl;
    std::cout << "After mastering these, study:" << std::endl;
    std::cout << "  - Minimum Spanning Tree (Kruskal's and Prim's)" << std::endl;
    std::cout << "  - Dijkstra's Shortest Path Algorithm" << std::endl;
    std::cout << "  - Egyptian Fraction" << std::endl;
    std::cout << "  - Minimum Coin Change (canonical coin systems)" << std::endl;
    std::cout << "  - Greedy on Trees (Tree Diameter, Tree Coloring)" << std::endl;

    return 0;
}
