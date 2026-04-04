/*
 * File: 01_Hash_Table_Basics.cpp
 * Topic: What is Hash Table, Hash Function
 * Description: Basic concepts of hashing - key, value, hash function, bucket
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Hash Table Basics ===" << endl;
    cout << endl;

    cout << "--- What is a Hash Table? ---" << endl;
    cout << "A hash table stores key-value pairs." << endl;
    cout << "It uses a HASH FUNCTION to convert key -> index." << endl;
    cout << endl;

    cout << "--- Key Terms ---" << endl;
    cout << "Key:          The identifier (e.g., 'apple')" << endl;
    cout << "Value:        The data stored (e.g., 10)" << endl;
    cout << "Hash Function: Maps key to an integer index" << endl;
    cout << "Bucket:       A slot in the hash table array" << endl;
    cout << "Collision:    When two keys map to the same bucket" << endl;
    cout << endl;

    cout << "--- Example ---" << endl;
    cout << "Hash Function: key length % 5" << endl;
    cout << endl;
    cout << "Key        | Length | Hash (index)" << endl;
    cout << "-----------|--------|-------------" << endl;
    cout << "apple      |   5    | 5 % 5 = 0" << endl;
    cout << "bat        |   3    | 3 % 5 = 3" << endl;
    cout << "cat        |   3    | 3 % 5 = 3  <-- COLLISION with bat!" << endl;
    cout << "date       |   4    | 4 % 5 = 4" << endl;
    cout << "elephant   |   8    | 8 % 5 = 3  <-- COLLISION too!" << endl;
    cout << endl;

    cout << "--- Collision Resolution Methods ---" << endl;
    cout << "1. Chaining:       Each bucket is a linked list" << endl;
    cout << "2. Open Addressing: Find next empty slot (probing)" << endl;
    cout << endl;

    cout << "--- Load Factor ---" << endl;
    cout << "Load Factor = Number of entries / Number of buckets" << endl;
    cout << "High load factor = more collisions" << endl;
    cout << "When load factor > 0.75 -> rehash (double the table size)" << endl;
    cout << endl;

    cout << "--- Complexity (Average) ---" << endl;
    cout << "Insert:  O(1)" << endl;
    cout << "Search:  O(1)" << endl;
    cout << "Delete:  O(1)" << endl;
    cout << endl;
    cout << "Worst case (all keys collide): O(n)" << endl;

    return 0;
}
