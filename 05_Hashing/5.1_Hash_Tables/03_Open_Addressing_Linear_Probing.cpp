/*
 * File: 03_Open_Addressing_Linear_Probing.cpp
 * Topic: Hash Table with Open Addressing (Linear Probing)
 * Description: All entries in array, find next empty slot on collision
 */
#include <iostream>
using namespace std;

struct Entry {
    string key;
    int value;
    bool occupied;  // slot was used at some point
    bool deleted;   // slot was deleted (tombstone)

    Entry() {
        occupied = false;
        deleted = false;
    }
};

class HashTableProbing {
    Entry* table;
    int capacity;
    int size;

    int hashFunc(string key) {
        int sum = 0;
        for (int i = 0; i < key.length(); i++) {
            sum = sum + key[i];
        }
        return sum % capacity;
    }

public:
    HashTableProbing(int cap) {
        capacity = cap;
        size = 0;
        table = new Entry[capacity];
    }

    void insert(string key, int value) {
        // Rehash at 50% load (lower threshold for open addressing)
        if ((float)(size + 1) / capacity > 0.5) {
            rehash();
        }

        int idx = hashFunc(key);

        // Linear probing: find next available slot
        for (int i = 0; i < capacity; i++) {
            int curr = (idx + i) % capacity;

            if (table[curr].occupied == false || table[curr].deleted == true) {
                // Found empty or deleted slot
                table[curr].key = key;
                table[curr].value = value;
                table[curr].occupied = true;
                table[curr].deleted = false;
                size = size + 1;
                return;
            }

            // Key already exists -> update
            if (table[curr].key == key) {
                table[curr].value = value;
                return;
            }
        }
    }

    int get(string key) {
        int idx = hashFunc(key);

        for (int i = 0; i < capacity; i++) {
            int curr = (idx + i) % capacity;

            // Empty slot (never occupied) -> key not found
            if (table[curr].occupied == false) {
                return -1;
            }

            // Found the key (occupied and not deleted)
            if (table[curr].occupied == true && table[curr].deleted == false && table[curr].key == key) {
                return table[curr].value;
            }
        }
        return -1; // not found
    }

    bool remove(string key) {
        int idx = hashFunc(key);

        for (int i = 0; i < capacity; i++) {
            int curr = (idx + i) % capacity;

            if (table[curr].occupied == false) {
                return false; // not found
            }

            if (table[curr].occupied == true && table[curr].deleted == false && table[curr].key == key) {
                // Mark as deleted (tombstone) - don't clear, it breaks probing chain
                table[curr].deleted = true;
                size = size - 1;
                return true;
            }
        }
        return false;
    }

    void rehash() {
        int oldCap = capacity;
        Entry* oldTable = table;

        capacity = capacity * 2;
        table = new Entry[capacity];
        size = 0;

        for (int i = 0; i < oldCap; i++) {
            if (oldTable[i].occupied == true && oldTable[i].deleted == false) {
                insert(oldTable[i].key, oldTable[i].value);
            }
        }
        delete[] oldTable;
    }

    void print() {
        for (int i = 0; i < capacity; i++) {
            if (table[i].occupied == true && table[i].deleted == false) {
                cout << "  [" << i << "] {" << table[i].key << ":" << table[i].value << "}" << endl;
            } else if (table[i].deleted == true) {
                cout << "  [" << i << "] <DELETED>" << endl;
            } else {
                cout << "  [" << i << "] empty" << endl;
            }
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
    cout << "=== Hash Table - Open Addressing (Linear Probing) ===" << endl;
    cout << endl;

    HashTableProbing ht(5);

    // Insert entries
    ht.insert("cat", 1);
    ht.insert("dog", 2);
    ht.insert("bat", 3); // may collide with cat
    ht.insert("rat", 4);

    cout << "After inserts:" << endl;
    cout << "Load factor: " << ht.loadFactor() << endl;
    ht.print();

    cout << endl;

    // Get values
    cout << "get('cat') = " << ht.get("cat") << endl;
    cout << "get('dog') = " << ht.get("dog") << endl;
    cout << "get('fox') = " << ht.get("fox") << " (not found)" << endl;

    cout << endl;

    // Remove (uses tombstone)
    cout << "--- Remove 'dog' ---" << endl;
    ht.remove("dog");
    cout << "Size: " << ht.getSize() << endl;
    ht.print();

    cout << "Note: 'dog' slot marked as <DELETED> (tombstone)" << endl;
    cout << "This is needed so probing chains don't break." << endl;

    cout << endl;
    cout << "--- Linear Probing ---" << endl;
    cout << "1. Hash key to find starting index" << endl;
    cout << "2. If slot occupied, try next slot (index+1, index+2, ...)" << endl;
    cout << "3. Wrap around to 0 if you reach end" << endl;
    cout << "4. On delete, mark as tombstone (don't clear)" << endl;
    cout << endl;
    cout << "Load factor threshold: 0.5 (lower than chaining)" << endl;
    cout << "Why? Probing creates clusters at high load" << endl;

    return 0;
}
