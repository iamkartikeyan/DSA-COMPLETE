// 17.1.03 - Design Min Stack
// Stack that supports getMin() in O(1) time.
// Uses auxiliary stack to track minimum values.
// Operations: push, pop, top, getMin - all O(1).

#include <iostream>

using namespace std;

const int MAX_SIZE = 1000;

class MinStack {
private:
    int data[MAX_SIZE];       // Main stack
    int minData[MAX_SIZE];    // Auxiliary stack for minimums
    int topIndex;

public:
    MinStack() {
        topIndex = -1;
    }

    // Push element and update minimum
    void push(int val) {
        if (topIndex >= MAX_SIZE - 1) {
            cout << "Stack overflow!" << endl;
            return;
        }
        topIndex++;
        data[topIndex] = val;

        // Push to min stack: min of val and current min
        if (topIndex == 0) {
            minData[topIndex] = val;
        } else {
            minData[topIndex] = (val < minData[topIndex - 1]) ? val : minData[topIndex - 1];
        }
    }

    // Pop from both stacks
    int pop() {
        if (isEmpty()) {
            cout << "Stack underflow!" << endl;
            return -1;
        }
        int val = data[topIndex];
        topIndex--;
        return val;
    }

    // Get top element
    int top() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return data[topIndex];
    }

    // Get minimum element in O(1)
    int getMin() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return minData[topIndex];
    }

    // Check if empty
    bool isEmpty() {
        return topIndex == -1;
    }

    int size() {
        return topIndex + 1;
    }
};

// Alternative: Space-optimized MinStack
// Store (val - min) in stack to save space.
// If stored value is negative, the actual minimum changed.
class MinStackOptimized {
private:
    int data[MAX_SIZE];
    int topIndex;
    int currentMin;

public:
    MinStackOptimized() {
        topIndex = -1;
        currentMin = 0;
    }

    void push(int val) {
        if (topIndex >= MAX_SIZE - 1) {
            cout << "Stack overflow!" << endl;
            return;
        }
        topIndex++;
        if (topIndex == 0) {
            data[topIndex] = val;
            currentMin = val;
        } else {
            if (val >= currentMin) {
                data[topIndex] = val;
            } else {
                // Store val - currentMin (negative) and update min
                data[topIndex] = val - currentMin;
                currentMin = val;
            }
        }
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack underflow!" << endl;
            return -1;
        }
        int val = data[topIndex];
        topIndex--;
        if (val < 0) {
            // This was a new minimum; restore previous min
            int actualMin = currentMin;
            // Previous min = currentMin - stored_negative_value
            // But stored = actual - oldMin, so oldMin = actual - stored
            // stored = val (negative), actual = currentMin
            // oldMin = currentMin - val = currentMin - (newMin - oldMin) = 2*oldMin - newMin
            // Actually: stored = newMin - oldMin (negative)
            // So oldMin = newMin - stored = currentMin - val
            currentMin = currentMin - val;
            return currentMin;  // Return the popped actual value (was currentMin before update)
        }
        return val;
    }

    int top() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        if (data[topIndex] < 0) {
            return currentMin;  // This was a minimum push
        }
        return data[topIndex];
    }

    int getMin() {
        if (isEmpty()) return -1;
        return currentMin;
    }

    bool isEmpty() {
        return topIndex == -1;
    }
};

int main() {
    cout << "=== Min Stack ===" << endl;

    MinStack ms;
    ms.push(-2);
    ms.push(0);
    ms.push(-3);

    cout << "Pushed: -2, 0, -3" << endl;
    cout << "Min: " << ms.getMin() << endl;       // -3
    cout << "Top: " << ms.top() << endl;          // -3
    cout << "Size: " << ms.size() << endl;        // 3

    ms.pop();
    cout << endl << "After pop:" << endl;
    cout << "Min: " << ms.getMin() << endl;       // -2
    cout << "Top: " << ms.top() << endl;          // 0

    ms.pop();
    ms.pop();
    cout << endl << "After popping all:" << endl;
    cout << "Empty? " << (ms.isEmpty() ? "Yes" : "No") << endl;

    // Another example
    cout << endl << "=== Another Example ===" << endl;
    MinStack ms2;
    ms2.push(5);
    ms2.push(3);
    ms2.push(7);
    ms2.push(2);
    ms2.push(8);
    cout << "Pushed: 5, 3, 7, 2, 8" << endl;
    cout << "Min: " << ms2.getMin() << endl;  // 2
    ms2.pop();  // 8
    cout << "After pop 8, Min: " << ms2.getMin() << endl;  // 2
    ms2.pop();  // 2
    cout << "After pop 2, Min: " << ms2.getMin() << endl;  // 3

    cout << endl << "Time: push/pop/top/getMin = O(1)" << endl;
    cout << "Space: O(n) for main stack + O(n) for min stack" << endl;

    return 0;
}
