/*
 * File: 02_Stack_Parenthesis_Matching.cpp
 * Topic: Valid parentheses using stack
 * Description: Check if brackets are balanced
 */
#include <iostream>
#include <string>
using namespace std;

// Simple stack for characters
class CharStack {
    char* arr;
    int top;
    int capacity;

public:
    CharStack(int cap) {
        capacity = cap;
        top = -1;
        arr = new char[capacity];
    }

    ~CharStack() {
        delete[] arr;
    }

    void push(char c) {
        top++;
        arr[top] = c;
    }

    char pop() {
        char c = arr[top];
        top--;
        return c;
    }

    char peek() {
        return arr[top];
    }

    bool isEmpty() {
        return top == -1;
    }
};

bool validParentheses(string s) {
    CharStack st(s.length());

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        // Opening bracket -> push
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        }
        // Closing bracket -> check match
        else {
            if (st.isEmpty()) {
                return false; // no opening bracket to match
            }

            char top = st.pop();

            if (c == ')' && top != '(') return false;
            if (c == '}' && top != '{') return false;
            if (c == ']' && top != '[') return false;
        }
    }

    return st.isEmpty(); // all brackets must be matched
}

int main() {
    cout << "=== Parenthesis Matching ===" << endl;
    cout << endl;

    string tests[] = {
        "{[()]}",   // valid
        "([)]",     // invalid - wrong order
        "((()))",   // valid
        "{[}",      // invalid - mismatch
        "()",       // valid
        "][",       // invalid - closing before opening
    };
    int n = 6;

    for (int i = 0; i < n; i++) {
        bool result = validParentheses(tests[i]);
        cout << "\"" << tests[i] "\" -> " << (result ? "Valid" : "Invalid") << endl;
    }

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. Opening bracket -> push onto stack" << endl;
    cout << "  2. Closing bracket -> pop and check match" << endl;
    cout << "  3. If stack empty at closing -> invalid" << endl;
    cout << "  4. If stack not empty at end -> invalid" << endl;
    cout << endl;
    cout << "Time: O(n)" << endl;
    cout << "Space: O(n) for stack" << endl;

    return 0;
}
