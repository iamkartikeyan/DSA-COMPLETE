/*
 * File: 04_Jump_Search.cpp
 * Topic: Jump Search - Jump ahead by blocks
 * Description: Between linear and binary search
 */
#include <iostream>
#include <cmath>
using namespace std;

int minVal(int a, int b) {
    if (a < b) return a;
    return b;
}

// Jump Search
int jumpSearch(int arr[], int n, int target) {
    // Optimal step size = sqrt(n)
    int step = sqrt(n);
    int prev = 0;

    // Jump forward until we find a block that could contain target
    while (arr[minVal(step, n) - 1] < target) {
        prev = step;
        step = step + sqrt(n);
        if (prev >= n) {
            return -1; // past end of array
        }
    }

    // Linear search within the identified block
    for (int i = prev; i < minVal(step, n); i++) {
        if (arr[i] == target) {
            return i;
        }
    }

    return -1; // not found
}

int main() {
    cout << "=== Jump Search ===" << endl;
    cout << endl;

    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = 10;

    cout << "Array: 2 5 8 12 16 23 38 56 72 91" << endl;
    cout << "Step size = sqrt(10) = " << (int)sqrt(n) << endl;
    cout << endl;

    int target = 23;
    int idx = jumpSearch(arr, n, target);
    if (idx != -1) {
        cout << "Search " << target << ": Found at index " << idx << endl;
    } else {
        cout << "Search " << target << ": Not found" << endl;
    }

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Jump ahead by sqrt(n) steps" << endl;
    cout << "  2. When you overshoot target, go back one block" << endl;
    cout << "  3. Linear search within that block" << endl;
    cout << endl;

    /*
     * Example with step=3, target=23:
     * Jump 0->3: arr[3]=12 < 23, keep jumping
     * Jump 3->6: arr[6]=38 >= 23, stop
     * Linear search in [3,6): 12, 16, 23 -> found!
     */

    cout << "Time: O(sqrt(n))" << endl;
    cout << "Space: O(1)" << endl;
    cout << "Requires: Sorted array" << endl;
    cout << "Use: When jumping is cheaper than full binary search" << endl;

    return 0;
}
