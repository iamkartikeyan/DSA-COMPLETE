/*
 * Minimum Platforms Problem
 *
 * Given arrival and departure times of trains,
 * find the minimum number of platforms needed so that
 * no train has to wait.
 *
 * Greedy Strategy:
 *   1. Sort arrivals and departures independently.
 *   2. Use two pointers to sweep through events.
 *   3. When a train arrives before the earliest departure,
 *      we need an extra platform.
 *   4. When a train departs before the next arrival,
 *      a platform becomes free.
 *   5. Track the maximum number of platforms needed at once.
 *
 * Time  : O(n log n)  for sorting
 * Space : O(1)        beyond input storage
 *
 * Why greedy works:
 *   By sorting both arrays and processing events in order,
 *   we accurately count how many trains overlap at any moment.
 *   The maximum overlap IS the answer.
 */

#include <iostream>

/* Swap two integers */
void swapInt(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

/* Sort array ascending */
void sortArray(int arr[], int n) {
    int i = 0;
    while (i < n) {
        int j = 0;
        while (j < n - i - 1) {
            if (arr[j] > arr[j + 1]) {
                swapInt(arr[j], arr[j + 1]);
            }
            j = j + 1;
        }
        i = i + 1;
    }
}

int findMinPlatforms(int arrival[], int departure[], int n) {
    /* Step 1: Sort both arrays */
    sortArray(arrival, n);
    sortArray(departure, n);

    /* Step 2: Two-pointer sweep */
    int platforms = 1;   /* platforms needed at current moment */
    int maxPlatforms = 1; /* maximum platforms ever needed */

    int i = 1;  /* pointer for arrivals */
    int j = 0;  /* pointer for departures */

    while (i < n && j < n) {
        if (arrival[i] <= departure[j]) {
            /* A train arrives before the earliest departure.
             * Need one more platform. */
            platforms = platforms + 1;
            i = i + 1;

            if (platforms > maxPlatforms) {
                maxPlatforms = platforms;
            }
        } else {
            /* A train departs before the next arrival.
             * One platform is freed. */
            platforms = platforms - 1;
            j = j + 1;
        }
    }

    return maxPlatforms;
}

int main() {
    /*
     * Example:
     *   Arrival:   [900, 940, 950, 1100, 1500, 1800]
     *   Departure: [910, 1200, 1120, 1130, 1900, 2000]
     *
     * Sorted Arrival:   [900, 940, 950, 1100, 1500, 1800]
     * Sorted Departure: [910, 1120, 1130, 1200, 1900, 2000]
     *
     * Timeline:
     *   900  -> train arrives, platforms = 1, max = 1
     *   910  -> train departs, platforms = 0
     *   940  -> train arrives, platforms = 1
     *   950  -> train arrives, platforms = 2, max = 2
     *   1100 -> train arrives, platforms = 3, max = 3
     *   1120 -> train departs, platforms = 2
     *   1130 -> train departs, platforms = 1
     *   1200 -> train departs, platforms = 0
     *   1500 -> train arrives, platforms = 1
     *   1800 -> train arrives, platforms = 2, max = 3
     *   1900 -> train departs, platforms = 1
     *   2000 -> train departs, platforms = 0
     *
     * Answer: 3 platforms
     */

    int n = 6;
    int arrival[6]   = {900, 940, 950, 1100, 1500, 1800};
    int departure[6] = {910, 1200, 1120, 1130, 1900, 2000};

    std::cout << "=== Minimum Platforms ===" << std::endl;
    std::cout << std::endl;
    std::cout << "Train schedule:" << std::endl;

    int i = 0;
    while (i < n) {
        std::cout << "  Train " << (i + 1)
                  << ": arrives=" << arrival[i]
                  << ", departs=" << departure[i] << std::endl;
        i = i + 1;
    }

    std::cout << std::endl;
    std::cout << "Sorted arrivals:   ";
    i = 0;
    while (i < n) {
        std::cout << arrival[i];
        if (i < n - 1) std::cout << ", ";
        i = i + 1;
    }
    std::cout << std::endl;

    std::cout << "Sorted departures: ";
    i = 0;
    while (i < n) {
        std::cout << departure[i];
        if (i < n - 1) std::cout << ", ";
        i = i + 1;
    }
    std::cout << std::endl;

    std::cout << std::endl;

    /* Show the sweep step by step */
    std::cout << "Two-pointer sweep:" << std::endl;

    /* Re-sort for display (arrays were sorted by function) */
    int sortedArrival[6] = {900, 940, 950, 1100, 1500, 1800};
    int sortedDeparture[6] = {910, 1120, 1130, 1200, 1900, 2000};

    int platforms = 1;
    int maxPlatforms = 1;
    int a = 1;
    int d = 0;

    while (a < n && d < n) {
        if (sortedArrival[a] <= sortedDeparture[d]) {
            platforms = platforms + 1;
            std::cout << "  Time " << sortedArrival[a]
                      << " -> train arrives, platforms = " << platforms;
            if (platforms > maxPlatforms) {
                maxPlatforms = platforms;
                std::cout << " (NEW MAX)";
            }
            std::cout << std::endl;
            a = a + 1;
        } else {
            platforms = platforms - 1;
            std::cout << "  Time " << sortedDeparture[d]
                      << " -> train departs, platforms = " << platforms << std::endl;
            d = d + 1;
        }
    }

    int minPlat = findMinPlatforms(arrival, departure, n);
    std::cout << std::endl;
    std::cout << "Minimum platforms needed: " << minPlat << std::endl;

    return 0;
}
