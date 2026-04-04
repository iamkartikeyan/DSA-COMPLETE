/*
 * File: 03_Stack_Postfix_Evaluation.cpp
 * Topic: Evaluate postfix expression using stack
 * Description: Reverse Polish Notation evaluation
 */
#include <iostream>
#include <string>
using namespace std;

int isDigit(char c) {
    return c >= '0' && c <= '9';
}

int evaluatePostfix(string expr) {
    int stack[100];
    int top = -1;

    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];

        if (isDigit(c)) {
            // Push digit
            top++;
            stack[top] = c - '0'; // convert char to int
        } else {
            // Operator: pop two operands
            int b = stack[top];
            top--;
            int a = stack[top];
            top--;

            // Apply operator
            int result;
            if (c == '+') result = a + b;
            else if (c == '-') result = a - b;
            else if (c == '*') result = a * b;
            else if (c == '/') result = a / b;
            else {
                cout << "Unknown operator: " << c << endl;
                return -1;
            }

            // Push result back
            top++;
            stack[top] = result;
        }
    }

    return stack[top];
}

int main() {
    cout << "=== Postfix Expression Evaluation ===" << endl;
    cout << endl;

    string expr = "231*+9-";
    cout << "Expression: " << expr << endl;
    cout << endl;

    /*
     * How "231*+9-" is evaluated:
     *
     * Push 2:     stack: [2]
     * Push 3:     stack: [2, 3]
     * Push 1:     stack: [2, 3, 1]
     * Operator *: pop 1, 3 -> 3*1=3, push 3  stack: [2, 3]
     * Operator +: pop 3, 2 -> 2+3=5, push 5  stack: [5]
     * Push 9:     stack: [5, 9]
     * Operator -: pop 9, 5 -> 5-9=-4, push -4  stack: [-4]
     *
     * Result: -4
     *
     * Infix equivalent: ((2 + (3 * 1)) - 9)
     */

    int result = evaluatePostfix(expr);
    cout << "Result: " << result << endl;

    cout << endl;
    cout << "--- How it works ---" << endl;
    cout << "  1. If digit -> push onto stack" << endl;
    cout << "  2. If operator -> pop two values, apply op, push result" << endl;
    cout << "  3. Final answer is the only value left in stack" << endl;
    cout << endl;
    cout << "Postfix: operator comes AFTER operands (AB+)" << endl;
    cout << "Infix:   operator between operands (A+B)" << endl;
    cout << "Prefix:  operator comes BEFORE operands (+AB)" << endl;

    return 0;
}
