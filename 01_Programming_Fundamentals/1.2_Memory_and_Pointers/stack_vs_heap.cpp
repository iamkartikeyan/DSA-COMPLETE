#include <iostream>
#include <cstdlib>
using namespace std;

// ===== STACK VS HEAP MEMORY =====

// Stack allocation: Automatic, limited size, fast, freed automatically
void stackDemo() {
    int x = 10;             // Stack
    double arr[100];        // Stack (limited size ~1-8MB)
    cout << "Stack variable: " << x << "\n";
} // x and arr automatically freed

// Heap allocation: Manual, large size, slower, must free manually
void heapDemo() {
    // Dynamic allocation
    int *ptr = new int(42);         // Single int on heap
    int *arr = new int[1000000];    // Large array on heap

    cout << "Heap value: " << *ptr << "\n";

    // Must free manually
    delete ptr;
    delete[] arr;  // Use delete[] for arrays
}

// Stack vs Heap comparison
void compareStackHeap() {
    // STACK (fast, limited, auto cleanup)
    int stackVar = 100;
    cout << "Stack address: " << &stackVar << "\n";

    // HEAP (slower, large, manual cleanup)
    int *heapVar = new int(100);
    cout << "Heap address: " << heapVar << "\n";
    cout << "Heap value: " << *heapVar << "\n";
    delete heapVar;
}

int main() {
    // ===== STACK MEMORY =====
    // - Managed automatically
    // - LIFO order
    // - Limited size (typically 1-8 MB)
    // - Fast allocation/deallocation
    // - Local variables, function calls

    int a = 10;  // Stack
    double b = 3.14;  // Stack
    char str[] = "Hello";  // Stack

    // ===== HEAP MEMORY =====
    // - Managed manually (new/delete or malloc/free)
    // - Large available memory
    // - Slower allocation
    // - No automatic cleanup

    // C++ style: new / delete
    int *p1 = new int(5);
    int *p2 = new int[10];
    delete p1;
    delete[] p2;

    // C style: malloc / free
    int *p3 = (int*)malloc(sizeof(int));
    *p3 = 15;
    int *p4 = (int*)calloc(10, sizeof(int));  // Zero-initialized
    free(p3);
    free(p4);

    // realloc: resize allocation
    int *p5 = (int*)malloc(5 * sizeof(int));
    p5 = (int*)realloc(p5, 10 * sizeof(int));
    free(p5);

    compareStackHeap();

    return 0;
}
