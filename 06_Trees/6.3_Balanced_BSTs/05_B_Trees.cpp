/*
 * File: 05_B_Trees.cpp
 * Topic: B-Tree and B+ Tree (Conceptual)
 * Description: Multi-way search trees for databases and file systems
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== B-Trees ===" << endl;
    cout << endl;

    cout << "--- B-Tree Properties (Order-m) ---" << endl;
    cout << "1. Each node has at most m children." << endl;
    cout << "2. Each internal node (except root) has" << endl;
    cout << "   at least ceil(m/2) children." << endl;
    cout << "3. Root has at least 2 children (unless leaf)." << endl;
    cout << "4. All leaves are at the same level." << endl;
    cout << "5. A node with k children has k-1 keys." << endl;
    cout << endl;

    cout << "--- Why B-Trees? ---" << endl;
    cout << "Minimizes disk I/O." << endl;
    cout << "Each node = one disk block read." << endl;
    cout << "Fewer levels = fewer disk reads." << endl;
    cout << endl;

    cout << "--- B+ Tree Variant ---" << endl;
    cout << "Data stored ONLY in leaf nodes." << endl;
    cout << "Leaf nodes linked as a linked list." << endl;
    cout << "Good for range queries in databases." << endl;
    cout << endl;

    cout << "--- Where Used ---" << endl;
    cout << "Database indexes (MySQL, PostgreSQL)" << endl;
    cout << "File systems (NTFS, ext4, HFS+)" << endl;
    cout << "Filesystems that need fast sequential + random access" << endl;
    cout << endl;

    cout << "--- Comparison ---" << endl;
    cout << endl;
    cout << "Tree Type   | Children per node | Use Case" << endl;
    cout << "------------|-------------------|------------------------" << endl;
    cout << "BST         | 2                 | Simple (can be slow)" << endl;
    cout << "AVL         | 2                 | Read-heavy, strict balance" << endl;
    cout << "Red-Black   | 2                 | General purpose (STL maps)" << endl;
    cout << "B-Tree      | Many (100s)       | Databases, file systems" << endl;
    cout << "B+ Tree     | Many (100s)       | Range queries in databases" << endl;

    return 0;
}
