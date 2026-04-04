/*
 * File: 05_Advanced_Hashing_Summary.cpp
 * Topic: Summary of all advanced hashing concepts
 * Description: Rolling Hash, Bloom Filter, Consistent Hashing recap
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Advanced Hashing - Summary ===" << endl;
    cout << endl;

    cout << "--- Rolling Hash (Rabin-Karp) ---" << endl;
    cout << "Purpose:   String matching using sliding window hash" << endl;
    cout << "Time:      O(n+m) average, O(n*m) worst" << endl;
    cout << "Key idea:  Compute next hash in O(1) from current" << endl;
    cout << "Use:       Pattern search, plagiarism detection" << endl;
    cout << "Double Hash: Use two different mods to avoid collisions" << endl;
    cout << endl;

    cout << "--- Bloom Filter ---" << endl;
    cout << "Purpose:   Probabilistic set membership test" << endl;
    cout << "Space:     Very efficient (bit array)" << endl;
    cout << "Accuracy:  No false negatives, possible false positives" << endl;
    cout << "Use:       Cache filtering, URL tracking, spell check" << endl;
    cout << "Cannot delete (without Counting Bloom Filter)" << endl;
    cout << endl;

    cout << "--- Consistent Hashing ---" << endl;
    cout << "Purpose:   Distribute keys across servers efficiently" << endl;
    cout << "Key idea:  Hash ring with virtual nodes" << endl;
    cout << "Benefit:   Minimal remapping on server add/remove" << endl;
    cout << "Use:       Distributed caches (Memcached, DynamoDB)" << endl;
    cout << endl;

    cout << "--- All Hashing Topics Covered ---" << endl;
    cout << "5.1 Hash Tables:" << endl;
    cout << "  01. Hash Table Basics              - Concepts" << endl;
    cout << "  02. Chaining Hash Table            - Linked list per bucket" << endl;
    cout << "  03. Open Addressing (Linear Probe) - Array with probing" << endl;
    cout << "  04. Chaining vs Open Addressing    - Comparison" << endl;
    cout << "5.2 Hash-Based Structures:" << endl;
    cout << "  01. Hash Set Demo                  - Unique elements" << endl;
    cout << "  02. Hash Map Demo                  - Key-value pairs" << endl;
    cout << "  03. Frequency Counting             - Count occurrences" << endl;
    cout << "  04. Two Sum                        - Find pair with target" << endl;
    cout << "  05. Subarray Sum Divisible by K    - Prefix sum mod K" << endl;
    cout << "  06. Longest Subarray Sum K         - Prefix sum - K" << endl;
    cout << "  07. Longest Equal 0s and 1s        - Convert 0 to -1" << endl;
    cout << "  08. Hash-Based Patterns Summary    - Recap" << endl;
    cout << "5.3 Advanced Hashing:" << endl;
    cout << "  01. Rolling Hash Basics            - Rabin-Karp" << endl;
    cout << "  02. Double Hashing Rabin-Karp      - Two hashes" << endl;
    cout << "  03. Bloom Filter Basics            - Probabilistic set" << endl;
    cout << "  04. Consistent Hashing Basics      - Hash ring" << endl;
    cout << "  05. Advanced Hashing Summary       - This file" << endl;

    return 0;
}
