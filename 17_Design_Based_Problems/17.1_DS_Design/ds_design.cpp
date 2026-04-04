#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <string>
#include <random>
using namespace std;

// ===== LRU CACHE (Least Recently Used) =====
class LRUCache {
    int capacity;
    list<pair<int,int>> dll;  // key-value pairs, front=MRU
    unordered_map<int, list<pair<int,int>>::iterator> mp;
public:
    LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        if (mp.find(key) == mp.end()) return -1;
        dll.splice(dll.begin(), dll, mp[key]);  // Move to front
        return mp[key]->second;
    }

    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            dll.erase(mp[key]);  // Remove old
        } else if (mp.size() == capacity) {
            mp.erase(dll.back().first);  // Evict LRU
            dll.pop_back();
        }
        dll.push_front({key, value});
        mp[key] = dll.begin();
    }
};

// ===== LFU CACHE (Least Frequently Used) =====
class LFUCache {
    int capacity, minFreq;
    unordered_map<int, pair<int,int>> keyValFreq;  // key -> {val, freq}
    unordered_map<int, list<int>> freqKeys;        // freq -> list of keys
    unordered_map<int, list<int>::iterator> keyPos; // key -> position in list

    void updateFreq(int key) {
        int freq = keyValFreq[key].second;
        freqKeys[freq].erase(keyPos[key]);
        if (freqKeys[freq].empty() && minFreq == freq) minFreq++;
        freqKeys[freq + 1].push_front(key);
        keyPos[key] = freqKeys[freq + 1].begin();
        keyValFreq[key].second++;
    }
public:
    LFUCache(int cap) : capacity(cap), minFreq(0) {}

    int get(int key) {
        if (keyValFreq.find(key) == keyValFreq.end()) return -1;
        updateFreq(key);
        return keyValFreq[key].first;
    }

    void put(int key, int value) {
        if (capacity == 0) return;
        if (keyValFreq.find(key) != keyValFreq.end()) {
            keyValFreq[key].first = value;
            updateFreq(key);
        } else {
            if (keyValFreq.size() == capacity) {
                int evict = freqKeys[minFreq].back();
                freqKeys[minFreq].pop_back();
                keyValFreq.erase(evict);
                keyPos.erase(evict);
            }
            keyValFreq[key] = {value, 1};
            freqKeys[1].push_front(key);
            keyPos[key] = freqKeys[1].begin();
            minFreq = 1;
        }
    }
};

// ===== MIN STACK =====
class MinStack {
    vector<pair<int,int>> st;  // {value, currentMin}
public:
    void push(int val) {
        int minVal = st.empty() ? val : min(val, st.back().second);
        st.push_back({val, minVal});
    }
    void pop() { st.pop_back(); }
    int top() { return st.back().first; }
    int getMin() { return st.back().second; }
};

// ===== INSERT DELETE GETRANDOM O(1) =====
class RandomizedSet {
    vector<int> arr;
    unordered_map<int, int> valToIdx;
public:
    bool insert(int val) {
        if (valToIdx.count(val)) return false;
        valToIdx[val] = arr.size();
        arr.push_back(val);
        return true;
    }
    bool remove(int val) {
        if (!valToIdx.count(val)) return false;
        int last = arr.back();
        arr[valToIdx[val]] = last;
        valToIdx[last] = valToIdx[val];
        arr.pop_back();
        valToIdx.erase(val);
        return true;
    }
    int getRandom() {
        return arr[rand() % arr.size()];
    }
};

// ===== LOGGER RATE LIMITER =====
class Logger {
    unordered_map<string, int> msgTimestamp;
public:
    bool shouldPrintMessage(int timestamp, string msg) {
        if (msgTimestamp.count(msg) && timestamp - msgTimestamp[msg] < 10)
            return false;
        msgTimestamp[msg] = timestamp;
        return true;
    }
};

int main() {
    // LRU Cache
    cout << "=== LRU Cache ===\n";
    LRUCache lru(2);
    lru.put(1, 1); lru.put(2, 2);
    cout << "get(1): " << lru.get(1) << "\n";  // 1
    lru.put(3, 3);  // Evicts key 2
    cout << "get(2): " << lru.get(2) << "\n";  // -1

    // LFU Cache
    cout << "\n=== LFU Cache ===\n";
    LFUCache lfu(2);
    lfu.put(1, 1); lfu.put(2, 2);
    cout << "get(1): " << lfu.get(1) << "\n";  // 1
    lfu.put(3, 3);  // Evicts key 2 (least freq)
    cout << "get(2): " << lfu.get(2) << "\n";  // -1

    // Min Stack
    cout << "\n=== Min Stack ===\n";
    MinStack ms;
    ms.push(-2); ms.push(0); ms.push(-3);
    cout << "Min: " << ms.getMin() << "\n";  // -3
    ms.pop();
    cout << "Min after pop: " << ms.getMin() << "\n";  // -2

    // RandomizedSet
    cout << "\n=== RandomizedSet ===\n";
    RandomizedSet rs;
    cout << "insert(1): " << rs.insert(1) << "\n";
    cout << "insert(1): " << rs.insert(1) << "\n";  // false
    cout << "getRandom: " << rs.getRandom() << "\n";

    // Logger
    cout << "\n=== Logger Rate Limiter ===\n";
    Logger logger;
    cout << "print(msg1, t=1): " << logger.shouldPrintMessage(1, "msg1") << "\n";
    cout << "print(msg1, t=5): " << logger.shouldPrintMessage(5, "msg1") << "\n";  // false

    return 0;
}
