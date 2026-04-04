/*
 * File: 01_Stack_Basics.cpp
 * Topic: What is Stack, LIFO principle, array-based implementation
 * Description: push, pop, peek, isEmpty, size
 */
#include <iostream>
using namespace std;

class MyStack {
    int* arr;
    int top;
    int capacity;

public:
    MyStack(int cap) {
        capacity = cap;
        top = -1;
        arr = new int[capacity];
    }

    ~MyStack() {
        delete[] arr;
    }

    // Push: add element on top
    void push(int val) {
        if (top == capacity - 1) {
            cout << "  Stack Overflow! Cannot push " << val << endl;
            return;
        }
        top = top + 1;
        arr[top] = val;
        cout << "  Pushed " << val << endl;
    }

    // Pop: remove top element
    int pop() {
        if (top == -1) {
            cout << "  Stack Underflow! Cannot pop." << endl;
            return -1;
        }
        int val = arr[top];
        top = top - 1;
        return val;
    }

    // Peek: see top element without removing
    int peek() {
        if (top == -1) {
            cout << "  Stack is empty!" << endl;
            return -1;
        }
        return arr[top];
    }

    bool isEmpty() {
        return top == -1;
    }

    int size() {
        return top + 1;
    }
};

int main() {
    cout << "=== Stack Basics ===" << endl;
    cout << endl;

    MyStack st(5);

    // Push elements
    cout << "--- Push Operations ---" << endl;
    st.push(10);
    st.push(20);
    st.push(30);
    cout << endl;

    // Peek
    cout << "--- Peek ---" << endl;
    cout << "Top element: " << st.peek() << endl;
    cout << endl;

    // Pop
    cout << "--- Pop Operations ---" << endl;
    cout << "Popped: " << st.pop() << endl;
    cout << "Popped: " << st.pop() << endl;
    cout << "New top: " << st.peek() << endl;
    cout << endl;

    // Size and empty
    cout << "--- Status ---" << endl;
    cout << "Size: " << st.size() << endl;
    cout << "Empty? " << (st.isEmpty() ? "Yes" : "No") << endl;

    cout << endl;
    cout << "--- Stack Properties ---" << endl;
    cout << "LIFO: Last In, First Out" << endl;
    cout << "Think of it like a stack of plates - you remove from top." << endl;
    cout << endl;
    cout << "Operations:" << endl;
    cout << "  push(x)  - Add x on top       O(1)" << endl;
    cout << "  pop()    - Remove top element   O(1)" << endl;
    cout << "  peek()   - See top element      O(1)" << endl;
    cout << "  isEmpty  - Check if empty       O(1)" << endl;
    cout << "  size()   - Get size             O(1)" << endl;

    return 0;
}
