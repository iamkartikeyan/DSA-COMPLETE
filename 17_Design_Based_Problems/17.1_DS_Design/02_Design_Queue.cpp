// 17.1.02 - Design Queue
// Queue: FIFO (First In, First Out) data structure.
// Operations: enqueue, dequeue, front, rear, isEmpty, size.
// Time: all O(1). Space: O(n).

#include <iostream>

using namespace std;

const int MAX_SIZE = 1000;

class Queue {
private:
    int data[MAX_SIZE];
    int frontIndex;
    int rearIndex;
    int count;

public:
    Queue() {
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    // Add element to rear of queue
    void enqueue(int val) {
        if (count >= MAX_SIZE) {
            cout << "Queue overflow!" << endl;
            return;
        }
        rearIndex = (rearIndex + 1) % MAX_SIZE;
        data[rearIndex] = val;
        count++;
    }

    // Remove element from front of queue
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue underflow!" << endl;
            return -1;
        }
        int val = data[frontIndex];
        frontIndex = (frontIndex + 1) % MAX_SIZE;
        count--;
        return val;
    }

    // Get front element without removing
    int getFront() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return data[frontIndex];
    }

    // Get rear element without removing
    int getRear() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return data[rearIndex];
    }

    // Check if queue is empty
    bool isEmpty() {
        return count == 0;
    }

    // Get number of elements
    int size() {
        return count;
    }

    // Display queue contents
    void display() {
        if (isEmpty()) {
            cout << "  Queue is empty" << endl;
            return;
        }
        cout << "  Queue (front to rear): ";
        int idx = frontIndex;
        for (int i = 0; i < count; i++) {
            cout << data[idx] << " ";
            idx = (idx + 1) % MAX_SIZE;
        }
        cout << endl;
    }
};

int main() {
    cout << "=== Queue Implementation ===" << endl;

    Queue q;
    cout << "Empty? " << (q.isEmpty() ? "Yes" : "No") << endl;

    // Enqueue
    cout << endl << "Enqueue 10, 20, 30, 40:" << endl;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.display();

    // Front and Rear
    cout << "Front: " << q.getFront() << endl;  // 10
    cout << "Rear: " << q.getRear() << endl;    // 40
    cout << "Size: " << q.size() << endl;       // 4

    // Dequeue
    cout << endl << "Dequeue: " << q.dequeue() << endl;  // 10
    cout << "Dequeue: " << q.dequeue() << endl;  // 20
    q.display();

    // Enqueue more
    q.enqueue(50);
    q.enqueue(60);
    cout << endl << "After enqueue 50, 60:" << endl;
    q.display();

    cout << "Front: " << q.getFront() << endl;  // 30
    cout << "Rear: " << q.getRear() << endl;    // 60
    cout << "Size: " << q.size() << endl;       // 4

    cout << endl << "Time: enqueue/dequeue/front/rear/isEmpty/size = O(1)" << endl;
    cout << "Space: O(n) for array storage (circular buffer)" << endl;

    return 0;
}
