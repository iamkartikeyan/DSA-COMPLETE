// 15.4 - Insert Interval (LeetCode 57)
// Insert a new interval into a sorted list of non-overlapping intervals.
// Merge overlapping intervals as needed.
// Time: O(n), Space: O(n) for result.
//
// PATTERN - Three phases:
//   1. BEFORE: Add all intervals that end before newInterval starts (no overlap)
//   2. MERGE: Merge all overlapping intervals with newInterval
//      - Overlap condition: interval.start <= newInterval.end
//      - Merge: newInterval.start = min, newInterval.end = max
//   3. AFTER: Add all remaining intervals (start after newInterval ends)

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

void printIntervals(const vector<Interval> &intervals) {
    for (int i = 0; i < (int)intervals.size(); i++) {
        printInterval(intervals[i]);
        cout << " ";
    }
    cout << endl;
}

int minInt(int a, int b) { return (a < b) ? a : b; }
int maxInt(int a, int b) { return (a > b) ? a : b; }

// ============================================================
// INSERT INTERVAL
// ============================================================

vector<Interval> insertInterval(const Interval intervals[], int n, Interval newInterval) {
    vector<Interval> result;
    int i = 0;

    // Phase 1: Add intervals that end before newInterval starts
    while (i < n && intervals[i].end < newInterval.start) {
        result.push_back(intervals[i]);
        i++;
    }

    // Phase 2: Merge all overlapping intervals
    while (i < n && intervals[i].start <= newInterval.end) {
        newInterval.start = minInt(newInterval.start, intervals[i].start);
        newInterval.end = maxInt(newInterval.end, intervals[i].end);
        i++;
    }
    result.push_back(newInterval);

    // Phase 3: Add remaining intervals
    while (i < n) {
        result.push_back(intervals[i]);
        i++;
    }

    return result;
}

// ============================================================
// DEMONSTRATION
// ============================================================

void demoInsertInterval() {
    cout << "=== Insert Interval - Example 1 ===" << endl;
    Interval intervals[] = {{1, 3}, {6, 9}};
    Interval newInterval = {2, 7};
    int n = 2;

    cout << "Intervals: ";
    printIntervals(vector<Interval>(intervals, intervals + n));
    cout << "Insert:    ";
    printInterval(newInterval);
    cout << endl;

    vector<Interval> result = insertInterval(intervals, n, newInterval);
    cout << "Result:    ";
    printIntervals(result);
    cout << "Expected: [1,9]" << endl;
    cout << endl;
}

void demoInsertInterval2() {
    cout << "=== Insert Interval - Example 2 ===" << endl;
    Interval intervals[] = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    Interval newInterval = {4, 8};
    int n = 5;

    cout << "Intervals: ";
    printIntervals(vector<Interval>(intervals, intervals + n));
    cout << "Insert:    ";
    printInterval(newInterval);
    cout << endl;

    vector<Interval> result = insertInterval(intervals, n, newInterval);
    cout << "Result:    ";
    printIntervals(result);
    cout << "Expected: [1,2] [3,10] [12,16]" << endl;
    cout << endl;
}

void demoInsertNoOverlap() {
    cout << "=== Insert Interval - No Overlap ===" << endl;
    Interval intervals[] = {{1, 2}, {5, 6}};
    Interval newInterval = {3, 4};
    int n = 2;

    cout << "Intervals: ";
    printIntervals(vector<Interval>(intervals, intervals + n));
    cout << "Insert:    ";
    printInterval(newInterval);
    cout << endl;

    vector<Interval> result = insertInterval(intervals, n, newInterval);
    cout << "Result:    ";
    printIntervals(result);
    cout << "Expected: [1,2] [3,4] [5,6]" << endl;
    cout << endl;
}

void demoInsertAtBeginning() {
    cout << "=== Insert Interval - At Beginning ===" << endl;
    Interval intervals[] = {{3, 5}, {7, 9}};
    Interval newInterval = {1, 2};
    int n = 2;

    cout << "Intervals: ";
    printIntervals(vector<Interval>(intervals, intervals + n));
    cout << "Insert:    ";
    printInterval(newInterval);
    cout << endl;

    vector<Interval> result = insertInterval(intervals, n, newInterval);
    cout << "Result:    ";
    printIntervals(result);
    cout << "Expected: [1,2] [3,5] [7,9]" << endl;
    cout << endl;
}

void demoWalkthrough() {
    cout << "=== Walkthrough: Insert [4,8] into [1,2],[3,5],[6,7],[8,10],[12,16] ===" << endl;
    cout << endl;
    cout << "Phase 1 (BEFORE): intervals ending before 4" << endl;
    cout << "  [1,2]: end=2 < 4 -> add to result. result = [[1,2]]" << endl;
    cout << "  [3,5]: end=5 >= 4 -> stop Phase 1" << endl;
    cout << endl;
    cout << "Phase 2 (MERGE): intervals overlapping with [4,8]" << endl;
    cout << "  [3,5]: start=3 <= 8 -> merge: [min(4,3), max(8,5)] = [3,8]" << endl;
    cout << "  [6,7]: start=6 <= 8 -> merge: [min(3,6), max(8,7)] = [3,8]" << endl;
    cout << "  [8,10]: start=8 <= 8 -> merge: [min(3,8), max(8,10)] = [3,10]" << endl;
    cout << "  [12,16]: start=12 > 10 -> stop Phase 2" << endl;
    cout << "  Add merged: result = [[1,2], [3,10]]" << endl;
    cout << endl;
    cout << "Phase 3 (AFTER): remaining intervals" << endl;
    cout << "  [12,16]: add. result = [[1,2], [3,10], [12,16]]" << endl;
    cout << endl;
}

int main() {
    demoWalkthrough();
    demoInsertInterval();
    demoInsertInterval2();
    demoInsertNoOverlap();
    demoInsertAtBeginning();
    return 0;
}
