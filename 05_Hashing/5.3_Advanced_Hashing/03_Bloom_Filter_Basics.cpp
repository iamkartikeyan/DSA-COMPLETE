/*
 * File: 03_Bloom_Filter_Basics.cpp
 * Topic: What is Bloom Filter, add and mightContain
 * Description: Probabilistic data structure for set membership
 */
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class BloomFilter {
    vector<bool> bits;
    int size;
    int numHashes;

    // Simple hash function with seed
    unsigned int hashFunc(string item, int seed) {
        unsigned int h = seed;
        for (int i = 0; i < item.length(); i++) {
            h = h * 31 + item[i];
        }
        return h % size;
    }

public:
    BloomFilter(int expectedItems, double falsePositiveRate) {
        // Optimal size: m = -n * ln(p) / (ln(2))^2
        size = max(64, (int)(-(expectedItems * log(falsePositiveRate)) / (log(2) * log(2))));

        // Optimal number of hash functions: k = (m/n) * ln(2)
        numHashes = max(2, (int)(ceil((double)size / expectedItems * log(2))));

        bits.assign(size, false);

        cout << "  Bloom filter: " << size << " bits, " << numHashes << " hash functions" << endl;
    }

    void add(string item) {
        for (int i = 0; i < numHashes; i++) {
            unsigned int idx = hashFunc(item, i * 31 + 7);
            bits[idx] = true;
        }
    }

    bool mightContain(string item) {
        for (int i = 0; i < numHashes; i++) {
            unsigned int idx = hashFunc(item, i * 31 + 7);
            if (bits[idx] == false) {
                return false; // definitely NOT in set
            }
        }
        return true; // MIGHT be in set (could be false positive)
    }
};

int main() {
    cout << "=== Bloom Filter ===" << endl;
    cout << endl;

    cout << "--- What is a Bloom Filter? ---" << endl;
    cout << "A space-efficient probabilistic data structure." << endl;
    cout << "Answers: Is element X in the set?" << endl;
    cout << endl;
    cout << "Two possible answers:" << endl;
    cout << "  'DEFINITELY NOT' -> 100% correct (no false negatives)" << endl;
    cout << "  'MIGHT CONTAIN'  -> could be false positive" << endl;
    cout << endl;

    // Create bloom filter for ~5 items with 1% false positive rate
    BloomFilter bf(5, 0.01);

    cout << endl;
    cout << "--- Adding items ---" << endl;
    bf.add("apple");
    bf.add("banana");
    bf.add("cherry");
    bf.add("date");
    bf.add("elderberry");

    cout << "Added: apple, banana, cherry, date, elderberry" << endl;
    cout << endl;

    // Test membership
    cout << "--- Testing Membership ---" << endl;

    string tests[] = {"apple", "banana", "grape", "xyz", "cherry"};
    int numTests = 5;

    for (int i = 0; i < numTests; i++) {
        bool result = bf.mightContain(tests[i]);
        if (result) {
            cout << "  \"" << tests[i] << "\": MIGHT contain" << endl;
        } else {
            cout << "  \"" << tests[i] << "\": DEFINITELY NOT contain" << endl;
        }
    }

    cout << endl;
    cout << "--- Properties ---" << endl;
    cout << "NEVER returns false negative" << endl;
    cout << "MAY return false positive" << endl;
    cout << "More items added -> more false positives" << endl;
    cout << "Cannot delete items (without Counting Bloom Filter)" << endl;
    cout << endl;
    cout << "--- Use Cases ---" << endl;
    cout << "Cache filtering (avoid DB lookup for non-existent keys)" << endl;
    cout << "Web crawlers (visited URL tracking)" << endl;
    cout << "Spell checkers" << endl;
    cout << "Database query optimization (skip non-existent partitions)" << endl;

    return 0;
}
