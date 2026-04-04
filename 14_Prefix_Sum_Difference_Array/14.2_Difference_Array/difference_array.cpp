// 14.2 Difference Array - Range Update O(1), Query O(n)
// Difference array enables batch range updates. Build diff, apply changes,
// then reconstruct with prefix sum. Core idea: arr[i] = diff[0]+..+diff[i]

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// ============================================================
// BASIC DIFFERENCE ARRAY
// Range update: O(1) each, Final reconstruction: O(n)
// ============================================================

// Build difference array: diff[i] = arr[i] - arr[i-1]
vector<int> buildDiff(const vector<int>& arr) {
    int n = arr.size();
    vector<int> diff(n);
    diff[0] = arr[0];
    for (int i = 1; i < n; i++)
        diff[i] = arr[i] - arr[i - 1];
    return diff;
}

// Range update: add val to arr[l..r] inclusive, O(1)
void rangeUpdate(vector<int>& diff, int l, int r, int val) {
    diff[l] += val;
    if (r + 1 < (int)diff.size())
        diff[r + 1] -= val;  // Cancel the addition after range ends
}

// Reconstruct original array from difference array: O(n)
vector<int> reconstruct(const vector<int>& diff) {
    vector<int> arr(diff.size());
    arr[0] = diff[0];
    for (int i = 1; i < (int)arr.size(); i++)
        arr[i] = arr[i - 1] + diff[i];
    return arr;
}

void demoBasicDiffArray() {
    cout << "=== Basic Difference Array ===" << endl;
    vector<int> arr = {1, 2, 3, 4, 5, 6};
    cout << "Initial: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    auto diff = buildDiff(arr);

    // Apply range updates in O(1) each
    rangeUpdate(diff, 1, 3, 5);  // Add 5 to indices 1-3
    rangeUpdate(diff, 2, 5, 3);  // Add 3 to indices 2-5

    auto result = reconstruct(diff);
    cout << "After updates: ";
    for (int x : result) cout << x << " ";
    cout << "  // [1, 7, 11, 12, 8, 9]" << endl;
    cout << endl;
}

// ============================================================
// APPLICATION 1: Airline Flight Booking (LeetCode 1109)
// n flights, bookings[i] = [first, last, seats]
// Each booking adds seats to flights first..last
// ============================================================

vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
    vector<int> diff(n, 0);
    for (auto& b : bookings) {
        int first = b[0] - 1, last = b[1] - 1, seats = b[2];
        diff[first] += seats;
        if (last + 1 < n) diff[last + 1] -= seats;
    }
    // Reconstruct via prefix sum
    for (int i = 1; i < n; i++)
        diff[i] += diff[i - 1];
    return diff;
}

void demoFlightBooking() {
    cout << "=== Application: Flight Booking ===" << endl;
    vector<vector<int>> bookings = {
        {1, 2, 10},  // flights 1-2: +10
        {2, 3, 20},  // flights 2-3: +20
        {2, 5, 25}   // flights 2-5: +25
    };
    int n = 5;
    auto result = corpFlightBookings(bookings, n);
    cout << "Bookings: [1,2,10], [2,3,20], [2,5,25]" << endl;
    cout << "Result: ";
    for (int x : result) cout << x << " ";  // [10, 55, 45, 25, 25]
    cout << endl << endl;
}

// ============================================================
// APPLICATION 2: Range Addition (LeetCode 370)
// Start with zeros, apply range additions, return final array
// ============================================================

vector<int> rangeAddition(int length, const vector<vector<int>>& updates) {
    vector<int> diff(length, 0);
    for (auto& u : updates) {
        diff[u[0]] += u[2];
        if (u[1] + 1 < length) diff[u[1] + 1] -= u[2];
    }
    for (int i = 1; i < length; i++)
        diff[i] += diff[i - 1];
    return diff;
}

