/*
 * File: 01_C_Style_Strings.cpp
 * Topic: C-style strings - char arrays with null terminator
 * Description: How C-strings work, strlen, strcpy, strcmp
 */
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    cout << "=== C-Style Strings ===" << endl;
    cout << endl;

    // --- Declaration ---
    char str1[] = "Hello";
    // Actually: {'H', 'e', 'l', 'l', 'o', '\0'}
    // '\0' is the NULL TERMINATOR - marks end of string

    cout << "str1: " << str1 << endl;
    cout << "Length: " << strlen(str1) << endl;
    cout << "Size (including \\0): " << sizeof(str1) << endl;
    cout << endl;

    // --- Character array without null ---
    char str2[] = {'H', 'i', '\0'};
    cout << "str2: " << str2 << endl;
    cout << endl;

    // --- Mutable - can change characters ---
    char str3[] = "Hello";
    cout << "Before: " << str3 << endl;
    str3[0] = 'h';
    cout << "After:  " << str3 << endl;
    cout << endl;

    // --- Common C-string functions ---
    cout << "--- Functions ---" << endl;

    // strlen - length (excluding \0)
    char name[] = "Kartikeyan";
    cout << "strlen(\"" << name << "\") = " << strlen(name) << endl;

    // strcpy - copy string
    char dest[20];
    strcpy(dest, name);
    cout << "strcpy: dest = " << dest << endl;

    // strcat - concatenate
    char first[20] = "Hello";
    char last[] = " World";
    strcat(first, last);
    cout << "strcat: " << first << endl;

    // strcmp - compare (0 = equal, <0 = smaller, >0 = larger)
    char a[] = "abc";
    char b[] = "abc";
    char c[] = "abd";
    cout << "strcmp(\"abc\", \"abc\") = " << strcmp(a, b) << endl;
    cout << "strcmp(\"abc\", \"abd\") = " << strcmp(a, c) << endl;

    cout << endl;
    cout << "--- Important ---" << endl;
    cout << "C-strings are NULL-terminated char arrays." << endl;
    cout << "Missing \\0 = undefined behavior (prints garbage)." << endl;
    cout << "Buffer overflow risk - no bounds checking." << endl;
    cout << "Use C++ string for safety." << endl;

    return 0;
}
