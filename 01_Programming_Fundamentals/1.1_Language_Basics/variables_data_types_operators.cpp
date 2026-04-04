#include <iostream>
#include <string>
using namespace std;

int main() {
    // ===== VARIABLES =====
    int age = 25;              // Integer
    double salary = 50000.50;  // Floating point (double precision)
    float pi = 3.14f;          // Floating point (single precision)
    char grade = 'A';          // Single character
    bool isActive = true;      // Boolean (true/false)
    string name = "Kartikey";  // String (requires <string>)

    // ===== DATA TYPES =====
    // Integral types
    short s = 32767;           // 2 bytes: -32768 to 32767
    int i = 2147483647;        // 4 bytes
    long l = 2147483647L;      // 4 or 8 bytes
    long long ll = 9e18;       // 8 bytes

    // Unsigned types (only positive)
    unsigned int ui = 4294967295u;

    // Size of data types
    cout << "Size of int: " << sizeof(int) << " bytes\n";
    cout << "Size of double: " << sizeof(double) << " bytes\n";

    // ===== OPERATORS =====
    int a = 10, b = 3;

    // Arithmetic: +, -, *, /, %
    cout << "a + b = " << a + b << "\n";   // 13
    cout << "a % b = " << a % b << "\n";   // 1

    // Comparison: ==, !=, <, >, <=, >=
    cout << "a > b: " << (a > b) << "\n";  // 1 (true)

    // Logical: &&, ||, !
    cout << "a > 0 && b > 0: " << (a > 0 && b > 0) << "\n";

    // Assignment: =, +=, -=, *=, /=, %=
    a += 5;  // a = a + 5

    // Ternary operator
    int maxVal = (a > b) ? a : b;

    // Bitwise: &, |, ^, ~, <<, >>
    cout << "5 & 3 = " << (5 & 3) << "\n";  // 1

    return 0;
}
