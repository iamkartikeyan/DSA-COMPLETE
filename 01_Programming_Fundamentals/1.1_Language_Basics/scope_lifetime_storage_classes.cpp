#include <iostream>
using namespace std;

// ===== STORAGE CLASSES =====

// Global variable (exists throughout program)
int globalVar = 100;

// Static global (file scope only)
static int fileStaticVar = 50;

void scopeDemo() {
    // Local variable (exists only in this function)
    int localVar = 10;

    // Static local (persists across calls)
    static int staticLocalVar = 0;
    staticLocalVar++;

    cout << "localVar: " << localVar << ", staticLocalVar: " << staticLocalVar << "\n";
}

void staticVsAuto() {
    auto autoVar = 5;     // Automatic (default for locals) - C++11
    register regVar = 10; // Hint to store in CPU register (deprecated in C++17)

    cout << "autoVar: " << autoVar << "\n";
}

// Extern variable (defined elsewhere, declared here)
extern int globalVar;  // Just a declaration, not definition

int main() {
    // ===== SCOPE =====
    // Block scope
    {
        int x = 10;
        cout << "Inside block: x = " << x << "\n";
    }
    // x is out of scope here

    // Function scope
    scopeDemo();
    scopeDemo();  // staticLocalVar retains value
    scopeDemo();  // Will print 3

    // Global scope
    cout << "globalVar: " << globalVar << "\n";

    // ===== LIFETIME =====
    // Automatic: Created on entry, destroyed on exit
    // Static: Created once, exists until program ends
    // Dynamic: Created with new, destroyed with delete

    int *dynamicVar = new int(42);  // Heap allocation
    cout << "Dynamic: " << *dynamicVar << "\n";
    delete dynamicVar;  // Manual cleanup

    // ===== STORAGE CLASSES SUMMARY =====
    // auto:       Default for locals, stack, function scope
    // register:   Hint for CPU register (mostly ignored by compiler)
    // static:     Persists across calls, initialized once
    // extern:     Declares variable defined in another file
    // mutable:    Allows modification in const member functions

    return 0;
}
