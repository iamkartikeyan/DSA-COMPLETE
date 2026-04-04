#include <iostream>
using namespace std;

int main() {
    int num = 42;
    int *ptr;  // Pointer declaration

    // ===== POINTER BASICS =====
    ptr = &num;  // Address-of operator

    cout << "Value of num: " << num << "\n";          // 42
    cout << "Address of num: " << &num << "\n";       // Memory address
    cout << "Value of ptr: " << ptr << "\n";           // Same address
    cout << "Value at ptr (dereference): " << *ptr << "\n";  // 42

    // ===== DEREFERENCING =====
    *ptr = 100;  // Modify value through pointer
    cout << "After *ptr = 100, num = " << num << "\n";  // 100

    // ===== POINTER ARITHMETIC =====
    int arr[] = {10, 20, 30, 40, 50};
    int *arrPtr = arr;  // Points to arr[0]

    cout << "\nPointer arithmetic:\n";
    cout << "arrPtr (arr[0]): " << *arrPtr << "\n";     // 10
    cout << "*(arrPtr+1): " << *(arrPtr + 1) << "\n";   // 20
    cout << "*(arrPtr+2): " << *(arrPtr + 2) << "\n";   // 30

    // Traverse array with pointer
    for (int i = 0; i < 5; i++) {
        cout << *(arrPtr + i) << " ";
    }
    cout << "\n";

    // Pointer increment/decrement
    int *p = arr;
    p++;  // Moves to next int (4 bytes ahead)
    cout << "After p++: " << *p << "\n";  // 20
    p--;  // Moves back
    cout << "After p--: " << *p << "\n";  // 10

    // ===== POINTER TO POINTER =====
    int **doublePtr = &ptr;
    cout << "\nDouble pointer: " << **doublePtr << "\n";  // 100

    // ===== CONST POINTERS =====
    const int *ptrToConst = &num;     // Can't change value through pointer
    int *const constPtr = &num;       // Can't change pointer itself
    const int *const constPtrToConst = &num;  // Both fixed

    // ===== NULL POINTER =====
    int *nullPtr = nullptr;  // C++11 (use NULL in older versions)
    if (nullPtr == nullptr) {
        cout << "Pointer is null\n";
    }

    // ===== VOID POINTER =====
    void *voidPtr = &num;  // Can point to any type
    cout << "Void ptr value: " << *(int*)voidPtr << "\n";  // Must cast to use

    return 0;
}
