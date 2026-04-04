// 15.4 - Merge Intervals (LeetCode 56)
// Given a list of intervals, merge all overlapping intervals.
// Sort by start time, then process linearly with merge logic.
// Time: O(n log n) for sort, O(n) for merge. Space: O(n) for result.
//
// PATTERN:
//   1. Sort intervals by start time
//   2. Initialize merged list with first interval
//   3. For each subsequent interval:
//      - If it overlaps with last merged (curr.start <= last.end):
//        extend last.end to max(last.end, curr.end)
//      - Else: add as new interval

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

// ============================================================
// MERGE INTERVALS
// ============================================================

// Sort intervals by start time (bubble sort)
void sortIntervals(Interval intervals[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (intervals[j].start > intervals[j + 1].start) {
                Interval temp = intervals[j];
                intervals[j] = intervals[j + 1];
                intervals[j + 1] = temp;
            }
        }
    }
}

// Helper: return max of two ints
int maxInt(int a, int b) {
    return (a > b) ? a : b;
}

vector<Interval> mergeIntervals(Interval intervals[], int n) {
    if (n == 0) {
        vector<Interval> empty;
        return empty;
    }

    // Sort by start time
    sortIntervals(intervals, n);

    // Merge
    vector<Interval> merged;
    merged.push_back(intervals[0]);

    for (int i = 1; i < n; i++) {
        Interval last = merged[(int)merged.size() - 1];
        if (intervals[i].start <= last.end) {
            // Overlapping: extend the end
            merged[(int)merged.size() - 1].end = maxInt(last.end, intervals[i].end);
        } else {
            // Non-overlapping: add new interval
            merged.push_back(intervals[i]);
        }
    }

    return merged;
}

// ============================================================
// DEMONSTRATION
// ============================================================

void demoMergeIntervals() {
    cout << "=== Merge Intervals - Example 1 ===" << endl;
    Interval intervals[] = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    int n = 4;

    cout << "Input:  ";
    printIntervals(vector<Interval>(intervals, intervals + n));

    vector<Interval> result = mergeIntervals(intervals, n);
    cout << "Merged: ";
    printIntervals(result);
    cout << "Expected: [1,6] [8,10] [15,18]" << endl;
    cout << endl;
}

void demoMergeIntervals2() {
    cout << "=== Merge Intervals - Example 2 ===" << endl;
    Interval intervals[] = {{1, 4}, {4, 5}};
    int n = 2;

    cout << "Input:  ";
    printIntervals(vector<Interval>(intervals, intervals + n));

    vector<Interval> result = mergeIntervals(intervals, n);
    cout << "Merged: ";
    printIntervals(result);
    cout << "Expected: [1,5] (touching intervals merge)" << endl;
    cout << endl;
}

void demoMergeIntervals3() {
    cout << "=== Merge Intervals - Example 3 (Unsorted) ===" << endl;
    Interval intervals[] = {{5, 8}, {1, 3}, {2, 6}, {10, 12}};
    int n = 4;

    cout << "Input:  ";
    printIntervals(vector<Interval>(intervals, intervals + n));

    vector<Interval> result = mergeIntervals(intervals, n);
    cout << "Merged: ";
    printIntervals(result);
    cout << "Expected: [1,6] [10,12]" << endl;
    cout << endl;
}

void demoWalkthrough() {
    cout << "=== Walkthrough: Merge [1,3], [2,6], [8,10], [15,18] ===" << endl;
    cout << "Step 1: Sort by start (already sorted)" << endl;
    cout << "  [1,3], [2,6], [8,10], [15,18]" << endl;
    cout << endl;
    cout << "Step 2: Merge" << endl;
    cout << "  merged = [[1,3]]" << endl;
    cout << "  [2,6]: 2 <= 3 (overlap), extend: merged = [[1,6]]" << endl;
    cout << "  [8,10]: 8 > 6 (no overlap), add: merged = [[1,6], [8,10]]" << endl;
    cout << "  [15,18]: 15 > 10 (no overlap), add: merged = [[1,6], [8,10], [15,18]]" << endl;
    cout << endl;
}

void demoNestedIntervals() {
    cout << "=== Merge Intervals - Nested Intervals ===" << endl;
    Interval intervals[] = {{1, 10}, {2, 5}, {3, 7}, {12, 15}};
    int n = 4;

    cout << "Input:  ";
    printIntervals(vector<Interval>(intervals, intervals + n));
    cout << "Note: [2,5] and [3,7] are nested within [1,10]" << endl;

    vector<Interval> result = mergeIntervals(intervals, n);
    cout << "Merged: ";
    printIntervals(result);
    cout << "Expected: [1,10] [12,15]" << endl;
    cout << endl;
}

int main() {
    demoWalkthrough();
    demoMergeIntervals();
    demoMergeIntervals2();
    demoMergeIntervals3();
    demoNestedIntervals();
    return 0;
}
