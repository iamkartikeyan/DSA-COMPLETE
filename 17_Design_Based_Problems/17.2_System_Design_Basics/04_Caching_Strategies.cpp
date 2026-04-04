// 17.2.04 - Caching Strategies
// LRU, LFU, FIFO caching strategies with simulation.
// Compare hit rates, eviction behavior, and use cases.

#include <iostream>

using namespace std;

const int MAX_CACHE = 10;

struct CacheEntry {
    int key;
    int value;
    int frequency;     // For LFU
    int lastAccess;    // For LRU
    int insertTime;    // For FIFO
    bool valid;
};

// ---- FIFO Cache ----
// First In, First Out: evict oldest entry
class FIFOCache {
private:
    CacheEntry entries[MAX_CACHE];
    int capacity;
    int size;
    int insertCounter;

public:
    FIFOCache(int cap) {
        capacity = cap;
        size = 0;
        insertCounter = 0;
        for (int i = 0; i < MAX_CACHE; i++) entries[i].valid = false;
    }

    int get(int key) {
        for (int i = 0; i < size; i++) {
            if (entries[i].key == key && entries[i].valid) {
                return entries[i].value;
            }
        }
        return -1;  // Cache miss
    }

    void put(int key, int value) {
        // Check if key already exists
        for (int i = 0; i < size; i++) {
            if (entries[i].key == key && entries[i].valid) {
                entries[i].value = value;
                return;
            }
        }
        // Cache full? Evict oldest
        if (size >= capacity) {
            int oldestIdx = 0;
            int oldestTime = entries[0].insertTime;
            for (int i = 1; i < size; i++) {
                if (entries[i].insertTime < oldestTime) {
                    oldestTime = entries[i].insertTime;
                    oldestIdx = i;
                }
            }
            entries[oldestIdx].valid = false;
        } else {
            size++;
        }
        // Find empty slot
        for (int i = 0; i < MAX_CACHE; i++) {
            if (!entries[i].valid) {
                entries[i].key = key;
                entries[i].value = value;
                entries[i].valid = true;
                entries[i].insertTime = insertCounter++;
                return;
            }
        }
    }

    void display() {
        cout << "  FIFO Cache: ";
        for (int i = 0; i < size; i++) {
            if (entries[i].valid) {
                cout << "(" << entries[i].key << "," << entries[i].value << ") ";
            }
        }
        cout << endl;
    }
};

// ---- LRU Cache ----
// Least Recently Used: evict least recently accessed entry
class LRUCache {
private:
    CacheEntry entries[MAX_CACHE];
    int capacity;
    int size;
    int accessCounter;

public:
    LRUCache(int cap) {
        capacity = cap;
        size = 0;
        accessCounter = 0;
        for (int i = 0; i < MAX_CACHE; i++) entries[i].valid = false;
    }

    int get(int key) {
        for (int i = 0; i < size; i++) {
            if (entries[i].key == key && entries[i].valid) {
                entries[i].lastAccess = ++accessCounter;
                return entries[i].value;
            }
        }
        return -1;
    }

    void put(int key, int value) {
        // Check if key exists
        for (int i = 0; i < size; i++) {
            if (entries[i].key == key && entries[i].valid) {
                entries[i].value = value;
                entries[i].lastAccess = ++accessCounter;
                return;
            }
        }
        // Cache full? Evict LRU
        if (size >= capacity) {
            int lruIdx = 0;
            int lruTime = entries[0].lastAccess;
            for (int i = 1; i < size; i++) {
                if (entries[i].lastAccess < lruTime) {
                    lruTime = entries[i].lastAccess;
                    lruIdx = i;
                }
            }
            entries[lruIdx].valid = false;
        } else {
            size++;
        }
        // Find empty slot
        for (int i = 0; i < MAX_CACHE; i++) {
            if (!entries[i].valid) {
                entries[i].key = key;
                entries[i].value = value;
                entries[i].valid = true;
                entries[i].lastAccess = ++accessCounter;
                entries[i].frequency = 1;
                return;
            }
        }
    }

    void display() {
        cout << "  LRU Cache: ";
        for (int i = 0; i < size; i++) {
            if (entries[i].valid) {
                cout << "(" << entries[i].key << "," << entries[i].value << ") ";
            }
        }
        cout << endl;
    }
};

// ---- LFU Cache ----
// Least Frequently Used: evict least frequently accessed entry
class LFUCache {
private:
    CacheEntry entries[MAX_CACHE];
    int capacity;
    int size;
    int accessCounter;

public:
    LFUCache(int cap) {
        capacity = cap;
        size = 0;
        accessCounter = 0;
        for (int i = 0; i < MAX_CACHE; i++) entries[i].valid = false;
    }

    int get(int key) {
        for (int i = 0; i < size; i++) {
            if (entries[i].key == key && entries[i].valid) {
                entries[i].frequency++;
                entries[i].lastAccess = ++accessCounter;
                return entries[i].value;
            }
        }
        return -1;
    }

