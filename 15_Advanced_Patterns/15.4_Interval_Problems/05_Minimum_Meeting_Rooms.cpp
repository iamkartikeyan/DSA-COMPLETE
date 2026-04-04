// 15.4 - Meeting Rooms (I and II)
// Meeting Rooms I: Can you attend all meetings? (any overlap?)
// Meeting Rooms II: Minimum rooms needed for all meetings.
//
// MEETING ROOMS I:
//   Sort by start time. Check if any adjacent intervals overlap.
//   Overlap: intervals[i].start < intervals[i-1].end
//
// MEETING ROOMS II - Two approaches:
//   Approach 1: Timeline Sweep
//     - Separate start and end times into two arrays
//     - Sort both independently
//     - Walk through starts: if start < current end, need new room
//       else a meeting ended, free a room
//
//   Approach 2: Min-Heap of End Times
//     - Sort by start time
//     - Use min-heap to track end times of ongoing meetings
//     - If earliest ending meeting ends before current starts, free that room
//     - Push current meeting's end time
//     - Heap size = rooms needed

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
// SORT HELPERS
// ============================================================

void sortByStart(Interval intervals[], int n) {
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

void sortArray(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ============================================================
// MEETING ROOMS I - Can attend all?
// ============================================================

bool canAttendAllMeetings(const Interval meetings[], int n) {
    // Check all pairs for overlap
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // Two intervals overlap if they cross
            int s1 = meetings[i].start, e1 = meetings[i].end;
            int s2 = meetings[j].start, e2 = meetings[j].end;
            if (s1 < e2 && s2 < e1) {
                return false;
            }
        }
    }
    return true;
}

// Non-const version that sorts
bool canAttendAllMeetingsSorted(Interval meetings[], int n) {
    if (n <= 1) return true;
    sortByStart(meetings, n);

    for (int i = 1; i < n; i++) {
        if (meetings[i].start < meetings[i - 1].end) {
            return false;
        }
    }
    return true;
}

// ============================================================
// MEETING ROOMS II - Timeline Sweep
// ============================================================

int minMeetingRooms(const Interval meetings[], int n) {
    if (n == 0) return 0;

    int starts[1000], ends[1000];
    for (int i = 0; i < n; i++) {
        starts[i] = meetings[i].start;
        ends[i] = meetings[i].end;
    }

    sortArray(starts, n);
    sortArray(ends, n);

    int rooms = 0, endIdx = 0;
    for (int i = 0; i < n; i++) {
        if (starts[i] < ends[endIdx]) {
            // A meeting starts before one ends -> need new room
            rooms++;
        } else {
            // A meeting ended -> free a room
            endIdx++;
        }
    }
    return rooms;
}

// ============================================================
// MEETING ROOMS II - Min-Heap of End Times
// ============================================================

// Simple min-heap using array
int minMeetingRoomsHeap(const Interval meetings[], int n) {
    if (n == 0) return 0;

    // Copy and sort by start
    Interval sorted[1000];
    for (int i = 0; i < n; i++) sorted[i] = meetings[i];
    sortByStart(sorted, n);

    // Min-heap of end times (using sorted array as heap)
    int heap[1000];
    int heapSize = 0;

    for (int i = 0; i < n; i++) {
        // Check if earliest ending meeting ends before current starts
        if (heapSize > 0 && heap[0] <= sorted[i].start) {
            // Remove min (swap with last, decrease size, re-heapify)
            heap[0] = heap[heapSize - 1];
            heapSize--;
            // Re-heapify (sift down)
            int j = 0;
            while (2 * j + 1 < heapSize) {
                int child = 2 * j + 1;
                if (child + 1 < heapSize && heap[child + 1] < heap[child]) {
                    child++;
                }
                if (heap[j] <= heap[child]) break;
                int temp = heap[j];
                heap[j] = heap[child];
                heap[child] = temp;
                j = child;
            }
        }

        // Insert current end time (sift up)
        heap[heapSize] = sorted[i].end;
        int k = heapSize;
        heapSize++;
        while (k > 0 && heap[k] < heap[(k - 1) / 2]) {
            int temp = heap[k];
            heap[k] = heap[(k - 1) / 2];
            heap[(k - 1) / 2] = temp;
            k = (k - 1) / 2;
        }
    }

    return heapSize;
}

