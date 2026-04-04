/*
 * File: 03_Bucket_Sort.cpp
 * Topic: Bucket Sort - Distribute into buckets, sort individually
 * Description: Best for uniformly distributed float data
 */
#include <iostream>
using namespace std;

void insertionSort(float arr[], int n) {
    for (int i = 1; i < n; i++) {
        float key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void bucketSort(float arr[], int n) {
    if (n <= 0) return;

    // Create n buckets
    // Each bucket is an array with max capacity n
    float** buckets = new float*[n];
    int* bucketSizes = new int[n];

    for (int i = 0; i < n; i++) {
        buckets[i] = new float[n];
        bucketSizes[i] = 0;
    }

    // Distribute elements into buckets
    // Assumes values in range [0, 1)
    for (int i = 0; i < n; i++) {
        int bucketIdx = n * arr[i]; // which bucket?
        buckets[bucketIdx][bucketSizes[bucketIdx]] = arr[i];
        bucketSizes[bucketIdx]++;
    }

    // Sort each bucket using insertion sort
    for (int i = 0; i < n; i++) {
        if (bucketSizes[i] > 1) {
            insertionSort(buckets[i], bucketSizes[i]);
        }
    }

    // Concatenate all buckets back into original array
    int idx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bucketSizes[i]; j++) {
            arr[idx] = buckets[i][j];
            idx++;
        }
    }

    // Free memory
    for (int i = 0; i < n; i++) {
        delete[] buckets[i];
    }
    delete[] buckets;
    delete[] bucketSizes;
}

void printArray(float arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Bucket Sort ===" << endl;
    cout << endl;

    float arr[] = {0.89, 0.67, 0.56, 0.12, 0.34, 0.78, 0.90, 0.45};
    int n = 8;

    cout << "Before: ";
    printArray(arr, n);

    bucketSort(arr, n);

    cout << "After:  ";
    printArray(arr, n);

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Create n empty buckets" << endl;
    cout << "  2. Distribute each element into a bucket" << endl;
    cout << "     bucket_idx = n * value (for values in [0,1))" << endl;
    cout << "  3. Sort each bucket individually (insertion sort)" << endl;
    cout << "  4. Concatenate all buckets in order" << endl;
    cout << endl;

    /*
     * 8 buckets for values in [0, 1):
     * Bucket 0 [0.0-0.125): empty
     * Bucket 1 [0.125-0.25): 0.12
     * Bucket 2 [0.25-0.375): 0.34
     * Bucket 3 [0.375-0.5): 0.45
     * Bucket 4 [0.5-0.625): 0.56
     * Bucket 5 [0.625-0.75): 0.67
     * Bucket 6 [0.75-0.875): 0.78, 0.89 (sorted: 0.78, 0.89)
     * Bucket 7 [0.875-1.0): 0.90
     *
     * Concatenate: 0.12 0.34 0.45 0.56 0.67 0.78 0.89 0.90
     */

    cout << "Time: O(n + k) average, O(n^2) worst (all in one bucket)" << endl;
    cout << "Space: O(n + k) for buckets" << endl;
    cout << "Stable: Depends on bucket sort algorithm" << endl;
    cout << "Use: Uniformly distributed float data in known range" << endl;
    cout << "     Example: probabilities, test scores, percentages" << endl;

    return 0;
}
