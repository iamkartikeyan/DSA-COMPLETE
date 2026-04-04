// ============================================================
// 01_What_Is_Divide_Conquer.cpp
// The Divide and Conquer Paradigm
// ============================================================

#include <iostream>
#include <climits>

using namespace std;

// ============================================================
// DIVIDE AND CONQUER PARADIGM
// ============================================================
//
// Three Steps:
//   1. DIVIDE   - Break the problem into smaller sub-problems
//                  of the same type
//   2. CONQUER  - Solve the sub-problems recursively
//   3. COMBINE  - Merge the sub-problem results into the final answer
//
// General Recurrence Relation:
//   T(n) = a * T(n / b) + f(n)
//
//   where:
//     a  = number of sub-problems
//     n/b = size of each sub-problem
//     f(n) = cost of dividing + combining
//
// ============================================================

// -----------------------------------------------------------
// Example 1: Find maximum element using Divide and Conquer
// -----------------------------------------------------------
//
// Divide:  Split array into left and right halves
// Conquer: Find max in left half and max in right half
// Combine: Return the larger of the two maxes
//
// Recurrence: T(n) = 2*T(n/2) + O(1)
// Time:  O(n)
// Space: O(log n) for recursion stack
// -----------------------------------------------------------

int findMax(int arr[], int low, int high)
{
    // Base case: only one element
    if (low == high)
    {
        return arr[low];
    }

    // Base case: two elements
    if (low + 1 == high)
    {
        if (arr[low] > arr[high])
        {
            return arr[low];
        }
        else
        {
            return arr[high];
        }
    }

    // Divide
    int mid = (low + high) / 2;

    // Conquer
    int leftMax = findMax(arr, low, mid);
    int rightMax = findMax(arr, mid + 1, high);

    // Combine
    if (leftMax > rightMax)
    {
        return leftMax;
    }
    else
    {
        return rightMax;
    }
}

// -----------------------------------------------------------
// Example 2: Find minimum element using Divide and Conquer
// -----------------------------------------------------------
//
// Recurrence: T(n) = 2*T(n/2) + O(1)
// Time:  O(n)
// Space: O(log n) for recursion stack
// -----------------------------------------------------------

int findMin(int arr[], int low, int high)
{
    // Base case: only one element
    if (low == high)
    {
        return arr[low];
    }

    // Base case: two elements
    if (low + 1 == high)
    {
        if (arr[low] < arr[high])
        {
            return arr[low];
        }
        else
        {
            return arr[high];
        }
    }

    // Divide
    int mid = (low + high) / 2;

    // Conquer
    int leftMin = findMin(arr, low, mid);
    int rightMin = findMin(arr, mid + 1, high);

    // Combine
    if (leftMin < rightMin)
    {
        return leftMin;
    }
    else
    {
        return rightMin;
    }
}

// -----------------------------------------------------------
// Example 3: Sum of array using Divide and Conquer
// -----------------------------------------------------------
//
// Divide:  Split array into left and right halves
// Conquer: Compute sum of left half and sum of right half
// Combine: Add the two sums together
//
// Recurrence: T(n) = 2*T(n/2) + O(1)
// Time:  O(n)
// Space: O(log n) for recursion stack
// -----------------------------------------------------------

int arraySum(int arr[], int low, int high)
{
    // Base case: only one element
    if (low == high)
    {
        return arr[low];
    }

    // Divide
    int mid = (low + high) / 2;

    // Conquer
    int leftSum = arraySum(arr, low, mid);
    int rightSum = arraySum(arr, mid + 1, high);

    // Combine
    return leftSum + rightSum;
}

// ============================================================

int main()
{
    cout << "============================================" << endl;
    cout << "  Divide and Conquer Paradigm" << endl;
    cout << "============================================" << endl;
    cout << endl;

    // --- Example 1: Find Max ---
    int arr1[] = {3, 7, 2, 9, 5, 1, 8, 4};
    int n1 = 8;

    cout << "Array: ";
    for (int i = 0; i < n1; i = i + 1)
    {
        cout << arr1[i] << " ";
    }
    cout << endl;

    int maxVal = findMax(arr1, 0, n1 - 1);
    cout << "Maximum (D&C): " << maxVal << endl;
    cout << endl;

    // --- Example 2: Find Min ---
    int arr2[] = {12, 5, 18, 3, 9, 7, 15, 1};
    int n2 = 8;

    cout << "Array: ";
    for (int i = 0; i < n2; i = i + 1)
    {
        cout << arr2[i] << " ";
    }
    cout << endl;

    int minVal = findMin(arr2, 0, n2 - 1);
    cout << "Minimum (D&C): " << minVal << endl;
    cout << endl;

    // --- Example 3: Array Sum ---
    int arr3[] = {4, 2, 7, 1, 8, 3, 6, 5};
    int n3 = 8;

    cout << "Array: ";
    for (int i = 0; i < n3; i = i + 1)
    {
        cout << arr3[i] << " ";
    }
    cout << endl;

    int sum = arraySum(arr3, 0, n3 - 1);
    cout << "Sum (D&C): " << sum << endl;
    cout << endl;

    // --- Key Takeaways ---
    cout << "============================================" << endl;
    cout << "  Key Takeaways" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "1. D&C has three steps: Divide, Conquer, Combine" << endl;
    cout << "2. General recurrence: T(n) = a*T(n/b) + f(n)" << endl;
    cout << "3. All three examples above have T(n) = 2*T(n/2) + O(1)" << endl;
    cout << "4. By Master Theorem, these give O(n) time" << endl;
    cout << "5. Space is O(log n) due to recursion stack" << endl;

    return 0;
}
