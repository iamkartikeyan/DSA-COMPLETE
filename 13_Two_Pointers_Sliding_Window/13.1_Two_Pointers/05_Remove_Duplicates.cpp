// 13.1 - Remove Duplicates from Sorted Array
// Slow pointer = write position, Fast pointer = read position.
// O(n) time, O(1) extra space.
// Standalone compilable file with basic C++ only.

#include <iostream>
using namespace std;

// Removes duplicates in-place, returns new length
int removeDuplicates(int arr[], int n) {
    if (n == 0) return 0;

    int slow = 1;  // Write position (first element always kept)
    for (int fast = 1; fast < n; fast++) {
        if (arr[fast] != arr[fast - 1]) {
            // Found a new unique element
            arr[slow] = arr[fast];
            slow++;
        }
    }
    return slow;  // New length of unique portion
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Remove Duplicates from Sorted Array ===" << endl;
    cout << endl;

    int arr[] = {1, 1, 2, 2, 3, 4, 4, 5};
    int n = 8;

    cout << "Before: ";
    printArray(arr, n);
    cout << endl;

    cout << "Approach: Same Direction (fast/slow pointers)" << endl;
    cout << "  - slow = write position for next unique element" << endl;
    cout << "  - fast = read position scanning the array" << endl;
    cout << "  - When arr[fast] != arr[fast-1], we found a new unique" << endl;
    cout << "  - Write it at arr[slow] and increment slow" << endl;
    cout << "  - Time: O(n), Space: O(1)" << endl;
    cout << endl;

    // Step-by-step trace
    cout << "Step-by-step:" << endl;
    cout << "  i=0: arr[0]=1 (always kept)" << endl;
    cout << "  fast=1: arr[1]=1 == arr[0]=1 -> skip" << endl;
    cout << "  fast=2: arr[2]=2 != arr[1]=1 -> write at slow=1, slow=2" << endl;
    cout << "  fast=3: arr[3]=2 == arr[2]=2 -> skip" << endl;
    cout << "  fast=4: arr[4]=3 != arr[3]=2 -> write at slow=2, slow=3" << endl;
    cout << "  fast=5: arr[5]=4 != arr[4]=3 -> write at slow=3, slow=4" << endl;
    cout << "  fast=6: arr[6]=4 == arr[5]=4 -> skip" << endl;
    cout << "  fast=7: arr[7]=5 != arr[6]=4 -> write at slow=4, slow=5" << endl;
    cout << endl;

    int newLen = removeDuplicates(arr, n);

    cout << "After:  ";
    printArray(arr, newLen);
    cout << "New length: " << newLen << endl;
    cout << endl;

    // Second example
    int arr2[] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int n2 = 10;
    cout << "Input:  ";
    printArray(arr2, n2);
    int newLen2 = removeDuplicates(arr2, n2);
    cout << "Output: ";
    printArray(arr2, newLen2);
    cout << "New length: " << newLen2 << endl;

    return 0;
}
