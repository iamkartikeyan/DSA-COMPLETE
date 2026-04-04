// 15.4 Interval Problems - Merge, Insert, Meeting Rooms
// Intervals [start, end] are common in scheduling. Key technique:
// sort by start time, then process linearly with merge logic.

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Interval {
    int start, end;
    bool operator<(const Interval& other) const { return start < other.start; }
};

ostream& operator<<(ostream& os, const Interval& iv) {
    return os << "[" << iv.start << "," << iv.end << "]";
}

// ============================================================
// MERGE INTERVALS (LeetCode 56)
// Sort by start time, merge overlapping intervals.
// Two intervals overlap if current.start <= previous.end.
// Time: O(n log n) for sort, O(n) for merge.
// ============================================================

vector<Interval> mergeIntervals(vector<Interval>& intervals) {
    if (intervals.empty()) return {};
    sort(intervals.begin(), intervals.end());

    vector<Interval> merged;
    merged.push_back(intervals[0]);

    for (size_t i = 1; i < intervals.size(); i++) {
        if (intervals[i].start <= merged.back().end) {
            // Overlapping: extend the end of last merged interval
            merged.back().end = max(merged.back().end, intervals[i].end);
        } else {
            merged.push_back(intervals[i]);
        }
    }
    return merged;
}

void demoMergeIntervals() {
    cout << "=== Merge Intervals ===" << endl;
    vector<Interval> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    cout << "Input:  ";
    for (auto& iv : intervals) cout << iv << " "; cout << endl;

    auto result = mergeIntervals(intervals);
    cout << "Merged: ";
    for (auto& iv : result) cout << iv << " ";  // [1,6] [8,10] [15,18]
    cout << endl << endl;
}

// ============================================================
// INSERT INTERVAL (LeetCode 57)
// Insert new interval into sorted non-overlapping list, merge if needed.
// Three phases: before overlap, merging, after overlap.
// Time: O(n)
// ============================================================

vector<Interval> insertInterval(vector<Interval>& intervals, Interval newInterval) {
    vector<Interval> result;
    int i = 0, n = intervals.size();

    // Phase 1: Add intervals that end before newInterval starts
    while (i < n && intervals[i].end < newInterval.start)
        result.push_back(intervals[i++]);

    // Phase 2: Merge all overlapping intervals
    while (i < n && intervals[i].start <= newInterval.end) {
        newInterval.start = min(newInterval.start, intervals[i].start);
        newInterval.end = max(newInterval.end, intervals[i].end);
        i++;
    }
    result.push_back(newInterval);

    // Phase 3: Add remaining intervals
    while (i < n) result.push_back(intervals[i++]);

    return result;
}

void demoInsertInterval() {
    cout << "=== Insert Interval ===" << endl;
    vector<Interval> intervals = {{1, 3}, {6, 9}};
    Interval newInterval = {2, 7};
    cout << "Intervals: ";
    for (auto& iv : intervals) cout << iv << " "; cout << endl;
    cout << "Insert " << newInterval << endl;

    auto result = insertInterval(intervals, newInterval);
    cout << "Result: ";
    for (auto& iv : result) cout << iv << " ";  // [1,9]
    cout << endl << endl;
}

// ============================================================
// NON-OVERLAPPING INTERVALS (LeetCode 435)
// Find minimum intervals to remove to make rest non-overlapping.
// Greedy: sort by end time, always keep the one that ends earliest.
// ============================================================

int minRemovalForNonOverlapping(const vector<Interval>& intervals) {
    if (intervals.empty()) return 0;

    // Sort by end time (greedy: earliest finish first)
    auto sorted = intervals;
    sort(sorted.begin(), sorted.end(), [](const Interval& a, const Interval& b) {
        return a.end < b.end;
    });

    int removeCount = 0, lastEnd = sorted[0].end;
    for (size_t i = 1; i < sorted.size(); i++) {
        if (sorted[i].start < lastEnd)
            removeCount++;  // Overlaps with last kept interval
        else
            lastEnd = sorted[i].end;
    }
    return removeCount;
}

void demoNonOverlapping() {
    cout << "=== Minimum Removal for Non-Overlapping ===" << endl;
    vector<Interval> intervals = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
    cout << "Intervals: ";
    for (auto& iv : intervals) cout << iv << " "; cout << endl;
    cout << "Min removals: " << minRemovalForNonOverlapping(intervals) << endl;  // 1
    cout << endl;
}

// ============================================================
// MEETING ROOMS I (LeetCode 252)
// Can you attend all meetings? Check if any intervals overlap.
// ============================================================

