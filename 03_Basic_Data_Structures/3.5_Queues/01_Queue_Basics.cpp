/*
 * File: 01_Queue_Basics.cpp
 * Topic: Simple Queue - FIFO using array
 * Description: enqueue, dequeue, front, rear
 */
#include <iostream>
using namespace std;

class MyQueue {
    int* arr;
    int front;
    int rear;
    int capacity;
    int size;

public:
    MyQueue(int cap) {
        capacity = cap;
        front = 0;
        rear = -1;
        size = 0;
        arr = new int[capacity];
    }

    ~MyQueue() {
        delete[] arr;
    }

    // Enqueue: add to rear
    void enqueue(int val) {
        if (size == capacity) {
            cout << "  Queue is full! Cannot enqueue " << val << endl;
            return;
        }
        rear++;
        arr[rear] = val;
        size++;
        cout << "  Enqueued " << val << endl;
    }

    // Dequeue: remove from front
    int dequeue() {
        if (size == 0) {
            cout << "  Queue is empty! Cannot dequeue." << endl;
            return -1;
        }
        int val = arr[front];
        front++;
        size--;
        return val;
    }

    int getFront() {
        if (size == 0) return -1;
        return arr[front];
    }

    int getRear() {
        if (size == 0) return -1;
        return arr[rear];
    }

    bool isEmpty() {
        return size == 0;
    }

    int getSize() {
        return size;
    }
};

int main() {
    cout << "=== Queue Basics ===" << endl;
    cout << endl;

    MyQueue q(5);

    // Enqueue
    cout << "--- Enqueue ---" << endl;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    cout << endl;

    // Front and Rear
    cout << "--- Front and Rear ---" << endl;
    cout << "Front: " << q.getFront() << endl;
    cout << "Rear:  " << q.getRear() << endl;
    cout << "Size:  " << q.getSize() << endl;
    cout << endl;

    // Dequeue
    cout << "--- Dequeue ---" << endl;
    cout << "Dequeued: " << q.dequeue() << endl;
    cout << "Dequeued: " << q.dequeue() << endl;
    cout << "New Front: " << q.getFront() << endl;
    cout << endl;

    cout << "--- Queue Properties ---" << endl;
    cout << "FIFO: First In, First Out" << endl;
    cout << "Think of it like a line at a ticket counter." << endl;
    cout << endl;
    cout << "Operations:" << endl;
    cout << "  enqueue(x)  - Add x at rear     O(1)" << endl;
    cout << "  dequeue()   - Remove from front  O(n) with array shift" << endl;
    cout << "  front()     - See front element  O(1)" << endl;
    cout << "  rear()      - See rear element   O(1)" << endl;

    return 0;
}
