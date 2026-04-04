// 13.1 - Three Sum
// Find all unique triplets that sum to zero.
// Fix one element, use two pointers for the rest. Skip duplicates.
// Standalone compilable file with basic C++ only.

#include <iostream>
using namespace std;

// Simple bubble sort for the array
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

// Three sum: O(n^2)
// Returns count of triplets found, stores them in result arrays
int threeSum(int arr[], int n, int result[][3]) {
    sortArray(arr, n);
    int count = 0;

    for (int i = 0; i < n - 2; i++) {
        // Skip duplicate fixed elements
        if (i > 0 && arr[i] == arr[i - 1]) {
            continue;
        }

        int left = i + 1;
        int right = n - 1;

        while (left < right) {
            int sum = arr[i] + arr[left] + arr[right];

            if (sum == 0) {
                result[count][0] = arr[i];
                result[count][1] = arr[left];
                result[count][2] = arr[right];
                count++;

                // Skip duplicate left values
                while (left < right && arr[left] == arr[left + 1]) {
                    left++;
                }
                // Skip duplicate right values
                while (left < right && arr[right] == arr[right - 1]) {
                    right--;
                }
                left++;
                right--;
            } else if (sum < 0) {
                left++;   // Need larger sum
            } else {
                right--;  // Need smaller sum
            }
        }
    }
    return count;
}

int main() {
    cout << "=== Three Sum (Triplets Summing to Zero) ===" << endl;
    cout << endl;

    int arr[] = {-1, 0, 1, 2, -1, -4};
    int n = 6;

    cout << "Input: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << endl;

    cout << "Approach:" << endl;
    cout << "  1. Sort the array first" << endl;
    cout << "  2. Fix arr[i], then use two pointers for arr[i+1..n-1]" << endl;
    cout << "  3. Skip duplicates at every level to avoid repeated triplets" << endl;
    cout << "  4. Time: O(n^2), Space: O(1)" << endl;
    cout << endl;

    // Result storage: max n triplets possible
    int result[20][3];
    int count = threeSum(arr, n, result);

    cout << "Found " << count << " triplet(s):" << endl;
    for (int i = 0; i < count; i++) {
        cout << "  [" << result[i][0] << ", "
             << result[i][1] << ", "
             << result[i][2] << "]" << endl;
    }
    cout << endl;

    // Second example with no valid triplets
    int arr2[] = {1, 2, 3, 4};
    int n2 = 4;
    cout << "Input: ";
    for (int i = 0; i < n2; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;

    int result2[20][3];
    int count2 = threeSum(arr2, n2, result2);
    cout << "Found " << count2 << " triplet(s) summing to 0" << endl;

    return 0;
}