bool canAttendAllMeetings(const vector<Interval>& meetings) {
    auto sorted = meetings;
    sort(sorted.begin(), sorted.end());
    for (size_t i = 1; i < sorted.size(); i++) {
        if (sorted[i].start < sorted[i - 1].end)
            return false;
    }
    return true;
}

void demoMeetingRooms1() {
    cout << "=== Meeting Rooms I (Can Attend All?) ===" << endl;
    vector<Interval> m1 = {{0, 30}, {5, 10}, {15, 20}};
    cout << "Meetings: "; for (auto& iv : m1) cout << iv << " "; cout << endl;
    cout << "Can attend all? " << (canAttendAllMeetings(m1) ? "Yes" : "No") << endl;  // No
    cout << endl;
}

// ============================================================
// MEETING ROOMS II (LeetCode 253)
// Minimum number of rooms needed.
// Two approaches: (1) timeline sweep, (2) min-heap.
// ============================================================

// Approach 1: Separate start/end times, sort independently
int minMeetingRooms(const vector<Interval>& meetings) {
    vector<int> starts, ends;
    for (auto& m : meetings) {
        starts.push_back(m.start);
        ends.push_back(m.end);
    }
    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());

    int rooms = 0, endIdx = 0;
    for (int s : starts) {
        if (s < ends[endIdx]) rooms++;   // Need new room
        else endIdx++;                    // Room freed
    }
    return rooms;
}

// Approach 2: Min-heap of end times
int minMeetingRoomsHeap(const vector<Interval>& meetings) {
    if (meetings.empty()) return 0;
    auto sorted = meetings;
    sort(sorted.begin(), sorted.end());

    priority_queue<int, vector<int>, greater<int>> minHeap;  // End times
    for (auto& m : sorted) {
        if (!minHeap.empty() && minHeap.top() <= m.start)
            minHeap.pop();  // Meeting ended, free the room
        minHeap.push(m.end);
    }
    return minHeap.size();
}

void demoMeetingRooms2() {
    cout << "=== Meeting Rooms II (Min Rooms Needed) ===" << endl;
    vector<Interval> meetings = {{0, 30}, {5, 10}, {15, 20}};
    cout << "Meetings: "; for (auto& m : meetings) cout << m << " "; cout << endl;
    cout << "Min rooms (timeline): " << minMeetingRooms(meetings) << endl;   // 2
    cout << "Min rooms (heap):     " << minMeetingRoomsHeap(meetings) << endl;  // 2
    cout << endl;
}

// ============================================================
// EMPLOYEE FREE TIME (LeetCode 759) - Concept
// Given employees' busy intervals, find common free time.
// Flatten all intervals, merge, then gaps are free time.
// ============================================================

void demoEmployeeFreeTime() {
    cout << "=== Employee Free Time (Concept) ===" << endl;
    cout << "Algorithm:" << endl;
    cout << "1. Flatten all employees' intervals into one list" << endl;
    cout << "2. Sort by start time, merge overlapping intervals" << endl;
    cout << "3. Gaps between merged intervals = common free time" << endl;
    cout << "Time: O(N log N) where N = total intervals" << endl << endl;
}

// ============================================================
// INTERVAL INTERSECTION (LeetCode 986)
// Given two lists of disjoint intervals, find all intersections.
// ============================================================

vector<Interval> intervalIntersection(const vector<Interval>& A, const vector<Interval>& B) {
    vector<Interval> result;
    int i = 0, j = 0;

    while (i < (int)A.size() && j < (int)B.size()) {
        int start = max(A[i].start, B[j].start);
        int end = min(A[i].end, B[j].end);
        if (start <= end)  // Valid intersection
            result.push_back({start, end});

        // Move the pointer with smaller end time
        if (A[i].end < B[j].end) i++;
        else j++;
    }
    return result;
}

void demoIntervalIntersection() {
    cout << "=== Interval Intersection ===" << endl;
    vector<Interval> A = {{0, 2}, {5, 10}, {13, 23}};
    vector<Interval> B = {{1, 5}, {8, 12}, {15, 24}};
    cout << "A: "; for (auto& iv : A) cout << iv << " "; cout << endl;
    cout << "B: "; for (auto& iv : B) cout << iv << " "; cout << endl;

    auto result = intervalIntersection(A, B);
    cout << "Intersection: "; for (auto& iv : result) cout << iv << " ";
    // [1,2] [5,5] [8,10] [15,23]
    cout << endl;
}

int main() {
    demoMergeIntervals();
    demoInsertInterval();
    demoNonOverlapping();
    demoMeetingRooms1();
    demoMeetingRooms2();
    demoEmployeeFreeTime();
    demoIntervalIntersection();
    return 0;
}
