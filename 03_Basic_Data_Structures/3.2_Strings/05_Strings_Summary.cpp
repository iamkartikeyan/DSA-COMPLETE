/*
 * File: 05_Strings_Summary.cpp
 * Topic: String properties, C-string vs C++ string summary
 * Description: Key concepts and when to use each
 */
#include <iostream>
using namespace std;

int main() {
    cout << "=== Strings - Summary ===" << endl;
    cout << endl;

    cout << "--- C-Style Strings ---" << endl;
    cout << "Type:        char array with \\0 terminator" << endl;
    cout << "Mutable:     Yes" << endl;
    cout << "Functions:   strlen, strcpy, strcat, strcmp" << endl;
    cout << "Risk:        Buffer overflow, missing \\0" << endl;
    cout << "Use when:    Low-level programming, interfacing with C" << endl;
    cout << endl;

    cout << "--- C++ std::string ---" << endl;
    cout << "Type:        Class with automatic memory management" << endl;
    cout << "Mutable:     Yes" << endl;
    cout << "Functions:   length(), substr(), find(), replace(), etc." << endl;
    cout << "Safety:      Automatic \\0, bounds checking with at()" << endl;
    cout << "Use when:    General purpose (RECOMMENDED)" << endl;
    cout << endl;

    cout << "--- Common Patterns ---" << endl;
    cout << "1. Palindrome:        Two pointers from ends" << endl;
    cout << "2. Anagram:           Sort or frequency count" << endl;
    cout << "3. Pattern matching:  Naive O(n*m), KMP O(n+m)" << endl;
    cout << "4. Reverse words:     Reverse all, then reverse each word" << endl;
    cout << "5. Substring extract: Use substr(pos, len)" << endl;
    cout << endl;

    cout << "--- String Complexity ---" << endl;
    cout << "Access char:  O(1)" << endl;
    cout << "Length:       O(1)" << endl;
    cout << "Concatenation: O(n) - creates new string" << endl;
    cout << "Find:         O(n * m) naive" << endl;
    cout << "Reverse:      O(n)" << endl;
    cout << endl;

    cout << "--- Topics Covered in 3.2 ---" << endl;
    cout << "01. C-Style Strings       - Char arrays, null terminator" << endl;
    cout << "02. C++ Strings             - Safe, convenient std::string" << endl;
    cout << "03. String Pattern Matching - Naive approach" << endl;
    cout << "04. String Common Problems  - Palindrome, anagram, reverse" << endl;
    cout << "05. Strings Summary         - This file" << endl;

    return 0;
}
