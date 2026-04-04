#include <iostream>
#include <string>
using namespace std;

// ===== FUNCTION DECLARATION (Prototype) =====
int add(int a, int b);
void greet(string name);
int multiply(int a, int b = 1);  // Default parameter

// ===== FUNCTION DEFINITION =====
int add(int a, int b) {
    return a + b;
}

void greet(string name) {
    cout << "Hello, " << name << "!\n";
}

int multiply(int a, int b) {
    return a * b;
}

// Function with reference parameter (modifies original)
void swapByRef(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Function with pointer parameter
void swapByPtr(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function returning multiple values via reference
void getMinMax(int arr[], int n, int &minVal, int &maxVal) {
    minVal = maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }
}

// Recursive function
int factorial(int n) {
    if (n <= 1) return 1;       // Base case
    return n * factorial(n - 1); // Recursive case
}

// Inline function (compiler may optimize)
inline int square(int x) {
    return x * x;
}

// Function overloading (same name, different params)
int add(int a, int b) {
    return a + b;
}
double add(double a, double b) {
    return a + b;
}
string add(string a, string b) {
    return a + b;
}

int main() {
    // Function calls
    cout << "Add: " << add(5, 3) << "\n";
    greet("Kartikey");
    cout << "Multiply (default): " << multiply(5) << "\n";
    cout << "Multiply: " << multiply(5, 3) << "\n";

    // Pass by reference
    int a = 10, b = 20;
    swapByRef(a, b);
    cout << "After swapByRef: " << a << ", " << b << "\n";

    // Pass by pointer
    swapByPtr(&a, &b);
    cout << "After swapByPtr: " << a << ", " << b << "\n";

    // Multiple return values
    int arr[] = {5, 2, 9, 1, 7};
    int minVal, maxVal;
    getMinMax(arr, 5, minVal, maxVal);
    cout << "Min: " << minVal << ", Max: " << maxVal << "\n";

    // Recursive
    cout << "Factorial(5): " << factorial(5) << "\n";

    // Inline
    cout << "Square(4): " << square(4) << "\n";

    // Overloading
    cout << "add(int): " << add(1, 2) << "\n";
    cout << "add(double): " << add(1.5, 2.5) << "\n";
    cout << "add(string): " << add("Hello", " World") << "\n";

    return 0;
}
