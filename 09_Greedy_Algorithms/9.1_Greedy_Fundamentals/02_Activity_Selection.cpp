/*
 * Activity Selection Problem
 *
 * Given n activities with start and finish times,
 * find the maximum number of activities one person
 * can perform (one at a time).
 *
 * Greedy Strategy:
 *   1. Sort activities by finish time (ascending).
 *   2. Pick the first activity (earliest finish).
 *   3. For each remaining activity, if its start time
 *      is >= finish time of last picked activity, select it.
 *
 * Time  : O(n log n)  for sorting
 * Space : O(1)        beyond input storage
 *
 * Why greedy works here:
 *   By picking the activity that finishes earliest, we
 *   leave maximum remaining time for future activities.
 *   No other choice can leave MORE room for the rest.
 *   This is the "greedy choice property."
 */

#include <iostream>

struct Activity {
    int id;
    int start;
    int finish;
};

/* Bubble sort activities by finish time */
void sortByFinish(Activity arr[], int n) {
    int i = 0;
    while (i < n) {
        int j = 0;
        while (j < n - i - 1) {
            if (arr[j].finish > arr[j + 1].finish) {
                Activity temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            j = j + 1;
        }
        i = i + 1;
    }
}

int activitySelection(Activity arr[], int n, int selected[]) {
    /* Step 1: Sort by finish time */
    sortByFinish(arr, n);

    /* Step 2: Always pick the first activity */
    int count = 1;
    selected[0] = arr[0].id;

    int lastFinish = arr[0].finish;
    int i = 1;
    while (i < n) {
        /* Step 3: If start >= last finish, pick it */
        if (arr[i].start >= lastFinish) {
            selected[count] = arr[i].id;
            count = count + 1;
            lastFinish = arr[i].finish;
        }
        i = i + 1;
    }

    return count;
}

int main() {
    /*
     * Example:
     *   Activity 0: [1, 4]
     *   Activity 1: [3, 5]
     *   Activity 2: [0, 6]
     *   Activity 3: [5, 7]
     *   Activity 4: [3, 9]
     *   Activity 5: [5, 9]
     *   Activity 6: [6, 10]
     *   Activity 7: [8, 11]
     *   Activity 8: [8, 12]
     *   Activity 9: [2, 14]
     *   Activity 10: [12, 16]
     */

    int n = 11;
    Activity activities[11];
    activities[0].id = 0;  activities[0].start = 1;  activities[0].finish = 4;
    activities[1].id = 1;  activities[1].start = 3;  activities[1].finish = 5;
    activities[2].id = 2;  activities[2].start = 0;  activities[2].finish = 6;
    activities[3].id = 3;  activities[3].start = 5;  activities[3].finish = 7;
    activities[4].id = 4;  activities[4].start = 3;  activities[4].finish = 9;
    activities[5].id = 5;  activities[5].start = 5;  activities[5].finish = 9;
    activities[6].id = 6;  activities[6].start = 6;  activities[6].finish = 10;
    activities[7].id = 7;  activities[7].start = 8;  activities[7].finish = 11;
    activities[8].id = 8;  activities[8].start = 8;  activities[8].finish = 12;
    activities[9].id = 9;  activities[9].start = 2;  activities[9].finish = 14;
    activities[10].id = 10; activities[10].start = 12; activities[10].finish = 16;

    std::cout << "=== Activity Selection ===" << std::endl;
    std::cout << std::endl;
    std::cout << "Activities (before sorting):" << std::endl;

    int i = 0;
    while (i < n) {
        std::cout << "  Activity " << activities[i].id
                  << ": [" << activities[i].start
                  << ", " << activities[i].finish << "]" << std::endl;
        i = i + 1;
    }

    std::cout << std::endl;

    /* Array to hold selected activity IDs */
    int selected[11];
    int count = activitySelection(activities, n, selected);

    std::cout << "Maximum activities that can be performed: " << count << std::endl;
    std::cout << "Selected activities: ";

    int j = 0;
    while (j < count) {
        std::cout << selected[j];
        if (j < count - 1) {
            std::cout << ", ";
        }
        j = j + 1;
    }
    std::cout << std::endl;

    /*
     * WHY GREEDY WORKS - Proof Sketch:
     *
     * Let A = {a1, a2, ..., an} sorted by finish time.
     * Let O = optimal solution.
     *
     * Claim: There exists an optimal solution that includes a1
     *        (the activity with earliest finish time).
     *
     * Proof (exchange argument):
     *   Let the first activity in O be ak.
     *   Since a1 finishes before or at same time as ak,
     *   we can replace ak with a1 in O.
     *   a1 finishes earlier, so it leaves AT LEAST as much
     *   room for remaining activities as ak did.
     *   Therefore O' = (O - {ak}) U {a1} is also optimal.
     *
     * This proves that the greedy choice is safe.
     */

    std::cout << std::endl;
    std::cout << "Why greedy works:" << std::endl;
    std::cout << "  By always picking the earliest-finishing activity," << std::endl;
    std::cout << "  we maximize the time remaining for future activities." << std::endl;
    std::cout << "  No other choice can leave more room." << std::endl;

    return 0;
}
