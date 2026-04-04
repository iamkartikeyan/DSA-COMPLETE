/*
 * File: 02_CPP_Strings.cpp
 * Topic: C++ std::string - Safe, convenient string handling
 * Description: All string operations without null terminator worries
 */
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    cout << "=== C++ Strings ===" << endl;
    cout << endl;

    // --- Creation ---
    string s1 = "Hello World";
    string s2("Constructor style");
    string s3(5, 'A'); // "AAAAA"

    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    cout << "s3: " << s3 << endl;
    cout << endl;

    // --- Basic operations ---
    cout << "--- Length ---" << endl;
    cout << "s1.length() = " << s1.length() << endl;
    cout << "s1.size() = " << s1.size() << endl;
    cout << "s1.empty()? " << (s1.empty() ? "Yes" : "No") << endl;
    cout << endl;

    // --- Access characters ---
    cout << "--- Access Characters ---" << endl;
    cout << "s1[0] = " << s1[0] << endl;
    cout << "s1[6] = " << s1[6] << endl;
    cout << "s1.front() = " << s1.front() << endl;
    cout << "s1.back() = " << s1.back() << endl;
    cout << endl;

    // --- Concatenation ---
    cout << "--- Concatenation ---" << endl;
    string a = "Hello";
    string b = " World";
    string c = a + b;
    cout << a << " + " << b << " = " << c << endl;

    a += "!!";
    cout << "After += : " << a << endl;
    cout << endl;

    // --- Substring ---
    cout << "--- Substring ---" << endl;
    string str = "Hello World";
    string sub = str.substr(6, 5); // start at 6, take 5 chars
    cout << "substr(6, 5) = \"" << sub << "\"" << endl;
    cout << endl;

    // --- Find ---
    cout << "--- Find ---" << endl;
    size_t pos = str.find("World");
    cout << "find(\"World\") = position " << pos << endl;

    size_t notFound = str.find("xyz");
    cout << "find(\"xyz\") = " << notFound << " (string::npos = " << string::npos << ")" << endl;
    cout << endl;

    // --- Replace ---
    cout << "--- Replace ---" << endl;
    string replaceStr = "Hello World";
    replaceStr.replace(6, 5, "Earth");
    cout << "After replace: " << replaceStr << endl;
    cout << endl;

    // --- Compare ---
    cout << "--- Compare ---" << endl;
    string x = "abc";
    string y = "abc";
    string z = "abd";
    cout << "\"abc\" compare \"abc\" = " << x.compare(y) << " (0 = equal)" << endl;
    cout << "\"abc\" compare \"abd\" = " << x.compare(z) << " (negative = smaller)" << endl;
    cout << endl;

    // --- Reverse ---
    cout << "--- Reverse ---" << endl;
    string rev = "abcdef";
    cout << "Before: " << rev << endl;
    reverse(rev.begin(), rev.end());
    cout << "After:  " << rev << endl;

    return 0;
}
