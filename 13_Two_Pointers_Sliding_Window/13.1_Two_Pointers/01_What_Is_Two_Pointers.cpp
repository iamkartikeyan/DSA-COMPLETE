// 13.1 - What Is Two Pointers?
// Explains the two pointers technique, its patterns, and when to use it.
// Standalone compilable file with basic C++ only.

#include <iostream>
using namespace std;

int main() {
    cout << "=== Two Pointers Technique ===" << endl;
    cout << endl;

    cout << "WHAT IS IT?" << endl;
    cout << "  Use two indices (pointers) to traverse a data structure" << endl;
    cout << "  in a single pass, avoiding nested loops." << endl;
    cout << endl;

    cout << "PATTERN 1: Opposite Ends (converging pointers)" << endl;
    cout << "  - left starts at 0, right starts at n-1" << endl;
    cout << "  - move left++ or right-- based on condition" << endl;
    cout << "  - stop when left >= right" << endl;
    cout << "  - REQUIRES sorted array (or sort first)" << endl;
    cout << "  Examples: pair sum, three sum, container with most water," << endl;
    cout << "            palindrome check, array reverse" << endl;
    cout << endl;
    cout << "  Template:" << endl;
    cout << "    int left = 0, right = n - 1;" << endl;
    cout << "    while (left < right) {" << endl;
    cout << "        if (condition) left++;" << endl;
    cout << "        else right--;" << endl;
    cout << "    }" << endl;
    cout << endl;

    cout << "PATTERN 2: Same Direction (fast/slow pointers)" << endl;
    cout << "  - both start at 0, move at different speeds" << endl;
    cout << "  - slow = write position, fast = read position" << endl;
    cout << "  - fast always >= slow" << endl;
    cout << "  Examples: remove duplicates, move zeroes," << endl;
    cout << "            partition array, detect cycle (linked list)" << endl;
    cout << endl;
    cout << "  Template:" << endl;
    cout << "    int slow = 0;" << endl;
    cout << "    for (int fast = 0; fast < n; fast++) {" << endl;
    cout << "        if (should_keep(fast)) {" << endl;
    cout << "            arr[slow++] = arr[fast];" << endl;
    cout << "        }" << endl;
    cout << "    }" << endl;
    cout << endl;

    cout << "WHEN TO USE:" << endl;
    cout << "  - Sorted array, looking for pairs or triplets" << endl;
    cout << "  - Need to reduce O(n^2) nested loops to O(n)" << endl;
    cout << "  - In-place array modification (remove, partition)" << endl;
    cout << "  - Palindrome or symmetry checking" << endl;
    cout << "  - Merging two sorted sequences" << endl;
    cout << endl;

    cout << "DEMONSTRATION - Opposite Ends on sorted array:" << endl;
    int arr[] = {2, 4, 6, 8, 10, 12};
    int n = 6;
    int left = 0;
    int right = n - 1;
    while (left < right) {
        cout << "  left=" << arr[left] << ", right=" << arr[right] << endl;
        left++;
        right--;
    }
    cout << endl;

    cout << "DEMONSTRATION - Same Direction (remove even numbers):" << endl;
    int data[] = {1, 2, 3, 4, 5, 6, 7};
    int len = 7;
    int slow = 0;
    for (int fast = 0; fast < len; fast++) {
        if (data[fast] % 2 != 0) {
            data[slow++] = data[fast];
        }
    }
    cout << "  Odd numbers: ";
    for (int i = 0; i < slow; i++) {
        cout << data[i] << " ";
    }
    cout << endl;

    return 0;
}
