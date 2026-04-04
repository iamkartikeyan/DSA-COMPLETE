/*
 * File: 04_Linked_List_Cycle_Detection.cpp
 * Topic: Floyd's Cycle Detection Algorithm (Tortoise and Hare)
 * Description: Detect if linked list has a cycle using two pointers
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

// Floyd's Cycle Detection
bool hasCycle(Node* head) {
    Node* slow = head;
    Node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;         // moves 1 step
        fast = fast->next->next;   // moves 2 steps

        if (slow == fast) {
            return true; // cycle detected
        }
    }
    return false; // no cycle
}

int main() {
    cout << "=== Linked List Cycle Detection ===" << endl;
    cout << endl;

    // --- List WITHOUT cycle ---
    Node* head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(4);

    cout << "--- List without cycle ---" << endl;
    cout << "1 -> 2 -> 3 -> 4 -> NULL" << endl;
    cout << "Has cycle? " << (hasCycle(head1) ? "Yes" : "No") << endl;
    cout << endl;

    // --- List WITH cycle ---
    Node* head2 = new Node(1);
    head2->next = new Node(2);
    head2->next->next = new Node(3);
    head2->next->next->next = new Node(4);
    head2->next->next->next->next = new Node(5);
    head2->next->next->next->next->next = head2->next; // 5 points back to 2

    cout << "--- List with cycle ---" << endl;
    cout << "1 -> 2 -> 3 -> 4 -> 5 -+" << endl;
    cout << "       ^----------------+" << endl;
    cout << "Has cycle? " << (hasCycle(head2) ? "Yes" : "No") << endl;
    cout << endl;

    cout << "--- Floyd's Algorithm ---" << endl;
    cout << "  slow pointer: moves 1 step at a time" << endl;
    cout << "  fast pointer: moves 2 steps at a time" << endl;
    cout << "  If they meet -> CYCLE exists" << endl;
    cout << "  If fast reaches NULL -> NO cycle" << endl;
    cout << endl;

    /*
     * Why it works:
     * In a cycle, fast pointer "laps" slow pointer like runners on a track.
     * They MUST eventually meet.
     */

    cout << "Time: O(n)" << endl;
    cout << "Space: O(1) - no extra memory!" << endl;

    // Free memory (only list1, list2 has cycle so skip for demo)
    delete head1->next->next->next;
    delete head1->next->next;
    delete head1->next;
    delete head1;

    return 0;
}
