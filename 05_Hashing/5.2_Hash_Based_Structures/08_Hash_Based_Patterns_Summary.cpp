/*
 * File: 08_Hash_Based_Patterns_Summary.cpp
 * Topic: Common hash-based patterns and summary
 * Description: Recap of all patterns with when to use
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Hash-Based Patterns Summary ===" << endl;
    cout << endl;

    cout << "--- Common Patterns ---" << endl;
    cout << endl;

    cout << "1. Frequency Counting" << endl;
    cout << "   Pattern: for (x : arr) freq[x]++" << endl;
    cout << "   Use: Duplicates, mode, top K frequent" << endl;
    cout << endl;

    cout << "2. Two Sum Pattern" << endl;
    cout << "   Pattern: Check if (target - x) exists, then store x" << endl;
    cout << "   Use: Pair sum, triplet sum (extended)" << endl;
    cout << endl;

    cout << "3. Prefix Sum + Hash Map" << endl;
    cout << "   Pattern: Track running sum, if (sum-k) seen -> subarray found" << endl;
    cout << "   Use: Subarray sum, longest subarray with sum K" << endl;
    cout << endl;

    cout << "4. Deduplication" << endl;
    cout << "   Pattern: Use hash set to track seen elements" << endl;
    cout << "   Use: Remove duplicates, find first duplicate" << endl;
    cout << endl;

    cout << "5. Sliding Window with Hash Map" << endl;
    cout << "   Pattern: Add right, remove left, track counts" << endl;
    cout << "   Use: Longest substring without repeating chars" << endl;
    cout << endl;

    cout << "--- Topics Covered in 5.2 ---" << endl;
    cout << "01. Hash Set Demo                - Unique elements" << endl;
    cout << "02. Hash Map Demo                - Key-value pairs" << endl;
    cout << "03. Frequency Counting           - Count occurrences" << endl;
    cout << "04. Two Sum                      - Find pair with target sum" << endl;
    cout << "05. Subarray Sum Divisible by K  - Prefix sum mod K" << endl;
    cout << "06. Longest Subarray Sum K       - Prefix sum - K trick" << endl;
    cout << "07. Longest Equal 0s and 1s      - Convert 0 to -1" << endl;
    cout << "08. Hash-Based Patterns Summary  - This file" << endl;

    return 0;
}
