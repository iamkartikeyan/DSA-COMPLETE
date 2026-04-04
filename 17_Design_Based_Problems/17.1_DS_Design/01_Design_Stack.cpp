// 17.1.01 - Design Stack
// Stack: LIFO (Last In, First Out) data structure.
// Operations: push, pop, peek, isEmpty, size.
// Time: all O(1). Space: O(n).

#include <iostream>

using namespace std;

const int MAX_SIZE = 1000;

class Stack {
private:
    int data[MAX_SIZE];
    int topIndex;

public:
    Stack() {
        topIndex = -1;
    }

    // Push element onto stack
    void push(int val) {
        if (topIndex >= MAX_SIZE - 1) {
            cout << "Stack overflow!" << endl;
            return;
        }
        topIndex++;
        data[topIndex] = val;
    }

    // Pop element from stack
    int pop() {
        if (isEmpty()) {
            cout << "Stack underflow!" << endl;
            return -1;
        }
        int val = data[topIndex];
        topIndex--;
        return val;
    }

    // Peek top element without removing
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return data[topIndex];
    }

    // Check if stack is empty
    bool isEmpty() {
        return topIndex == -1;
    }

    // Get number of elements
    int size() {
        return topIndex + 1;
    }

    // Display stack contents
    void display() {
        if (isEmpty()) {
            cout << "  Stack is empty" << endl;
            return;
        }
        cout << "  Stack (top to bottom): ";
        for (int i = topIndex; i >= 0; i--) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    cout << "=== Stack Implementation ===" << endl;

    Stack st;
    cout << "Empty? " << (st.isEmpty() ? "Yes" : "No") << endl;

    // Push
    cout << endl << "Pushing 10, 20, 30:" << endl;
    st.push(10);
    st.push(20);
    st.push(30);
    st.display();

    // Peek
    cout << "Peek: " << st.peek() << endl;  // 30
    cout << "Size: " << st.size() << endl;  // 3

    // Pop
    cout << endl << "Pop: " << st.pop() << endl;  // 30
    cout << "Pop: " << st.pop() << endl;  // 20
    st.display();

    cout << "Size: " << st.size() << endl;  // 1

    // Pop remaining
    cout << "Pop: " << st.pop() << endl;  // 10
    cout << "Empty? " << (st.isEmpty() ? "Yes" : "No") << endl;

    cout << endl << "Time: push/pop/peek/isEmpty/size = O(1)" << endl;
    cout << "Space: O(n) for array storage" << endl;

    return 0;
}
