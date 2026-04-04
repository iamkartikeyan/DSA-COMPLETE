// 17.1.05 - Data Structure Design Summary
// Complete summary: Stack, Queue, Min Stack, LRU Cache.

#include <iostream>

using namespace std;

const int MAX_SIZE = 1000;

// ---- Stack ----
class Stack {
private:
    int data[MAX_SIZE];
    int topIdx;
public:
    Stack() { topIdx = -1; }
    void push(int val) { if (topIdx < MAX_SIZE - 1) data[++topIdx] = val; }
    int pop() { return (topIdx >= 0) ? data[topIdx--] : -1; }
    int peek() { return (topIdx >= 0) ? data[topIdx] : -1; }
    bool isEmpty() { return topIdx == -1; }
    int size() { return topIdx + 1; }
};

// ---- Queue ----
class Queue {
private:
    int data[MAX_SIZE];
    int frontIdx;
    int rearIdx;
    int count;
public:
    Queue() { frontIdx = 0; rearIdx = -1; count = 0; }
    void enqueue(int val) {
        if (count < MAX_SIZE) {
            rearIdx = (rearIdx + 1) % MAX_SIZE;
            data[rearIdx] = val;
            count++;
        }
    }
    int dequeue() {
        if (count > 0) {
            int val = data[frontIdx];
            frontIdx = (frontIdx + 1) % MAX_SIZE;
            count--;
            return val;
        }
        return -1;
    }
    int getFront() { return (count > 0) ? data[frontIdx] : -1; }
    bool isEmpty() { return count == 0; }
    int getSize() { return count; }
};

// ---- Min Stack ----
class MinStack {
private:
    int data[MAX_SIZE];
    int minData[MAX_SIZE];
    int topIdx;
public:
    MinStack() { topIdx = -1; }
    void push(int val) {
        if (topIdx >= MAX_SIZE - 1) return;
        topIdx++;
        data[topIdx] = val;
        if (topIdx == 0) minData[topIdx] = val;
        else minData[topIdx] = (val < minData[topIdx - 1]) ? val : minData[topIdx - 1];
    }
    int pop() { return (topIdx >= 0) ? data[topIdx--] : -1; }
    int top() { return (topIdx >= 0) ? data[topIdx] : -1; }
    int getMin() { return (topIdx >= 0) ? minData[topIdx] : -1; }
};

// ---- LRU Cache (simplified array-based) ----
class LRUCache {
private:
    int capacity;
    int size;
    int keys[MAX_CAPACITY];
    int values[MAX_CAPACITY];
    bool exists[MAX_CAPACITY];
    static const int MAX_CAPACITY = 100;

    void moveToFront(int key) {
        int val = -1, pos = -1;
        for (int i = 0; i < size; i++) {
            if (keys[i] == key) { val = values[i]; pos = i; break; }
        }
        if (pos > 0) {
            for (int j = pos; j > 0; j--) { keys[j] = keys[j - 1]; values[j] = values[j - 1]; }
            keys[0] = key;
            values[0] = val;
        }
    }

public:
    LRUCache(int cap) {
        capacity = cap;
        size = 0;
        for (int i = 0; i < MAX_CAPACITY; i++) exists[i] = false;
    }

    int get(int key) {
        if (key < 0 || key >= MAX_CAPACITY || !exists[key]) return -1;
        moveToFront(key);
        for (int i = 0; i < size; i++) { if (keys[i] == key) return values[i]; }
        return -1;
    }

    void put(int key, int value) {
        if (key < 0 || key >= MAX_CAPACITY) return;
        if (exists[key]) {
            for (int i = 0; i < size; i++) { if (keys[i] == key) { values[i] = value; break; } }
            moveToFront(key);
        } else {
            if (size == capacity) { exists[keys[size - 1]] = false; size--; }
            for (int i = size; i > 0; i--) { keys[i] = keys[i - 1]; values[i] = values[i - 1]; }
            keys[0] = key;
            values[0] = value;
            exists[key] = true;
            size++;
        }
    }
};

int main() {
    cout << "========================================" << endl;
    cout << "  DS DESIGN - COMPLETE SUMMARY" << endl;
    cout << "========================================" << endl;

    // 1. Stack
    cout << endl << "1. STACK (LIFO)" << endl;
    Stack st;
    st.push(10);
    st.push(20);
    st.push(30);
    cout << "   Push 10, 20, 30. Top: " << st.peek() << ", Size: " << st.size() << endl;
    cout << "   Pop: " << st.pop() << ", Min remaining: " << st.peek() << endl;

    // 2. Queue
    cout << endl << "2. QUEUE (FIFO)" << endl;
    Queue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    cout << "   Enqueue 10, 20, 30. Front: " << q.getFront() << ", Size: " << q.getSize() << endl;
    cout << "   Dequeue: " << q.dequeue() << ", New front: " << q.getFront() << endl;

    // 3. Min Stack
    cout << endl << "3. MIN STACK (O(1) getMin)" << endl;
    MinStack ms;
    ms.push(5);
    ms.push(3);
    ms.push(7);
    ms.push(2);
    cout << "   Push 5, 3, 7, 2" << endl;
    cout << "   Min: " << ms.getMin() << endl;  // 2
    ms.pop();
    cout << "   After pop, Min: " << ms.getMin() << endl;  // 3

    // 4. LRU Cache
    cout << endl << "4. LRU CACHE (get/put)" << endl;
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout << "   put(1,1), put(2,2)" << endl;
    cout << "   get(1): " << cache.get(1) << endl;  // 1
    cache.put(3, 3);  // Evicts key 2
    cout << "   put(3,3) evicts key 2" << endl;
    cout << "   get(2): " << cache.get(2) << endl;  // -1

    // Complexity summary
    cout << endl << "========================================" << endl;
    cout << "  COMPLEXITY SUMMARY" << endl;
    cout << "========================================" << endl;
    cout << "  Stack:        push/pop/peek = O(1) time, O(n) space" << endl;
    cout << "  Queue:        enqueue/dequeue = O(1) time, O(n) space" << endl;
    cout << "  Min Stack:    push/pop/top/getMin = O(1) time, O(n) space" << endl;
    cout << "  LRU Cache:    get/put = O(capacity) array, O(1) with hash map + DLL" << endl;
    cout << endl;
    cout << "  Key Design Patterns:" << endl;
    cout << "  - Auxiliary data structures (min stack uses extra stack)" << endl;
    cout << "  - Circular buffer (queue avoids shifting)" << endl;
    cout << "  - Doubly linked list + hash map (LRU cache O(1))" << endl;

    return 0;
}
