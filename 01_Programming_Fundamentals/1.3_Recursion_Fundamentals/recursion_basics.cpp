#include <iostream>
#include <vector>
using namespace std;

// ===== BASE CASE & RECURSIVE CASE =====

// Factorial: n! = n * (n-1)!
int factorial(int n) {
    if (n <= 1) return 1;      // Base case (stops recursion)
    return n * factorial(n - 1); // Recursive case
}

// Fibonacci: F(n) = F(n-1) + F(n-2)
int fibonacci(int n) {
    if (n <= 0) return 0;      // Base case 1
    if (n == 1) return 1;      // Base case 2
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// ===== CALL STACK VISUALIZATION =====
void countdown(int n) {
    cout << "Push: " << n << "\n";  // Before recursive call
    if (n <= 0) {
        cout << "Base case reached!\n";
        return;
    }
    countdown(n - 1);
    cout << "Pop: " << n << "\n";   // After recursive call returns
}

// ===== TAIL RECURSION =====
// Tail recursive: recursive call is LAST operation
int factorialTail(int n, int acc = 1) {
    if (n <= 1) return acc;
    return factorialTail(n - 1, acc * n);  // Last operation
}

// Non-tail recursive: work after recursive call
int factorialNonTail(int n) {
    if (n <= 1) return 1;
    return n * factorialNonTail(n - 1);  // Multiplication after call
}

// ===== RECURSION TREE =====
// Sum of array elements
int sumArray(vector<int>& arr, int idx) {
    if (idx >= arr.size()) return 0;  // Base case
    return arr[idx] + sumArray(arr, idx + 1);
}

// Binary search (recursive)
int binarySearch(vector<int>& arr, int low, int high, int target) {
    if (low > high) return -1;  // Base case: not found
    int mid = low + (high - low) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] > target)
        return binarySearch(arr, low, mid - 1, target);
    return binarySearch(arr, mid + 1, high, target);
}

// Power function: x^n
double power(double x, int n) {
    if (n == 0) return 1;
    if (n < 0) return 1 / power(x, -n);
    double half = power(x, n / 2);
    return (n % 2 == 0) ? half * half : x * half * half;
}

int main() {
    cout << "Factorial(5): " << factorial(5) << "\n";  // 120
    cout << "Fibonacci(6): " << fibonacci(6) << "\n";  // 8

    cout << "\n=== Call Stack Demo ===\n";
    countdown(3);

    cout << "\n=== Tail vs Non-Tail ===\n";
    cout << "Tail factorial(5): " << factorialTail(5) << "\n";
    cout << "Non-tail factorial(5): " << factorialNonTail(5) << "\n";

    cout << "\n=== Recursion Applications ===\n";
    vector<int> arr = {1, 2, 3, 4, 5};
    cout << "Sum: " << sumArray(arr, 0) << "\n";  // 15

    vector<int> sorted = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    cout << "Binary search 23: index " << binarySearch(sorted, 0, 9, 23) << "\n";

    cout << "2^10: " << power(2, 10) << "\n";  // 1024

    return 0;
}
