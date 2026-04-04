/*
 * File: 05_Linked_List_Summary.cpp
 * Topic: All linked list types comparison
 * Description: Singly vs Doubly vs Circular, when to use each
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Linked Lists - Summary ===" << endl;
    cout << endl;

    cout << "--- Singly Linked List ---" << endl;
    cout << "Node:     [data | next]" << endl;
    cout << "End:      next = NULL" << endl;
    cout << "Traverse: Forward only" << endl;
    cout << "Insert:   O(1) at head, O(n) at end" << endl;
    cout << "Delete:   O(n) - need to find node + prev" << endl;
    cout << endl;

    cout << "--- Doubly Linked List ---" << endl;
    cout << "Node:     [prev | data | next]" << endl;
    cout << "End:      prev = NULL, next = NULL" << endl;
    cout << "Traverse: Both directions" << endl;
    cout << "Insert:   O(1) at head, O(n) at end" << endl;
    cout << "Delete:   O(n) but easier (have prev pointer)" << endl;
    cout << endl;

    cout << "--- Circular Linked List ---" << endl;
    cout << "Node:     [data | next]" << endl;
    cout << "End:      last->next = first (no NULL)" << endl;
    cout << "Traverse: Continuous loop" << endl;
    cout << "Use:      Round-robin, circular buffer" << endl;
    cout << endl;

    cout << "--- Linked List vs Array ---" << endl;
    cout << "Feature       | Array        | Linked List" << endl;
    cout << "--------------|--------------|-------------------" << endl;
    cout << "Size          | Fixed        | Dynamic" << endl;
    cout << "Access        | O(1)         | O(n)" << endl;
    cout << "Insert/Delete | O(n) - shift | O(1) if node known" << endl;
    cout << "Memory        | Less         | More (pointers)" << endl;
    cout << "Cache         | Friendly     | Not friendly" << endl;
    cout << "Overflow      | Possible     | Only if no memory" << endl;
    cout << endl;

    cout << "--- Topics Covered in 3.3 ---" << endl;
    cout << "01. Singly Linked List        - Insert, delete, reverse" << endl;
    cout << "02. Doubly Linked List        - Forward and backward traversal" << endl;
    cout << "03. Circular Linked List      - Last node points to first" << endl;
    cout << "04. Linked List Cycle Detection - Floyd's algorithm" << endl;
    cout << "05. Linked List Summary       - This file" << endl;

    return 0;
}
