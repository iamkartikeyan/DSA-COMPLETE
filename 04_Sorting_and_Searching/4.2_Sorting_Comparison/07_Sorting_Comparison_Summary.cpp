/*
 * File: 07_Sorting_Comparison_Summary.cpp
 * Topic: Complexity table, stability, when to use each sort
 * Description: Complete summary of comparison-based sorting
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Sorting Comparison - Summary ===" << endl;
    cout << endl;

    cout << "--- Complexity Table ---" << endl;
    cout << endl;
    cout << "Algorithm  | Best      | Average   | Worst     | Space    | Stable" << endl;
    cout << "-----------|-----------|-----------|-----------|----------|-------" << endl;
    cout << "Bubble     | O(n)      | O(n^2)    | O(n^2)    | O(1)     | Yes" << endl;
    cout << "Selection  | O(n^2)    | O(n^2)    | O(n^2)    | O(1)     | No" << endl;
    cout << "Insertion  | O(n)      | O(n^2)    | O(n^2)    | O(1)     | Yes" << endl;
    cout << "Merge      | O(n log n)| O(n log n)| O(n log n)| O(n)     | Yes" << endl;
    cout << "Quick      | O(n log n)| O(n log n)| O(n^2)    | O(log n) | No" << endl;
    cout << "Heap       | O(n log n)| O(n log n)| O(n log n)| O(1)     | No" << endl;
    cout << endl;

    cout << "--- Stability ---" << endl;
    cout << "Stable = equal elements keep their original relative order" << endl;
    cout << "Important when sorting by multiple keys" << endl;
    cout << "Example: Sort by name, then by age - stable sort keeps" << endl;
    cout << "         name-order for people with same age" << endl;
    cout << endl;

    cout << "--- When to Use ---" << endl;
    cout << "Bubble:      Educational, tiny arrays" << endl;
    cout << "Selection:   When swaps are expensive" << endl;
    cout << "Insertion:   Small or nearly-sorted data (BEST simple sort)" << endl;
    cout << "Merge:       Stability needed, guaranteed O(n log n)" << endl;
    cout << "Quick:       General purpose (FASTEST in practice)" << endl;
    cout << "Heap:        Guaranteed O(n log n) + in-place" << endl;
    cout << endl;

    cout << "--- Topics Covered in 4.2 ---" << endl;
    cout << "01. Bubble Sort      - Swap adjacent, bubble largest to end" << endl;
    cout << "02. Selection Sort   - Find minimum, swap to front" << endl;
    cout << "03. Insertion Sort   - Insert into sorted portion (like cards)" << endl;
    cout << "04. Merge Sort       - Divide, sort, merge (stable O(n log n))" << endl;
    cout << "05. Quick Sort       - Pivot, partition, recurse (fastest)" << endl;
    cout << "06. Heap Sort        - Build heap, extract max (in-place)" << endl;
    cout << "07. Sorting Summary  - Complexity + stability + when to use" << endl;

    return 0;
}
