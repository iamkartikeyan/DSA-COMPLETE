#include <iostream>
using namespace std;

int main() {
    int num = 10;

    // ===== IF-ELSE =====
    if (num > 0) {
        cout << "Positive\n";
    } else if (num < 0) {
        cout << "Negative\n";
    } else {
        cout << "Zero\n";
    }

    // Ternary shorthand
    string result = (num % 2 == 0) ? "Even" : "Odd";

    // ===== SWITCH =====
    int day = 3;
    switch (day) {
        case 1: cout << "Monday\n"; break;
        case 2: cout << "Tuesday\n"; break;
        case 3: cout << "Wednesday\n"; break;
        case 4: cout << "Thursday\n"; break;
        case 5: cout << "Friday\n"; break;
        case 6: cout << "Saturday\n"; break;
        case 7: cout << "Sunday\n"; break;
        default: cout << "Invalid day\n"; break;
    }

    // ===== LOOPS =====

    // For loop (when iterations are known)
    cout << "For loop: ";
    for (int i = 0; i < 5; i++) {
        cout << i << " ";
    }
    cout << "\n";

    // While loop (when condition-based)
    cout << "While loop: ";
    int i = 0;
    while (i < 5) {
        cout << i << " ";
        i++;
    }
    cout << "\n";

    // Do-while (executes at least once)
    cout << "Do-while: ";
    int j = 0;
    do {
        cout << j << " ";
        j++;
    } while (j < 5);
    cout << "\n";

    // Range-based for loop (C++11)
    int arr[] = {1, 2, 3, 4, 5};
    cout << "Range-based for: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << "\n";

    // Break and Continue
    cout << "Break at 3: ";
    for (int i = 0; i < 10; i++) {
        if (i == 3) break;
        cout << i << " ";
    }
    cout << "\n";

    cout << "Skip 3: ";
    for (int i = 0; i < 5; i++) {
        if (i == 3) continue;  // Skip iteration
        cout << i << " ";
    }
    cout << "\n";

    // Nested loops - Pattern printing
    cout << "Pattern:\n";
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= i; j++) {
            cout << "* ";
        }
        cout << "\n";
    }

    return 0;
}