// ============================================================
// DEMONSTRATION
// ============================================================

void demoMeetingRooms1() {
    cout << "=== Meeting Rooms I (Can Attend All?) ===" << endl;

    Interval m1[] = {{0, 30}, {5, 10}, {15, 20}};
    int n1 = 3;

    cout << "Meetings: ";
    for (int i = 0; i < n1; i++) {
        printInterval(m1[i]);
        cout << " ";
    }
    cout << endl;

    Interval copy1[1000];
    for (int i = 0; i < n1; i++) copy1[i] = m1[i];
    cout << "Can attend all? " << (canAttendAllMeetingsSorted(copy1, n1) ? "Yes" : "No") << endl;
    cout << "Expected: No (0-30 overlaps with 5-10 and 15-20)" << endl;
    cout << endl;

    Interval m2[] = {{0, 5}, {5, 10}, {10, 15}};
    int n2 = 3;

    cout << "Meetings: ";
    for (int i = 0; i < n2; i++) {
        printInterval(m2[i]);
        cout << " ";
    }
    cout << endl;

    Interval copy2[1000];
    for (int i = 0; i < n2; i++) copy2[i] = m2[i];
    cout << "Can attend all? " << (canAttendAllMeetingsSorted(copy2, n2) ? "Yes" : "No") << endl;
    cout << "Expected: Yes (no overlaps, touching at boundaries)" << endl;
    cout << endl;
}

void demoMeetingRooms2() {
    cout << "=== Meeting Rooms II (Min Rooms Needed) ===" << endl;

    Interval meetings[] = {{0, 30}, {5, 10}, {15, 20}};
    int n = 3;

    cout << "Meetings: ";
    for (int i = 0; i < n; i++) {
        printInterval(meetings[i]);
        cout << " ";
    }
    cout << endl;

    int rooms1 = minMeetingRooms(meetings, n);
    int rooms2 = minMeetingRoomsHeap(meetings, n);

    cout << "Min rooms (timeline sweep): " << rooms1 << endl;
    cout << "Min rooms (min-heap):       " << rooms2 << endl;
    cout << "Expected: 2" << endl;
    cout << endl;
}

void demoWalkthrough() {
    cout << "=== Walkthrough: Min Rooms for [0,30],[5,10],[15,20] ===" << endl;
    cout << endl;
    cout << "Timeline Sweep Approach:" << endl;
    cout << "  Starts: [0, 5, 15]" << endl;
    cout << "  Ends:   [10, 20, 30]" << endl;
    cout << endl;
    cout << "  Start=0: 0 < 10 -> rooms=1" << endl;
    cout << "  Start=5: 5 < 10 -> rooms=2" << endl;
    cout << "  Start=15: 15 >= 10 -> endIdx++, rooms stays 2" << endl;
    cout << "  Result: 2 rooms" << endl;
    cout << endl;
    cout << "Min-Heap Approach:" << endl;
    cout << "  Sort by start: [0,30], [5,10], [15,20]" << endl;
    cout << "  [0,30]: heap empty, push 30. heap=[30], size=1" << endl;
    cout << "  [5,10]: 30 > 5, can't free. push 10. heap=[10,30], size=2" << endl;
    cout << "  [15,20]: 10 <= 15, free room. pop 10. push 20. heap=[20,30], size=2" << endl;
    cout << "  Result: 2 rooms" << endl;
    cout << endl;
}

void demoLargerExample() {
    cout << "=== Larger Example ===" << endl;
    Interval meetings[] = {{7, 10}, {2, 4}, {5, 8}, {1, 3}, {9, 12}};
    int n = 5;

    cout << "Meetings: ";
    for (int i = 0; i < n; i++) {
        printInterval(meetings[i]);
        cout << " ";
    }
    cout << endl;

    cout << "Min rooms (timeline): " << minMeetingRooms(meetings, n) << endl;
    cout << "Expected: 2" << endl;
    cout << "  (e.g., Room 1: [1,3],[5,8],[9,12], Room 2: [2,4],[7,10])" << endl;
    cout << endl;
}

int main() {
    demoWalkthrough();
    demoMeetingRooms1();
    demoMeetingRooms2();
    demoLargerExample();
    return 0;
}