void demoRangeAddition() {
    cout << "=== Application: Range Addition ===" << endl;
    int length = 5;
    vector<vector<int>> updates = {
        {1, 3, 2},   // indices 1-3: +2
        {2, 4, 3},   // indices 2-4: +3
        {0, 2, -2}   // indices 0-2: -2
    };
    auto result = rangeAddition(length, updates);
    cout << "Length = 5, Updates: [1,3,+2], [2,4,+3], [0,2,-2]" << endl;
    cout << "Result: ";
    for (int x : result) cout << x << " ";  // [-2, 0, 3, 5, 3]
    cout << endl << endl;
}

// ============================================================
// APPLICATION 3: 2D Difference Array
// Range update on 2D submatrix in O(1)
// ============================================================

// 2D difference array update: add val to submatrix [r1..r2][c1..c2]
void rangeUpdate2D(vector<vector<int>>& diff, int r1, int c1, int r2, int c2, int val) {
    int m = diff.size(), n = diff[0].size();
    diff[r1][c1] += val;
    if (r2 + 1 < m) diff[r2 + 1][c1] -= val;
    if (c2 + 1 < n) diff[r1][c2 + 1] -= val;
    if (r2 + 1 < m && c2 + 1 < n) diff[r2 + 1][c2 + 1] += val;
}

// Reconstruct 2D array: prefix sum along rows, then cols
vector<vector<int>> reconstruct2D(const vector<vector<int>>& diff) {
    int m = diff.size(), n = diff[0].size();
    auto arr = diff;
    // Row-wise prefix sum
    for (int i = 0; i < m; i++)
        for (int j = 1; j < n; j++)
            arr[i][j] += arr[i][j - 1];
    // Column-wise prefix sum
    for (int j = 0; j < n; j++)
        for (int i = 1; i < m; i++)
            arr[i][j] += arr[i - 1][j];
    return arr;
}

void demo2DDiffArray() {
    cout << "=== 2D Difference Array ===" << endl;
    int m = 4, n = 4;
    vector<vector<int>> diff(m, vector<int>(n, 0));

    // Add 5 to submatrix [0,0] to [1,1]
    rangeUpdate2D(diff, 0, 0, 1, 1, 5);
    // Add 3 to submatrix [1,1] to [3,3]
    rangeUpdate2D(diff, 1, 1, 3, 3, 3);

    auto result = reconstruct2D(diff);
    cout << "After 2D range updates:" << endl;
    for (auto& row : result) {
        for (int x : row) cout << setw(3) << x;
        cout << endl;
    }
    cout << endl;
}

// ============================================================
// APPLICATION 4: Car Pooling (LeetCode 1094)
// Determine if all passengers can be accommodated
// ============================================================

bool carPooling(vector<vector<int>>& trips, int capacity) {
    // At most 1001 locations
    vector<int> diff(1001, 0);
    for (auto& t : trips) {
        int passengers = t[0], from = t[1], to = t[2];
        diff[from] += passengers;
        diff[to] -= passengers;  // Passengers leave at 'to'
    }
    for (int i = 1; i < 1001; i++) {
        diff[i] += diff[i - 1];
        if (diff[i] > capacity) return false;
    }
    return diff[0] <= capacity;
}

void demoCarPooling() {
    cout << "=== Application: Car Pooling ===" << endl;
    vector<vector<int>> trips = {{2, 1, 5}, {3, 3, 7}};
    cout << "Trips: [2,1,5], [3,3,7], Capacity = 4: "
         << (carPooling(trips, 4) ? "Yes" : "No") << endl;
    cout << "Trips: [2,1,5], [3,3,7], Capacity = 5: "
         << (carPooling(trips, 5) ? "Yes" : "No") << endl;
    cout << endl;
}

int main() {
    demoBasicDiffArray();
    demoFlightBooking();
    demoRangeAddition();
    demo2DDiffArray();
    demoCarPooling();
    return 0;
}
