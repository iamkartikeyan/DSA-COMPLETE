/*
 * File: 02_Doubly_Linked_List.cpp
 * Topic: Doubly Linked List - Each node has prev and next
 * Description: Forward and backward traversal
 */
#include <iostream>
using namespace std;

struct DNode {
    int data;
    DNode* prev;
    DNode* next;

    DNode(int val) {
        data = val;
        prev = NULL;
        next = NULL;
    }
};

// Insert at end
DNode* insertAtEnd(DNode* head, int val) {
    DNode* newNode = new DNode(val);
    if (head == NULL) {
        return newNode;
    }
    DNode* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

// Print forward
void printForward(DNode* head) {
    DNode* temp = head;
    while (temp != NULL) {
        cout << temp->data;
        if (temp->next != NULL) cout << " <-> ";
        temp = temp->next;
    }
    cout << " <-> NULL" << endl;
}

// Print backward
void printBackward(DNode* head) {
    if (head == NULL) return;

    // Go to last node
    DNode* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Traverse backward
    while (temp != NULL) {
        cout << temp->data;
        if (temp->prev != NULL) cout << " <-> ";
        temp = temp->prev;
    }
    cout << " <-> NULL" << endl;
}

// Free memory
void deleteList(DNode* head) {
    DNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    cout << "=== Doubly Linked List ===" << endl;
    cout << endl;

    DNode* head = NULL;

    head = insertAtEnd(head, 10);
    head = insertAtEnd(head, 20);
    head = insertAtEnd(head, 30);

    cout << "Forward:  ";
    printForward(head);

    cout << "Backward: ";
    printBackward(head);

    cout << endl;
    cout << "--- Structure ---" << endl;
    cout << "Each node has:" << endl;
    cout << "  - data: the value" << endl;
    cout << "  - prev: pointer to previous node" << endl;
    cout << "  - next: pointer to next node" << endl;
    cout << endl;
    cout << "Advantages over Singly Linked List:" << endl;
    cout << "  - Can traverse in BOTH directions" << endl;
    cout << "  - Delete is easier (have prev pointer)" << endl;
    cout << "Disadvantages:" << endl;
    cout << "  - Extra memory for prev pointer" << endl;
    cout << "  - More pointers to maintain on insert/delete" << endl;
    cout << endl;
    cout << "Use: When you need backward traversal" << endl;

    deleteList(head);

    return 0;
}
