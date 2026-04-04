// Flight Booking Problem (LeetCode 1109)
// n flights, bookings[i] = [first, last, seats]
// Each booking adds seats to flights first..last (1-based).
// Return array where result[i] = total seats on flight i+1.
//
// Approach: Use difference array for O(1) per booking.
//   1. Start with diff array of n zeros
//   2. For each booking [first, last, seats]:
//      - diff[first-1] += seats
//      - if last < n: diff[last] -= seats
//   3. Reconstruct with prefix sum
//
// Time Complexity: O(n + m) where m = number of bookings
// Space Complexity: O(n) for diff array

#include <iostream>
using namespace std;

const int MAXN = 100;

struct Booking {
    int first;
    int last;
    int seats;
};

void corpFlightBookings(const int bookings[][3], int numBookings, int n, int result[]) {
    // Initialize difference array with zeros
    int diff[MAXN];
    for (int i = 0; i < n; i++) {
        diff[i] = 0;
    }

    // Apply each booking as O(1) range update
    for (int i = 0; i < numBookings; i++) {
        int first = bookings[i][0] - 1;  // Convert to 0-based
        int last = bookings[i][1] - 1;
        int seats = bookings[i][2];

        diff[first] += seats;
        if (last + 1 < n) {
            diff[last + 1] -= seats;
        }
    }

    // Reconstruct via prefix sum
    result[0] = diff[0];
    for (int i = 1; i < n; i++) {
        result[i] = result[i - 1] + diff[i];
    }
}

int main() {
    cout << "=== Application: Flight Booking (LeetCode 1109) ===" << endl;
    cout << endl;

    // Example: 5 flights, 3 bookings
    int n = 5;
    int bookings[][3] = {
        {1, 2, 10},  // flights 1-2: +10 seats
        {2, 3, 20},  // flights 2-3: +20 seats
        {2, 5, 25}   // flights 2-5: +25 seats
    };
    int numBookings = 3;

    cout << "Number of flights: " << n << endl;
    cout << "Bookings:" << endl;
    for (int i = 0; i < numBookings; i++) {
        cout << "  Booking " << i + 1 << ": flights " << bookings[i][0] << "-" << bookings[i][1];
        cout << " get +" << bookings[i][2] << " seats" << endl;
    }
    cout << endl;

    // Solve using difference array
    int result[MAXN];
    corpFlightBookings(bookings, numBookings, n, result);

    // Show step-by-step diff array construction
    cout << "Step-by-step difference array:" << endl;
    int diff[MAXN];
    for (int i = 0; i < n; i++) diff[i] = 0;
    cout << "  Initial diff: ";
    for (int i = 0; i < n; i++) cout << diff[i] << " ";
    cout << endl;

    for (int i = 0; i < numBookings; i++) {
        int first = bookings[i][0] - 1;
        int last = bookings[i][1] - 1;
        int seats = bookings[i][2];
        diff[first] += seats;
        if (last + 1 < n) diff[last + 1] -= seats;

        cout << "  After booking " << i + 1 << " [" << bookings[i][0] << "," << bookings[i][1] << "," << seats << "]: ";
        for (int j = 0; j < n; j++) cout << diff[j] << " ";
        cout << endl;
    }
    cout << endl;

    cout << "Result (prefix sum of diff):" << endl;
    cout << "  Flights: ";
    for (int i = 0; i < n; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << "  Expected: 10 55 45 25 25" << endl;

    cout << endl;
    cout << "Why difference array works:" << endl;
    cout << "  Without it: each booking updates O(n) flights => O(m*n) total" << endl;
    cout << "  With it:    each booking is O(1) => O(n + m) total" << endl;

    return 0;
}
