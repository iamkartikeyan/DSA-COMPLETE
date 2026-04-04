#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    // ===== DYNAMIC MEMORY ALLOCATION =====

    // --- C++ Style: new / delete ---

    // Single variable
    int *p1 = new int(42);
    cout << "Single int: " << *p1 << "\n";
    delete p1;

    // Array
    int *arr = new int[5]{1, 2, 3, 4, 5};
    cout << "Array: ";
    for (int i = 0; i < 5; i++) cout << arr[i] << " ";
    cout << "\n";
    delete[] arr;  // Must use delete[] for arrays

    // 2D Array
    int rows = 3, cols = 4;
    int **matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j;
        }
    }
    // Cleanup 2D array
    for (int i = 0; i < rows; i++) delete[] matrix[i];
    delete[] matrix;

    // --- C Style: malloc / free ---
    int *m1 = (int*)malloc(sizeof(int));
    *m1 = 100;
    cout << "malloc: " << *m1 << "\n";
    free(m1);

    int *m2 = (int*)calloc(5, sizeof(int));  // Zero-initialized
    cout << "calloc: " << m2[0] << "\n";
    free(m2);

    int *m3 = (int*)malloc(3 * sizeof(int));
    m3[0] = 1; m3[1] = 2; m3[2] = 3;
    m3 = (int*)realloc(m3, 5 * sizeof(int));  // Resize
    m3[3] = 4; m3[4] = 5;
    free(m3);

    // ===== MEMORY LEAKS =====
    // Leak: allocating without freeing
    // int *leak = new int(10);
    // leak = new int(20);  // Original 10 is lost! MEMORY LEAK

    // Proper pattern
    int *safe = new int(10);
    delete safe;
    safe = new int(20);
    delete safe;
    safe = nullptr;  // Good practice after delete

    // ===== DANGLING POINTERS =====
    int *dangling = new int(42);
    delete dangling;
    // dangling is now dangling - points to freed memory
    dangling = nullptr;  // Prevents dangling pointer issues

    // ===== SMART POINTERS (C++11, recommended) =====
    // #include <memory>
    // unique_ptr: Exclusive ownership
    // shared_ptr: Shared ownership (ref count)
    // weak_ptr: Non-owning reference

    return 0;
}
