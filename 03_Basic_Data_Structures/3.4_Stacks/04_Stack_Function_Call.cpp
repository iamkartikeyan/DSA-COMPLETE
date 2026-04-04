/*
 * File: 04_Stack_Function_Call.cpp
 * Topic: Function call stack - how programs work internally
 * Description: LIFO nature of function calls
 */
#include <iostream>
using namespace std;

// These functions demonstrate the call stack
void funcA() {
    cout << "  Entered funcA" << endl;
    cout << "  funcA doing work..." << endl;
    cout << "  Exiting funcA" << endl;
}

void funcB() {
    cout << "  Entered funcB" << endl;
    cout << "  funcB calls funcA..." << endl;
    funcA();
    cout << "  Back in funcB (funcA returned)" << endl;
    cout << "  Exiting funcB" << endl;
}

void funcC() {
    cout << "  Entered funcC" << endl;
    cout << "  funcC calls funcB..." << endl;
    funcB();
    cout << "  Back in funcC (funcB returned)" << endl;
    cout << "  Exiting funcC" << endl;
}

int main() {
    cout << "=== Function Call Stack ===" << endl;
    cout << endl;

    cout << "main() calls funcC(), which calls funcB(), which calls funcA():" << endl;
    cout << endl;

    funcC();

    cout << endl;
    cout << "--- How Call Stack Works ---" << endl;
    cout << "  1. main() is pushed onto call stack" << endl;
    cout << "  2. main() calls funcC() -> funcC pushed" << endl;
    cout << "  3. funcC calls funcB() -> funcB pushed" << endl;
    cout << "  4. funcB calls funcA() -> funcA pushed" << endl;
    cout << "  5. funcA returns -> funcA popped" << endl;
    cout << "  6. funcB resumes -> funcB returns -> popped" << endl;
    cout << "  7. funcC resumes -> funcC returns -> popped" << endl;
    cout << "  8. main() continues" << endl;
    cout << endl;
    cout << "Call Stack:" << endl;
    cout << "  main -> funcC -> funcB -> funcA  (deepest)" << endl;
    cout << "  funcA returns first (LIFO!)" << endl;
    cout << endl;
    cout << "Stack Overflow (infinite recursion):" << endl;
    cout << "  If a function keeps calling itself without base case," << endl;
    cout << "  call stack fills up -> STACK OVERFLOW error" << endl;

    return 0;
}
