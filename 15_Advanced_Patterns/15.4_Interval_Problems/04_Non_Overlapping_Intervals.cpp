// 15.4 - Non-Overlapping Intervals (Activity Selection)
// Find the minimum number of intervals to remove so that the rest
// do not overlap. Equivalent to: find the maximum number of
// non-overlapping intervals, then remove the rest.
//
// GREEDY APPROACH: Sort by END TIME. Always keep the interval that
// ends earliest. This leaves maximum room for future intervals.
//
// WHY END TIME? Consider intervals [1,100], [2,3], [4,5]:
//   - If we keep [1,100], we can't fit any other interval.
//   - If we keep [2,3], we can also fit [4,5]. Better!
//   - Earliest finish maximizes remaining space.
//
// Time: O(n log n) for sort, O(n) for greedy pass.

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
// SORT BY END TIME (bubble sort)
// ============================================================

void sortByEndTime(Interval intervals[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (intervals[j].end > intervals[j + 1].end) {
                Interval temp = intervals[j];
                intervals[j] = intervals[j + 1];
                intervals[j + 1] = temp;
            }
        }
    }
}

// ============================================================
// MIN REMOVAL FOR NON-OVERLAPPING
// Returns the minimum number of intervals to remove.
// ============================================================

int minRemovalForNonOverlapping(Interval intervals[], int n) {
    if (n <= 1) return 0;

    // Sort by end time
    sortByEndTime(intervals, n);

    int removeCount = 0;
    int lastEnd = intervals[0].end;

    for (int i = 1; i < n; i++) {
        if (intervals[i].start < lastEnd) {
            // Overlaps with last kept interval -> remove it
            removeCount++;
        } else {
            // No overlap -> keep this interval
            lastEnd = intervals[i].end;
        }
    }

    return removeCount;
}

// ============================================================
// MAXIMUM NON-OVERLAPPING INTERVALS
// Returns the maximum number of non-overlapping intervals.
// ============================================================

int maxNonOverlapping(Interval intervals[], int n) {
    if (n <= 1) return n;

    sortByEndTime(intervals, n);

    int count = 1;  // Always keep the first (earliest ending)
    int lastEnd = intervals[0].end;

    for (int i = 1; i < n; i++) {
        if (intervals[i].start >= lastEnd) {
            count++;
            lastEnd = intervals[i].end;
        }
    }

    return count;
}

// ============================================================
// DEMONSTRATION
// ============================================================

void demoMinRemoval() {
    cout << "=== Minimum Removal for Non-Overlapping ===" << endl;
    Interval intervals[] = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
    int n = 4;

    cout << "Intervals: ";
    for (int i = 0; i < n; i++) {
        printInterval(intervals[i]);
        cout << " ";
    }
    cout << endl;

    cout << "Min removals: " << minRemovalForNonOverlapping(intervals, n) << endl;
    cout << "Expected: 1 (remove [1,3])" << endl;
    cout << endl;
}

void demoMaxNonOverlapping() {
    cout << "=== Maximum Non-Overlapping Intervals ===" << endl;
    Interval intervals[] = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
    int n = 4;

    cout << "Intervals: ";
    for (int i = 0; i < n; i++) {
        printInterval(intervals[i]);
        cout << " ";
    }
    cout << endl;

    cout << "Max non-overlapping: " << maxNonOverlapping(intervals, n) << endl;
    cout << "Expected: 3 ([1,2], [2,3], [3,4])" << endl;
    cout << endl;
}

void demoWalkthrough() {
    cout << "=== Walkthrough: [1,2],[2,3],[3,4],[1,3] ===" << endl;
    cout << endl;
    cout << "Step 1: Sort by end time" << endl;
    cout << "  [1,2](end=2), [2,3](end=3), [1,3](end=3), [3,4](end=4)" << endl;
    cout << endl;
    cout << "Step 2: Greedy scan" << endl;
    cout << "  Keep [1,2]. lastEnd = 2" << endl;
    cout << "  [2,3]: start=2 >= 2 -> keep. lastEnd = 3" << endl;
    cout << "  [1,3]: start=1 < 3 -> SKIP (remove)" << endl;
    cout << "  [3,4]: start=3 >= 3 -> keep. lastEnd = 4" << endl;
    cout << endl;
    cout << "Kept: [1,2], [2,3], [3,4] -> 3 intervals" << endl;
    cout << "Removed: 1" << endl;
    cout << endl;
}

void demoClassicActivitySelection() {
    cout << "=== Classic Activity Selection ===" << endl;
    // Activities: (start, finish)
    Interval activities[] = {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 14}, {12, 16}};
    int n = 11;

    cout << "Activities: ";
    for (int i = 0; i < n; i++) {
        printInterval(activities[i]);
        cout << " ";
    }
    cout << endl;

    cout << "Max activities: " << maxNonOverlapping(activities, n) << endl;
    cout << "Min removals: " << minRemovalForNonOverlapping(activities, n) << endl;
    cout << endl;
}

int main() {
    demoWalkthrough();
    demoMinRemoval();
    demoMaxNonOverlapping();
    demoClassicActivitySelection();
    return 0;
}
