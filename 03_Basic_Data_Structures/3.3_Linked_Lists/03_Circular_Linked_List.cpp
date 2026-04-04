/*
 * File: 03_Circular_Linked_List.cpp
 * Topic: Circular Linked List - Last node points to first
 * Description: No NULL, continuous loop
 */
#include <iostream>
using namespace std;

struct CNode {
    int data;
    CNode* next;

    CNode(int val) {
        data = val;
        next = NULL;
    }
};

class CircularLinkedList {
    CNode* tail; // points to last node

public:
    CircularLinkedList() {
        tail = NULL;
    }

    // Insert at end
    void insert(int val) {
        CNode* newNode = new CNode(val);

        if (tail == NULL) {
            // First node
            tail = newNode;
            tail->next = tail; // points to itself
            return;
        }

        // Insert after tail, then update tail
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode; // new node is now tail
    }

    // Print list
    void print() {
        if (tail == NULL) return;

        CNode* head = tail->next; // first node
        CNode* temp = head;

        do {
            cout << temp->data;
            if (temp->next != head) {
                cout << " -> ";
            }
            temp = temp->next;
        } while (temp != head);

        cout << " -> (head)" << endl;
    }

    // Free memory
    void deleteList() {
        if (tail == NULL) return;

        CNode* head = tail->next;
        CNode* temp = head;
        do {
            CNode* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != head);

        tail = NULL;
    }
};

int main() {
    cout << "=== Circular Linked List ===" << endl;
    cout << endl;

    CircularLinkedList cll;

    cll.insert(100);
    cll.insert(200);
    cll.insert(300);

    cout << "List: ";
    cll.print();

    cout << endl;
    cout << "--- Structure ---" << endl;
    cout << "Last node's next points to FIRST node (not NULL)." << endl;
    cout << "No NULL terminator - use do-while to traverse." << endl;
    cout << endl;
    cout << "Key difference from singly linked list:" << endl;
    cout << "  - Singly: last node -> NULL" << endl;
    cout << "  - Circular: last node -> first node" << endl;
    cout << endl;
    cout << "Use: Round-robin scheduling, circular buffers," << endl;
    cout << "     games (players take turns in cycle)" << endl;

    cll.deleteList();

    return 0;
}
