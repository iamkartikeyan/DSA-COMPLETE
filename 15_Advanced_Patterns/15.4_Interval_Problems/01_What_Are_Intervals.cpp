// 15.4 - What Are Interval Problems?
// An interval is a range [start, end]. Interval problems are common in scheduling,
// calendar management, and resource allocation.
//
// COMMON PATTERNS:
//   1. Sort by start time -> process linearly with merge logic
//   2. Sort by end time -> greedy selection (earliest finish first)
//   3. Separate start/end arrays -> timeline sweep
//   4. Two pointers on sorted interval lists
//
// KEY INSIGHT:
//   Two intervals [a,b] and [c,d] overlap if c <= b (assuming a <= c).
//   They can be merged into [a, max(b, d)].
//
// INTERVAL STRUCT:
//   struct Interval { int start, end; };

#include <iostream>

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
// OVERLAP DETECTION
// ============================================================

void demoOverlapDetection() {
    cout << "=== Overlap Detection ===" << endl;
    cout << endl;

    Interval a = {1, 5};
    Interval b = {3, 7};
    Interval c = {6, 8};
    Interval d = {5, 6};

    cout << "Two intervals [a,b] and [c,d] overlap if:" << endl;
    cout << "  c.start <= a.end  AND  a.start <= c.end" << endl;
    cout << "  (assuming a.start <= c.start)" << endl;
    cout << "  Simplified: c.start <= a.end" << endl;
    cout << endl;

    cout << "A = "; printInterval(a); cout << "  B = "; printInterval(b); cout << endl;
    cout << "  Overlap? " << (b.start <= a.end ? "Yes" : "No") << endl;
    cout << "  Merged: [1," << (a.end > b.end ? a.end : b.end) << "]" << endl;
    cout << endl;

    cout << "A = "; printInterval(a); cout << "  C = "; printInterval(c); cout << endl;
    cout << "  Overlap? " << (c.start <= a.end ? "Yes" : "No") << endl;
    cout << endl;

    cout << "A = "; printInterval(a); cout << "  D = "; printInterval(d); cout << endl;
    cout << "  Overlap? " << (d.start <= a.end ? "Yes (touching at boundary)" : "No") << endl;
    cout << "  Note: [1,5] and [5,6] touch at 5. Overlap depends on problem definition." << endl;
    cout << "    - If intervals are inclusive: they overlap at point 5" << endl;
    cout << "    - If [start, end): they do NOT overlap" << endl;
    cout << endl;
}

// ============================================================
// SORTING STRATEGIES
// ============================================================

void demoSortingStrategies() {
    cout << "=== Sorting Strategies ===" << endl;
    cout << endl;
    cout << "1. Sort by START time (ascending):" << endl;
    cout << "   Used for: Merge Intervals, Insert Interval, Meeting Rooms I/II" << endl;
    cout << "   After sorting, process left to right, merge overlapping." << endl;
    cout << endl;
    cout << "2. Sort by END time (ascending):" << endl;
    cout << "   Used for: Non-overlapping intervals (activity selection)" << endl;
    cout << "   Greedy: always pick the interval that ends earliest." << endl;
    cout << "   This leaves maximum room for future intervals." << endl;
    cout << endl;
    cout << "3. Separate start and end arrays, sort independently:" << endl;
    cout << "   Used for: Meeting Rooms II (timeline sweep)" << endl;
    cout << "   Walk through starts and ends to track concurrent meetings." << endl;
    cout << endl;
}

// ============================================================
// COMMON INTERVAL PROBLEMS
// ============================================================

void demoCommonProblems() {
    cout << "=== Common Interval Problems ===" << endl;
    cout << endl;
    cout << "1. Merge Intervals (LeetCode 56)" << endl;
    cout << "   Sort by start, merge overlapping intervals" << endl;
    cout << "   [1,3],[2,6],[8,10],[15,18] -> [1,6],[8,10],[15,18]" << endl;
    cout << endl;
    cout << "2. Insert Interval (LeetCode 57)" << endl;
    cout << "   Insert new interval into sorted list, merge overlaps" << endl;
    cout << "   [1,3],[6,9] insert [2,7] -> [1,9]" << endl;
    cout << endl;
    cout << "3. Non-Overlapping Intervals (LeetCode 435)" << endl;
    cout << "   Min removals to make all non-overlapping" << endl;
    cout << "   Sort by end time, greedy: keep earliest-ending" << endl;
    cout << endl;
    cout << "4. Meeting Rooms I (LeetCode 252)" << endl;
    cout << "   Can you attend all meetings? (any overlap?)" << endl;
    cout << "   Sort by start, check adjacent for overlap" << endl;
    cout << endl;
    cout << "5. Meeting Rooms II (LeetCode 253)" << endl;
    cout << "   Min rooms needed for all meetings" << endl;
    cout << "   Timeline sweep or min-heap of end times" << endl;
    cout << endl;
    cout << "6. Interval Intersection (LeetCode 986)" << endl;
    cout << "   Find all intersections of two interval lists" << endl;
    cout << "   Two pointers, advance pointer with smaller end" << endl;
    cout << endl;
    cout << "7. Employee Free Time (LeetCode 759)" << endl;
    cout << "   Flatten all busy intervals, merge, gaps = free time" << endl;
    cout << endl;
}

// ============================================================
// INTERVAL ARITHMETIC
// ============================================================

void demoIntervalArithmetic() {
    cout << "=== Interval Arithmetic ===" << endl;
    cout << endl;

    Interval a = {1, 5};
    Interval b = {3, 7};

    cout << "A = "; printInterval(a); cout << "  B = "; printInterval(b); cout << endl;
    cout << endl;

    // Union (if overlapping)
    cout << "Union (if overlapping): ";
    int unionStart = (a.start < b.start) ? a.start : b.start;
    int unionEnd = (a.end > b.end) ? a.end : b.end;
    cout << "[" << unionStart << "," << unionEnd << "]" << endl;

    // Intersection
    cout << "Intersection: ";
    int intStart = (a.start > b.start) ? a.start : b.start;
    int intEnd = (a.end < b.end) ? a.end : b.end;
    if (intStart <= intEnd) {
        cout << "[" << intStart << "," << intEnd << "]" << endl;
    } else {
        cout << "None" << endl;
    }

    // Gap
    cout << "Gap between A and B: ";
    if (b.start > a.end) {
        cout << b.start - a.end << " units (from " << a.end << " to " << b.start << ")" << endl;
    } else {
        cout << "0 (overlapping or adjacent)" << endl;
    }

    // Contains
    cout << "A contains B? " << (a.start <= b.start && a.end >= b.end ? "Yes" : "No") << endl;
    cout << "B contains A? " << (b.start <= a.start && b.end >= a.end ? "Yes" : "No") << endl;
    cout << endl;
}

int main() {
    demoOverlapDetection();
    demoSortingStrategies();
    demoCommonProblems();
    demoIntervalArithmetic();
    return 0;
}
