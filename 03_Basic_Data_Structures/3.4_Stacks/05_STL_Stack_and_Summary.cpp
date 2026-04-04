/*
 * File: 05_STL_Stack_and_Summary.cpp
 * Topic: STL stack usage and stack summary
 * Description: How to use stack in competitive programming
 */
#include <iostream>
#include <stack>
using namespace std;

int main() {
    cout << "=== STL Stack & Summary ===" << endl;
    cout << endl;

    // --- STL Stack Demo ---
    cout << "--- STL Stack ---" << endl;
    stack<int> st;

    st.push(10);
    st.push(20);
    st.push(30);

    cout << "Top: " << st.top() << endl;    // 30
    cout << "Size: " << st.size() << endl;  // 3
    cout << "Empty? " << (st.empty() ? "Yes" : "No") << endl;

    cout << "Popping all:" << endl;
    while (st.empty() == false) {
        cout << "  " << st.top();
        st.pop();
    }
    cout << endl;
    cout << endl;

    // --- Common Stack Problems ---
    cout << "--- Common Stack Problems ---" << endl;
    cout << "1.  Valid Parentheses" << endl;
    cout << "2.  Next Greater Element" << endl;
    cout << "3.  Min Stack (get minimum in O(1))" << endl;
    cout << "4.  Postfix/Prefix Evaluation" << endl;
    cout << "5.  Infix to Postfix Conversion" << endl;
    cout << "6.  Stock Span Problem" << endl;
    cout << "7.  Largest Rectangle in Histogram" << endl;
    cout << endl;

    cout << "--- Stack Properties ---" << endl;
    cout << "Principle: LIFO (Last In, First Out)" << endl;
    cout << endl;
    cout << "Operation | Time | Description" << endl;
    cout << "----------|------|---------------------------" << endl;
    cout << "push(x)   | O(1) | Add element on top" << endl;
    cout << "pop()     | O(1) | Remove top element" << endl;
    cout << "top()     | O(1) | See top without removing" << endl;
    cout << "empty()   | O(1) | Check if empty" << endl;
    cout << "size()    | O(1) | Get number of elements" << endl;
    cout << endl;

    cout << "--- Stack Implementations ---" << endl;
    cout << "Array-based:   Fixed size, O(1) all ops" << endl;
    cout << "Vector-based:  Dynamic size, O(1) amortized push" << endl;
    cout << "Linked List:   Dynamic size, O(1) all ops" << endl;
    cout << "STL stack:     Uses deque by default" << endl;

    cout << endl;
    cout << "--- Topics Covered in 3.4 ---" << endl;
    cout << "01. Stack Basics              - push, pop, peek, array impl" << endl;
    cout << "02. Stack Parenthesis Matching - Valid brackets check" << endl;
    cout << "03. Stack Postfix Evaluation  - Reverse Polish Notation" << endl;
    cout << "04. Stack Function Call        - How programs work internally" << endl;
    cout << "05. STL Stack and Summary      - This file" << endl;

    return 0;
}
