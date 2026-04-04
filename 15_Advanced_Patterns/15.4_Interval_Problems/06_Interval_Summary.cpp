// 15.4 - Interval Problems Summary
// Complete reference for all interval problem patterns.

#include <iostream>
#include <vector>

using namespace std;

// ============================================================
// INTERVAL STRUCT
// ============================================================

struct Interval {
    int start, end;
};

void printInterval(Interval iv) {
    cout << "[" << iv.start << "," << iv.end << "]";
}

// ============================================================
// PATTERN SUMMARY
// ============================================================

void demoPatternSummary() {
    cout << "=== INTERVAL PROBLEMS PATTERN SUMMARY ===" << endl;
    cout << endl;
    cout << "CORE IDEA:" << endl;
    cout << "  Intervals [start, end] represent ranges on a timeline." << endl;
    cout << "  Key technique: sort, then process with greedy or two-pointer logic." << endl;
    cout << endl;
    cout << "OVERLAP CONDITION (assuming a.start <= b.start):" << endl;
    cout << "  Intervals overlap if b.start <= a.end" << endl;
    cout << "  Merged interval: [a.start, max(a.end, b.end)]" << endl;
    cout << endl;
}

// ============================================================
// SORTING STRATEGIES
// ============================================================

void demoSortingStrategies() {
    cout << "=== SORTING STRATEGIES ===" << endl;
    cout << endl;
    cout << "Sort by START time:" << endl;
    cout << "  Used for: Merge Intervals, Insert Interval, Meeting Rooms I" << endl;
    cout << "  After sorting, process left to right" << endl;
    cout << endl;
    cout << "Sort by END time:" << endl;
    cout << "  Used for: Non-overlapping intervals (activity selection)" << endl;
    cout << "  Greedy: pick earliest-ending interval first" << endl;
    cout << endl;
    cout << "Sort start/end arrays independently:" << endl;
    cout << "  Used for: Meeting Rooms II (timeline sweep)" << endl;
    cout << "  Walk through starts and ends to count concurrent events" << endl;
    cout << endl;
}

// ============================================================
// PROBLEM CATALOG
// ============================================================

void demoProblemCatalog() {
    cout << "=== PROBLEM CATALOG ===" << endl;
    cout << endl;
    cout << "1. Merge Intervals (LeetCode 56)" << endl;
    cout << "   Sort by start, merge overlapping" << endl;
    cout << "   Pattern: for each interval, extend last or add new" << endl;
    cout << "   Time: O(n log n)" << endl;
    cout << endl;
    cout << "2. Insert Interval (LeetCode 57)" << endl;
    cout << "   Three phases: before, merge, after" << endl;
    cout << "   Time: O(n)" << endl;
    cout << endl;
    cout << "3. Non-Overlapping Intervals (LeetCode 435)" << endl;
    cout << "   Sort by end time, greedy: keep earliest-ending" << endl;
    cout << "   Min removals = total - max non-overlapping" << endl;
    cout << endl;
    cout << "4. Meeting Rooms I (LeetCode 252)" << endl;
    cout << "   Sort by start, check adjacent for overlap" << endl;
    cout << "   Time: O(n log n)" << endl;
    cout << endl;
    cout << "5. Meeting Rooms II (LeetCode 253)" << endl;
    cout << "   Approach A: Timeline sweep (separate start/end arrays)" << endl;
    cout << "   Approach B: Min-heap of end times" << endl;
    cout << endl;
    cout << "6. Interval Intersection (LeetCode 986)" << endl;
    cout << "   Two pointers on two sorted interval lists" << endl;
    cout << "   Intersection: [max(a.start,b.start), min(a.end,b.end)]" << endl;
    cout << "   Advance pointer with smaller end time" << endl;
    cout << endl;
    cout << "7. Employee Free Time (LeetCode 759)" << endl;
    cout << "   Flatten all intervals, merge, gaps = free time" << endl;
    cout << endl;
}

// ============================================================
// KEY PATTERNS
// ============================================================

void demoKeyPatterns() {
    cout << "=== KEY PATTERNS ===" << endl;
    cout << endl;
    cout << "MERGE PATTERN:" << endl;
    cout << "  merged.push_back(intervals[0]);" << endl;
    cout << "  for each interval:" << endl;
    cout << "    if interval.start <= merged.back().end:" << endl;
    cout << "      merged.back().end = max(merged.back().end, interval.end)" << endl;
    cout << "    else: merged.push_back(interval)" << endl;
    cout << endl;
    cout << "GREEDY INTERVAL SELECTION:" << endl;
    cout << "  Sort by end time" << endl;
    cout << "  Keep first interval" << endl;
    cout << "  For each subsequent: if start >= lastEnd -> keep it" << endl;
    cout << endl;
    cout << "TIMELINE SWEEP:" << endl;
    cout << "  Separate starts and ends into two arrays" << endl;
    cout << "  Sort both" << endl;
    cout << "  Walk through: if start < end -> increment counter" << endl;
    cout << "                else -> decrement counter" << endl;
    cout << "  Max counter value = peak concurrency" << endl;
    cout << endl;
}

// ============================================================
// COMMON MISTAKES
// ============================================================

void demoCommonMistakes() {
    cout << "=== COMMON MISTAKES ===" << endl;
    cout << endl;
    cout << "1. Forgetting to sort before processing" << endl;
    cout << "2. Using wrong sort key (start vs end)" << endl;
    cout << "3. Off-by-one in overlap check: <= vs <" << endl;
    cout << "   - [1,5] and [5,10]: overlap if inclusive (touch at 5)" << endl;
    cout << "   - No overlap if half-open [start, end)" << endl;
    cout << "4. Not handling empty input" << endl;
    cout << "5. Modifying input when it should be const" << endl;
    cout << endl;
}

// ============================================================
// INTERVAL INTERSECTION (bonus)
// ============================================================

void demoIntersection() {
    cout << "=== Bonus: Interval Intersection ===" << endl;
    Interval A[] = {{0, 2}, {5, 10}, {13, 23}};
    Interval B[] = {{1, 5}, {8, 12}, {15, 24}};
    int nA = 3, nB = 3;

    cout << "A: ";
    for (int i = 0; i < nA; i++) { printInterval(A[i]); cout << " "; }
    cout << endl;

    cout << "B: ";
    for (int i = 0; i < nB; i++) { printInterval(B[i]); cout << " "; }
    cout << endl;

    // Two pointers
    int i = 0, j = 0;
    cout << "Intersection: ";
    while (i < nA && j < nB) {
        int start = (A[i].start > B[j].start) ? A[i].start : B[j].start;
        int end = (A[i].end < B[j].end) ? A[i].end : B[j].end;
        if (start <= end) {
            cout << "[" << start << "," << end << "] ";
        }
        // Advance pointer with smaller end
        if (A[i].end < B[j].end) i++;
        else j++;
    }
    cout << endl;
    cout << "Expected: [1,2] [5,5] [8,10] [15,23]" << endl;
    cout << endl;
}

int main() {
    demoPatternSummary();
    demoSortingStrategies();
    demoProblemCatalog();
    demoKeyPatterns();
    demoCommonMistakes();
    demoIntersection();
    return 0;
}
