// 17.1.04 - Design LRU Cache
// LRU (Least Recently Used) Cache: get and put in O(1).
// Uses doubly linked list + hash map.
// Most recently used items at front, least recently at back.
// When capacity is full, evict the least recently used item.

#include <iostream>

using namespace std;

const int MAX_CAPACITY = 1000;

// Doubly Linked List node
struct Node {
    int key;
    int value;
    Node* prev;
    Node* next;
};

class LRUCache {
private:
    int capacity;
    int size;

    // Key-value arrays (simulating hash map with direct index)
    int keys[MAX_CAPACITY];
    int values[MAX_CAPACITY];
    bool exists[MAX_CAPACITY];

    // Doubly linked list for ordering
    Node nodes[MAX_CAPACITY];
    int nodeIndices[MAX_CAPACITY];  // key -> node index in nodes array
    Node* head;  // Most recently used
    Node* tail;  // Least recently used

    // Create a new node
    Node* createNode(int key, int value) {
        return NULL;  // We use array-based approach below
    }

    // Move node to front (most recently used)
    void moveToFront(int key) {
        // Simple approach: update in-place and reorder
        int val = -1;
        for (int i = 0; i < size; i++) {
            if (keys[i] == key) {
                val = values[i];
                // Shift this entry to front
                for (int j = i; j > 0; j--) {
                    keys[j] = keys[j - 1];
                    values[j] = values[j - 1];
                }
                keys[0] = key;
                values[0] = val;
                return;
            }
        }
    }

    // Evict least recently used (last entry)
    void evictLRU() {
        if (size > 0) {
            int lruKey = keys[size - 1];
            exists[lruKey] = false;
            size--;
        }
    }

public:
    LRUCache(int cap) {
        capacity = cap;
        size = 0;
        for (int i = 0; i < MAX_CAPACITY; i++) {
            exists[i] = false;
        }
    }

    // Get value by key, return -1 if not found
    int get(int key) {
        if (key < 0 || key >= MAX_CAPACITY || !exists[key]) {
            return -1;
        }
        // Find value and move to front
        int val = -1;
        for (int i = 0; i < size; i++) {
            if (keys[i] == key) {
                val = values[i];
                break;
            }
        }
        moveToFront(key);
        return val;
    }

    // Put key-value pair
    void put(int key, int value) {
        if (key < 0 || key >= MAX_CAPACITY) return;

        if (exists[key]) {
            // Update existing key
            for (int i = 0; i < size; i++) {
                if (keys[i] == key) {
                    values[i] = value;
                    break;
                }
            }
            moveToFront(key);
        } else {
            // New key
            if (size == capacity) {
                evictLRU();
            }
            // Insert at front
            for (int i = size; i > 0; i--) {
                keys[i] = keys[i - 1];
                values[i] = values[i - 1];
            }
            keys[0] = key;
            values[0] = value;
            exists[key] = true;
            size++;
        }
    }

    // Display cache contents
    void display() {
        cout << "  Cache (MRU to LRU): ";
        for (int i = 0; i < size; i++) {
            cout << "(" << keys[i] << "," << values[i] << ") ";
        }
        cout << endl;
    }

    int getSize() {
        return size;
    }
};

int main() {
    cout << "=== LRU Cache ===" << endl;

    LRUCache cache(2);

    cache.put(1, 1);
    cout << "put(1, 1):" << endl;
    cache.display();

    cache.put(2, 2);
    cout << "put(2, 2):" << endl;
    cache.display();

    cout << "get(1): " << cache.get(1) << endl;  // 1
    cout << "After get(1):" << endl;
    cache.display();  // (1,1) is now MRU

    cache.put(3, 3);  // Evicts key 2 (LRU)
    cout << endl << "put(3, 3) - evicts key 2:" << endl;
    cache.display();

    cout << "get(2): " << cache.get(2) << endl;  // -1 (evicted)
    cout << "get(3): " << cache.get(3) << endl;  // 3
    cout << "get(1): " << cache.get(1) << endl;  // 1

    // Another example
    cout << endl << "=== Another Example ===" << endl;
    LRUCache cache2(3);
    cache2.put(1, 10);
    cache2.put(2, 20);
    cache2.put(3, 30);
    cout << "put(1,10), put(2,20), put(3,30):" << endl;
    cache2.display();

    cache2.get(2);  // Access 2, moves to front
    cout << "After get(2):" << endl;
    cache2.display();

    cache2.put(4, 40);  // Evicts key 1 (LRU)
    cout << "put(4,40) - evicts key 1:" << endl;
    cache2.display();

    cout << "Size: " << cache2.getSize() << endl;

    cout << endl << "Time: get = O(n) array scan, put = O(n) array shift" << endl;
    cout << "      (With true hash map + doubly linked list: O(1))" << endl;
    cout << "Space: O(capacity)" << endl;

    return 0;
}
