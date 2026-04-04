/*
 * Interval Merging
 *
 * Given a collection of intervals, merge all overlapping
 * intervals into non-overlapping ones.
 *
 * Greedy Strategy:
 *   1. Sort intervals by start time (ascending).
 *   2. Start with the first interval as "current merged interval."
 *   3. For each next interval:
 *      a. If it overlaps with current (start <= current.end),
 *         merge by extending current.end = max(current.end, interval.end).
 *      b. If it does NOT overlap, save current and start a new merged interval.
 *
 * Time  : O(n log n)  for sorting
 * Space : O(1)        beyond input and output storage
 *
 * Why greedy works:
 *   After sorting by start time, if the current interval overlaps
 *   with the next one, they MUST be merged. There is no benefit
 *   in keeping them separate. If they don't overlap, they are
 *   already in the correct separate state.
 */

#include <iostream>

struct Interval {
    int start;
    int end;
    int id;  /* original ID for display */
};

/* Swap two intervals */
void swapIntervals(Interval &a, Interval &b) {
    Interval temp = a;
    a = b;
    b = temp;
}

/* Sort intervals by start time ascending */
void sortByStart(Interval arr[], int n) {
    int i = 0;
    while (i < n) {
        int j = 0;
        while (j < n - i - 1) {
            if (arr[j].start > arr[j + 1].start) {
                swapIntervals(arr[j], arr[j + 1]);
            }
            j = j + 1;
        }
        i = i + 1;
    }
}

/* Merge overlapping intervals, returns count of merged intervals */
int mergeIntervals(Interval intervals[], int n, Interval result[]) {
    if (n <= 0) {
        return 0;
    }

    /* Step 1: Sort by start time */
    sortByStart(intervals, n);

    /* Step 2: Greedily merge */
    int count = 0;  /* number of merged intervals */

    /* Initialize the first merged interval */
    int mergedStart = intervals[0].start;
    int mergedEnd = intervals[0].end;

    int i = 1;
    while (i < n) {
        if (intervals[i].start <= mergedEnd) {
            /* Overlapping: extend the current merged interval */
            if (intervals[i].end > mergedEnd) {
                mergedEnd = intervals[i].end;
            }
        } else {
            /* No overlap: save current and start new merged interval */
            result[count].start = mergedStart;
            result[count].end = mergedEnd;
            result[count].id = -1;  /* merged, no original ID */
            count = count + 1;

            mergedStart = intervals[i].start;
            mergedEnd = intervals[i].end;
        }
        i = i + 1;
    }

    /* Save the last merged interval */
    result[count].start = mergedStart;
    result[count].end = mergedEnd;
    result[count].id = -1;
    count = count + 1;

    return count;
}

int main() {
    int n = 6;
    Interval intervals[6];
    intervals[0].start = 1;  intervals[0].end = 3;  intervals[0].id = 1;
    intervals[1].start = 2;  intervals[1].end = 6;  intervals[1].id = 2;
    intervals[2].start = 8;  intervals[2].end = 10; intervals[2].id = 3;
    intervals[3].start = 15; intervals[3].end = 18; intervals[3].id = 4;
    intervals[4].start = 5;  intervals[4].end = 9;  intervals[4].id = 5;
    intervals[5].start = 7;  intervals[5].end = 12; intervals[5].id = 6;

    std::cout << "=== Interval Merging ===" << std::endl;
    std::cout << std::endl;
    std::cout << "Input intervals:" << std::endl;

    int i = 0;
    while (i < n) {
        std::cout << "  [" << intervals[i].start
                  << ", " << intervals[i].end << "]" << std::endl;
        i = i + 1;
    }

    std::cout << std::endl;

    /* Perform merge */
    Interval result[10];
    int mergedCount = mergeIntervals(intervals, n, result);

    std::cout << "After sorting by start time:" << std::endl;
    i = 0;
    while (i < n) {
        std::cout << "  [" << intervals[i].start
                  << ", " << intervals[i].end << "]" << std::endl;
        i = i + 1;
    }

    std::cout << std::endl;
    std::cout << "Merged intervals (" << mergedCount << "):" << std::endl;

    i = 0;
    while (i < mergedCount) {
        std::cout << "  [" << result[i].start
                  << ", " << result[i].end << "]" << std::endl;
        i = i + 1;
    }

    std::cout << std::endl;
    std::cout << "How merging worked:" << std::endl;
    std::cout << "  [1,3] and [2,6] -> overlap (2 <= 3) -> merge to [1,6]" << std::endl;
    std::cout << "  [1,6] and [5,9] -> overlap (5 <= 6) -> merge to [1,9]" << std::endl;
    std::cout << "  [1,9] and [7,12] -> overlap (7 <= 9) -> merge to [1,12]" << std::endl;
    std::cout << "  [1,12] and [8,10] -> overlap (8 <= 12) -> merge to [1,12] (no change)" << std::endl;
    std::cout << "  [1,12] and [15,18] -> NO overlap (15 > 12) -> save [1,12], start [15,18]" << std::endl;
    std::cout << "  Result: [1,12], [15,18]" << std::endl;

    std::cout << std::endl;
    std::cout << "Why greedy works:" << std::endl;
    std::cout << "  After sorting by start time, overlapping intervals" << std::endl;
    std::cout << "  are adjacent. If two intervals overlap, they MUST be" << std::endl;
    std::cout << "  merged - there is no reason to keep them separate." << std::endl;

    return 0;
}
