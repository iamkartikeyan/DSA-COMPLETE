// 13.1 - Move Zeroes
// Move all zeroes to the end while maintaining relative order of non-zeroes.
// Slow tracks non-zero position, fast scans. In-place, O(n).
// Standalone compilable file with basic C++ only.

#include <iostream>
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void moveZeroes(int arr[], int n) {
    int slow = 0;  // Position for next non-zero element
    for (int fast = 0; fast < n; fast++) {
        if (arr[fast] != 0) {
            swap(arr[slow], arr[fast]);
            slow++;
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Move Zeroes to End ===" << endl;
    cout << endl;

    int arr[] = {0, 1, 0, 3, 12};
    int n = 5;

    cout << "Before: ";
    printArray(arr, n);
    cout << endl;

    cout << "Approach: Same Direction (slow/fast pointers)" << endl;
    cout << "  - slow = position where next non-zero should go" << endl;
    cout << "  - fast = scans through array" << endl;
    cout << "  - When arr[fast] is non-zero, swap with arr[slow]" << endl;
    cout << "  - This pushes zeroes to the end naturally" << endl;
    cout << "  - Time: O(n), Space: O(1), In-place" << endl;
    cout << endl;

    // Step-by-step trace
    cout << "Step-by-step for {0, 1, 0, 3, 12}:" << endl;
    cout << "  fast=0: arr[0]=0 -> skip (slow=0)" << endl;
    cout << "  fast=1: arr[1]=1 != 0 -> swap(0,1) -> {1,0,0,3,12}, slow=1" << endl;
    cout << "  fast=2: arr[2]=0 -> skip (slow=1)" << endl;
    cout << "  fast=3: arr[3]=3 != 0 -> swap(1,3) -> {1,3,0,0,12}, slow=2" << endl;
    cout << "  fast=4: arr[4]=12 != 0 -> swap(2,4) -> {1,3,12,0,0}, slow=3" << endl;
    cout << endl;

    moveZeroes(arr, n);

    cout << "After:  ";
    printArray(arr, n);
    cout << endl;

    // Second example
    int arr2[] = {0, 0, 1};
    int n2 = 3;
    cout << "Before: ";
    printArray(arr2, n2);
    moveZeroes(arr2, n2);
    cout << "After:  ";
    printArray(arr2, n2);
    cout << endl;

    // Third example: all non-zero
    int arr3[] = {1, 2, 3};
    int n3 = 3;
    cout << "Before: ";
    printArray(arr3, n3);
    moveZeroes(arr3, n3);
    cout << "After:  ";
    printArray(arr3, n3);

    return 0;
}
