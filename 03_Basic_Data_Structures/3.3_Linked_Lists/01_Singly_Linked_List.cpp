/*
 * File: 01_Singly_Linked_List.cpp
 * Topic: Singly Linked List - Node with data and next pointer
 * Description: Insert at end, delete by value, print, reverse
 */
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = NULL;
    }
};

// Insert at end
Node* insertAtEnd(Node* head, int val) {
    Node* newNode = new Node(val);
    if (head == NULL) {
        return newNode;
    }
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

// Delete by value
Node* deleteByValue(Node* head, int val) {
    if (head == NULL) {
        return NULL;
    }
    // Delete head node
    if (head->data == val) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return head;
    }
    // Search for node to delete
    Node* curr = head;
    while (curr->next != NULL && curr->next->data != val) {
        curr = curr->next;
    }
    if (curr->next != NULL) {
        Node* temp = curr->next;
        curr->next = temp->next;
        delete temp;
    }
    return head;
}

// Reverse the list
Node* reverse(Node* head) {
    Node* prev = NULL;
    Node* curr = head;
    Node* nextNode = NULL;

    while (curr != NULL) {
        nextNode = curr->next; // save next
        curr->next = prev;     // reverse link
        prev = curr;           // move prev forward
        curr = nextNode;       // move curr forward
    }
    return prev; // prev is new head
}

// Print list
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->data;
        if (temp->next != NULL) {
            cout << " -> ";
        }
        temp = temp->next;
    }
    cout << " -> NULL" << endl;
}

// Free memory
void deleteList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    cout << "=== Singly Linked List ===" << endl;
    cout << endl;

    Node* head = NULL;

    // Insert nodes
    head = insertAtEnd(head, 1);
    head = insertAtEnd(head, 2);
    head = insertAtEnd(head, 3);
    head = insertAtEnd(head, 4);

    cout << "After inserts: ";
    printList(head);

    // Delete node
    cout << endl;
    cout << "--- Delete 3 ---" << endl;
    head = deleteByValue(head, 3);
    printList(head);

    // Reverse
    cout << endl;
    cout << "--- Reverse ---" << endl;
    head = reverse(head);
    printList(head);

    cout << endl;
    cout << "--- Structure ---" << endl;
    cout << "Each node has:" << endl;
    cout << "  - data: the value" << endl;
    cout << "  - next: pointer to next node (NULL at end)" << endl;
    cout << endl;
    cout << "Insert at end:   O(n)" << endl;
    cout << "Delete by value: O(n)" << endl;
    cout << "Reverse:         O(n)" << endl;
    cout << "Access by index: O(n) - no random access!" << endl;

    deleteList(head);

    return 0;
}
