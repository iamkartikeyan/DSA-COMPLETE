#include <iostream>
using namespace std;

// ===== REFERENCES VS POINTERS =====

// Reference: alias for another variable
void referenceDemo() {
    int x = 10;
    int &ref = x;  // ref is an alias for x

    cout << "x = " << x << ", ref = " << ref << "\n";  // 10, 10
    ref = 20;
    cout << "After ref = 20, x = " << x << "\n";  // 20
    cout << "Address same? " << (&x == &ref) << "\n";  // 1 (true)
}

// Key differences demo
void differencesDemo() {
    int a = 10, b = 20;

    // REFERENCE
    int &refA = a;
    // refA = b;  // This modifies a, not rebinds! refA is still alias of a
    refA = b;  // a = 20
    cout << "a = " << a << " (was changed via ref)\n";

    // POINTER
    int *ptrA = &a;
    ptrA = &b;  // Can reassign to point to different variable
    cout << "ptrA now points to b: " << *ptrA << "\n";
}

// Pass by value (copy)
void passByValue(int x) {
    x = 100;  // Only modifies copy
}

// Pass by reference (no copy, modifies original)
void passByRef(int &x) {
    x = 100;  // Modifies original
}

// Pass by pointer (can be null)
void passByPtr(int *x) {
    if (x != nullptr) {
        *x = 100;
    }
}

// Return by reference (efficient for large objects)
int& getElement(int arr[], int index) {
    return arr[index];  // Return reference to element
}

int main() {
    referenceDemo();
    cout << "\n";
    differencesDemo();

    cout << "\n=== Passing to functions ===\n";
    int val = 10;
    passByValue(val);
    cout << "After passByValue: " << val << "\n";  // 10 (unchanged)

    passByRef(val);
    cout << "After passByRef: " << val << "\n";  // 100

    val = 10;
    passByPtr(&val);
    cout << "After passByPtr: " << val << "\n";  // 100

    // Reference to array element
    int arr[] = {1, 2, 3, 4, 5};
    int &elem = getElement(arr, 2);
    cout << "\nElement at index 2: " << elem << "\n";  // 3
    elem = 99;  // Modifies array directly
    cout << "After elem = 99, arr[2] = " << arr[2] << "\n";  // 99

    // SUMMARY:
    // Reference: Must be initialized, can't be null, can't rebind, cleaner syntax
    // Pointer: Can be null, can reassign, explicit dereferencing, more flexible

    return 0;
}
