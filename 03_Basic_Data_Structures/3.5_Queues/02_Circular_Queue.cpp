/*
 * File: 02_Circular_Queue.cpp
 * Topic: Circular Queue - Reuse empty space at front
 * Description: Front and rear wrap around using modulo
 */
#include <iostream>
using namespace std;

class CircularQueue {
    int* data;
    int front;
    int rear;
    int capacity;
    int size;

public:
    CircularQueue(int k) {
        capacity = k;
        front = 0;
        rear = -1;
        size = 0;
        data = new int[capacity];
    }

    ~CircularQueue() {
        delete[] data;
    }

    bool enqueue(int val) {
        if (isFull()) {
            cout << "  Queue is full!" << endl;
            return false;
        }
        rear = (rear + 1) % capacity; // wrap around
        data[rear] = val;
        size++;
        return true;
    }

    bool dequeue() {
        if (isEmpty()) {
            cout << "  Queue is empty!" << endl;
            return false;
        }
        front = (front + 1) % capacity; // wrap around
        size--;
        return true;
    }

    int Front() {
        if (isEmpty()) return -1;
        return data[front];
    }

    int Rear() {
        if (isEmpty()) return -1;
        return data[rear];
    }

    bool isFull() {
        return size == capacity;
    }

    bool isEmpty() {
        return size == 0;
    }

    int getSize() {
        return size;
    }
};

int main() {
    cout << "=== Circular Queue ===" << endl;
    cout << endl;

    CircularQueue cq(3);

    cout << "--- Enqueue 10, 20, 30 ---" << endl;
    cq.enqueue(10);
    cq.enqueue(20);
    cq.enqueue(30);

    cout << endl;
    cout << "Full? " << (cq.isFull() ? "Yes" : "No") << endl;
    cout << "Front: " << cq.Front() << ", Rear: " << cq.Rear() << endl;
    cout << endl;

    cout << "--- Dequeue 10, 20 ---" << endl;
    cq.dequeue();
    cq.dequeue();

    cout << "Front: " << cq.Front() << ", Rear: " << cq.Rear() << endl;
    cout << endl;

    cout << "--- Enqueue 40 (uses freed space) ---" << endl;
    cq.enqueue(40);

    cout << "Front: " << cq.Front() << ", Rear: " << cq.Rear() << endl;
    cout << "Size: " << cq.getSize() << endl;

    cout << endl;
    cout << "--- Why Circular Queue? ---" << endl;
    cout << "In a normal queue with array, dequeued spaces at front are wasted." << endl;
    cout << "Circular queue REUSES those spaces by wrapping around." << endl;
    cout << endl;
    cout << "rear = (rear + 1) % capacity" << endl;
    cout << "front = (front + 1) % capacity" << endl;
    cout << endl;
    cout << "Time: O(1) for all operations" << endl;
    cout << "Space: O(k) for capacity k" << endl;

    return 0;
}
