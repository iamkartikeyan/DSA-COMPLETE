/*
 * File: 02_Chaining_Hash_Table.cpp
 * Topic: Hash Table with Chaining (Linked List per bucket)
 * Description: Insert, Get, Remove, Rehash with chaining
 */
#include <iostream>
using namespace std;

// Simple hash table with chaining
// Using string keys and int values

struct Node {
    string key;
    int value;
    Node* next;

    Node(string k, int v) {
        key = k;
        value = v;
        next = NULL;
    }
};

class HashTableChaining {
    Node** buckets; // array of linked list heads
    int capacity;
    int size;

    // Hash function: sum of char codes % capacity
    int hashFunc(string key) {
        int sum = 0;
        for (int i = 0; i < key.length(); i++) {
            sum = sum + key[i];
        }
        return sum % capacity;
    }

    // Double the table size and re-insert all
    void rehash() {
        int oldCap = capacity;
        Node** oldBuckets = buckets;

        capacity = capacity * 2;
        buckets = new Node*[capacity];
        for (int i = 0; i < capacity; i++) {
            buckets[i] = NULL;
        }
        size = 0;

        // Re-insert all old entries
        for (int i = 0; i < oldCap; i++) {
            Node* curr = oldBuckets[i];
            while (curr != NULL) {
                insert(curr->key, curr->value);
                Node* next = curr->next;
                delete curr;
                curr = next;
            }
        }
        delete[] oldBuckets;
    }

public:
    HashTableChaining(int cap) {
        capacity = cap;
        size = 0;
        buckets = new Node*[capacity];
        for (int i = 0; i < capacity; i++) {
            buckets[i] = NULL;
        }
    }

    // Insert or update
    void insert(string key, int value) {
        // Rehash if load factor too high
        if ((float)(size + 1) / capacity > 0.75) {
            rehash();
        }

        int idx = hashFunc(key);

        // Check if key already exists
        Node* curr = buckets[idx];
        while (curr != NULL) {
            if (curr->key == key) {
                curr->value = value; // update
                return;
            }
            curr = curr->next;
        }

        // Insert new node at head of chain
        Node* newNode = new Node(key, value);
        newNode->next = buckets[idx];
        buckets[idx] = newNode;
        size = size + 1;
    }

    // Get value for a key (returns -1 if not found)
    int get(string key) {
        int idx = hashFunc(key);
        Node* curr = buckets[idx];
        while (curr != NULL) {
            if (curr->key == key) {
                return curr->value;
            }
            curr = curr->next;
        }
        return -1; // not found
    }

    // Remove a key
    bool remove(string key) {
        int idx = hashFunc(key);
        Node* prev = NULL;
        Node* curr = buckets[idx];

        while (curr != NULL) {
            if (curr->key == key) {
                if (prev == NULL) {
                    buckets[idx] = curr->next;
                } else {
                    prev->next = curr->next;
                }
                delete curr;
                size = size - 1;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false; // not found
    }

    // Print all buckets
    void print() {
        for (int i = 0; i < capacity; i++) {
            cout << "  Bucket " << i << ": ";
            Node* curr = buckets[i];
            if (curr == NULL) {
                cout << "empty";
            } else {
                while (curr != NULL) {
                    cout << "{" << curr->key << ":" << curr->value << "}";
                    if (curr->next != NULL) cout << " -> ";
                    curr = curr->next;
                }
            }
            cout << endl;
        }
    }

    int getSize() {
        return size;
    }

    float loadFactor() {
        return (float)size / capacity;
    }
};

int main() {
    cout << "=== Hash Table - Chaining ===" << endl;
    cout << endl;

    HashTableChaining ht(5);

    // Insert entries
    ht.insert("apple", 10);
    ht.insert("banana", 20);
    ht.insert("grape", 30);
    ht.insert("date", 40);

    cout << "After inserts:" << endl;
    cout << "Load factor: " << ht.loadFactor() << endl;
    ht.print();

    cout << endl;

    // Update existing key
    cout << "--- Update 'apple' from 10 to 100 ---" << endl;
    ht.insert("apple", 100);

    // Get values
    cout << "get('apple')  = " << ht.get("apple") << endl;
    cout << "get('banana') = " << ht.get("banana") << endl;
    cout << "get('mango')  = " << ht.get("mango") << " (not found)" << endl;

    cout << endl;

    // Remove
    cout << "--- Remove 'grape' ---" << endl;
    ht.remove("grape");
    cout << "Size after remove: " << ht.getSize() << endl;
    ht.print();

    cout << endl;
    cout << "--- How Chaining Works ---" << endl;
    cout << "1. Hash the key to find bucket index" << endl;
    cout << "2. Each bucket is a linked list" << endl;
    cout << "3. On collision, add to the linked list" << endl;
    cout << "4. On search, traverse the linked list" << endl;
    cout << "5. If load factor > 0.75 -> rehash (double capacity)" << endl;

    return 0;
}