    void put(int key, int value) {
        // Check if key exists
        for (int i = 0; i < size; i++) {
            if (entries[i].key == key && entries[i].valid) {
                entries[i].value = value;
                entries[i].frequency++;
                entries[i].lastAccess = ++accessCounter;
                return;
            }
        }
        // Cache full? Evict LFU
        if (size >= capacity) {
            int lfuIdx = 0;
            int lfuFreq = entries[0].frequency;
            for (int i = 1; i < size; i++) {
                if (entries[i].frequency < lfuFreq) {
                    lfuFreq = entries[i].frequency;
                    lfuIdx = i;
                }
            }
            entries[lfuIdx].valid = false;
        } else {
            size++;
        }
        // Find empty slot
        for (int i = 0; i < MAX_CACHE; i++) {
            if (!entries[i].valid) {
                entries[i].key = key;
                entries[i].value = value;
                entries[i].valid = true;
                entries[i].frequency = 1;
                entries[i].lastAccess = ++accessCounter;
                return;
            }
        }
    }

    void display() {
        cout << "  LFU Cache: ";
        for (int i = 0; i < size; i++) {
            if (entries[i].valid) {
                cout << "(" << entries[i].key << "," << entries[i].value
                     << ",freq=" << entries[i].frequency << ") ";
            }
        }
        cout << endl;
    }
};

// Simulate cache performance with a workload
void compareCaches(int requests[], int n) {
    cout << endl << "=== Cache Performance Comparison ===" << endl;
    cout << "Workload: ";
    for (int i = 0; i < n; i++) cout << requests[i] << " ";
    cout << endl;

    int cacheSize = 3;
    FIFOCache fifo(cacheSize);
    LRUCache lru(cacheSize);
    LFUCache lfu(cacheSize);

    int fifoHits = 0, lruHits = 0, lfuHits = 0;

    for (int i = 0; i < n; i++) {
        int key = requests[i];

        // FIFO
        if (fifo.get(key) != -1) fifoHits++;
        else fifo.put(key, key * 10);

        // LRU
        if (lru.get(key) != -1) lruHits++;
        else lru.put(key, key * 10);

        // LFU
        if (lfu.get(key) != -1) lfuHits++;
        else lfu.put(key, key * 10);
    }

    cout << endl << "Cache size: " << cacheSize << ", Requests: " << n << endl;
    cout << "FIFO hits: " << fifoHits << " / " << n
         << " (" << (fifoHits * 100 / n) << "%)" << endl;
    cout << "LRU hits:  " << lruHits << " / " << n
         << " (" << (lruHits * 100 / n) << "%)" << endl;
    cout << "LFU hits:  " << lfuHits << " / " << n
         << " (" << (lfuHits * 100 / n) << "%)" << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "  CACHING STRATEGIES" << endl;
    cout << "========================================" << endl;

    // Individual demos
    cout << endl << "=== FIFO Cache ===" << endl;
    FIFOCache fifo(3);
    fifo.put(1, 10);
    fifo.put(2, 20);
    fifo.put(3, 30);
    fifo.display();
    cout << "  get(1): " << fifo.get(1) << endl;  // 10
    fifo.put(4, 40);  // Evicts 2 (oldest)
    cout << "  After put(4,40):" << endl;
    fifo.display();
    cout << "  get(2): " << fifo.get(2) << " (evicted)" << endl;  // -1

    cout << endl << "=== LRU Cache ===" << endl;
    LRUCache lru(3);
    lru.put(1, 10);
    lru.put(2, 20);
    lru.put(3, 30);
    lru.display();
    lru.get(1);  // Access 1, moves it to MRU
    lru.put(4, 40);  // Evicts 2 (LRU)
    cout << "  After get(1), put(4,40):" << endl;
    lru.display();

    cout << endl << "=== LFU Cache ===" << endl;
    LFUCache lfu(3);
    lfu.put(1, 10);
    lfu.put(2, 20);
    lfu.put(3, 30);
    lfu.get(1);  // freq of 1 increases
    lfu.get(1);
    lfu.get(2);
    lfu.put(4, 40);  // Evicts 3 (freq=1, same as 2 but 3 was inserted later)
    cout << "  After accesses, put(4,40):" << endl;
    lfu.display();

    // Compare with workload
    int workload1[] = {1, 2, 3, 1, 4, 1, 2, 5, 1, 2};
    compareCaches(workload1, 10);

    int workload2[] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    compareCaches(workload2, 10);

    cout << endl << "========================================" << endl;
    cout << "  WHEN TO USE WHICH" << endl;
    cout << "========================================" << endl;
    cout << "  FIFO: Simple workloads, streaming data" << endl;
    cout << "  LRU: Temporal locality (recently used = likely reused)" << endl;
    cout << "  LFU: Popularity-based access patterns" << endl;

    return 0;
}
