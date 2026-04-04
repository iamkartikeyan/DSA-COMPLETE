// Car Pooling Problem (LeetCode 1094)
// Determine if a car can pick up and drop off all passengers
// for all given trips without exceeding capacity at any point.
//
// trips[i] = [numPassengers, from, to]
//   - numPassengers: people getting in
//   - from: location where they get in
//   - to: location where they get out (they are NOT in the car at this location)
//
// Approach: Difference array on locations
//   1. For each trip [passengers, from, to]:
//      - diff[from] += passengers  (people board)
//      - diff[to] -= passengers    (people leave)
//   2. Compute prefix sum to get passenger count at each location
//   3. Check if any location exceeds capacity
//
// Time Complexity: O(n + L) where L = max location (at most 1001)
// Space Complexity: O(L) for diff array

#include <iostream>
using namespace std;

const int MAX_LOCATIONS = 1001;

struct Trip {
    int passengers;
    int from;
    int to;
};

bool canHandleAllTrips(const int trips[][3], int numTrips, int capacity) {
    // Difference array for locations 0..1000
    int diff[MAX_LOCATIONS];
    for (int i = 0; i < MAX_LOCATIONS; i++) {
        diff[i] = 0;
    }

    // Apply each trip
    for (int i = 0; i < numTrips; i++) {
        int passengers = trips[i][0];
        int from = trips[i][1];
        int to = trips[i][2];

        diff[from] += passengers;   // People board
        diff[to] -= passengers;     // People leave at 'to'
    }

    // Check prefix sums against capacity
    for (int i = 0; i < MAX_LOCATIONS; i++) {
        if (i > 0) {
            diff[i] += diff[i - 1];
        }
        if (diff[i] > capacity) {
            return false;
        }
    }

    return true;
}

int main() {
    cout << "=== Application: Car Pooling (LeetCode 1094) ===" << endl;
    cout << endl;

    // Example 1
    int trips1[][3] = {
        {2, 1, 5},  // 2 passengers from loc 1 to 5
        {3, 3, 7}   // 3 passengers from loc 3 to 7
    };
    int numTrips1 = 2;

    cout << "Test Case 1:" << endl;
    cout << "  Trips: [2,1,5], [3,3,7]" << endl;
    cout << "  Capacity = 4" << endl;

    // Show diff array
    int diff1[MAX_LOCATIONS];
    for (int i = 0; i < 11; i++) diff1[i] = 0;
    diff1[1] += 2; diff1[5] -= 2;
    diff1[3] += 3; diff1[7] -= 3;

    cout << "  Diff array (locations 0-10): ";
    for (int i = 0; i < 11; i++) cout << diff1[i] << " ";
    cout << endl;

    cout << "  Passengers at each location: ";
    for (int i = 1; i < 11; i++) diff1[i] += diff1[i - 1];
    for (int i = 0; i < 11; i++) cout << diff1[i] << " ";
    cout << endl;
    cout << "  Location 3-4 has 5 passengers > capacity 4" << endl;
    cout << "  Result: " << (canHandleAllTrips(trips1, numTrips1, 4) ? "Yes" : "No") << endl;
    cout << endl;

    cout << "  Capacity = 5" << endl;
    cout << "  Location 3-4 has 5 passengers <= capacity 5" << endl;
    cout << "  Result: " << (canHandleAllTrips(trips1, numTrips1, 5) ? "Yes" : "No") << endl;
    cout << endl;

    // Example 2: Multiple overlapping trips
    int trips2[][3] = {
        {3, 2, 7},
        {3, 7, 9},
        {8, 3, 9}
    };
    int numTrips2 = 3;

    cout << "Test Case 2:" << endl;
    cout << "  Trips: [3,2,7], [3,7,9], [8,3,9]" << endl;
    cout << "  Capacity = 11" << endl;

    int diff2[MAX_LOCATIONS];
    for (int i = 0; i < 11; i++) diff2[i] = 0;
    diff2[2] += 3; diff2[7] -= 3;
    diff2[7] += 3; diff2[9] -= 3;
    diff2[3] += 8; diff2[9] -= 8;

    cout << "  Passengers at locations 0-10:" << endl;
    cout << "  Diff:     ";
    for (int i = 0; i < 11; i++) cout << diff2[i] << " ";
    cout << endl;

    cout << "  Prefix:   ";
    for (int i = 1; i < 11; i++) diff2[i] += diff2[i - 1];
    for (int i = 0; i < 11; i++) cout << diff2[i] << " ";
    cout << endl;

    cout << "  Max passengers: 11 (at locations 3-6)" << endl;
    cout << "  Result (cap=11): " << (canHandleAllTrips(trips2, numTrips2, 11) ? "Yes" : "No") << endl;
    cout << "  Result (cap=10): " << (canHandleAllTrips(trips2, numTrips2, 10) ? "Yes" : "No") << endl;

    return 0;
}
