/*
 * File: 03_Deque.cpp
 * Topic: Double-Ended Queue - Insert/delete at both ends
 * Description: More flexible than normal queue
 */
#include <iostream>
#include <deque>
using namespace std;

int main() {
    cout << "=== Deque (Double-Ended Queue) ===" << endl;
    cout << endl;

    deque<int> dq;

    // --- Add at both ends ---
    cout << "--- Push Operations ---" << endl;
    dq.push_back(10);   // Add at rear
    cout << "push_back(10)" << endl;
    dq.push_front(20);  // Add at front
    cout << "push_front(20)" << endl;
    dq.push_back(30);   // Add at rear
    cout << "push_back(30)" << endl;
    cout << endl;

    // --- View ---
    cout << "Front: " << dq.front() << endl;  // 20
    cout << "Back:  " << dq.back() << endl;   // 30
    cout << endl;

    cout << "Deque contents: ";
    for (int i = 0; i < dq.size(); i++) {
        cout << dq[i] << " ";
    }
    cout << endl;
    cout << endl;

    // --- Remove from both ends ---
    cout << "--- Pop Operations ---" << endl;
    dq.pop_front();
    cout << "pop_front() -> removed 20" << endl;
    dq.pop_back();
    cout << "pop_back() -> removed 30" << endl;
    cout << endl;

    cout << "Remaining: ";
    for (int i = 0; i < dq.size(); i++) {
        cout << dq[i] << " ";
    }
    cout << endl;

    cout << endl;
    cout << "--- Deque Operations ---" << endl;
    cout << "push_front(x)  - Add x at front    O(1)" << endl;
    cout << "push_back(x)   - Add x at rear      O(1)" << endl;
    cout << "pop_front()    - Remove from front  O(1)" << endl;
    cout << "pop_back()     - Remove from rear   O(1)" << endl;
    cout << "front()        - See front          O(1)" << endl;
    cout << "back()         - See rear           O(1)" << endl;
    cout << endl;
    cout << "Use: Sliding window, palindrome check, undo/redo" << endl;

    return 0;
}
