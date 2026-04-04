#include <iostream>
#include <string>
using namespace std;

int main() {
    // ===== INPUT/OUTPUT =====
    int num;
    string name;

    // Output with cout
    cout << "Enter your name: ";
    // Input with cin
    cin >> name;  // Reads until whitespace

    // Read full line (including spaces)
    cout << "Enter full name: ";
    cin.ignore();  // Clear newline from buffer
    getline(cin, name);

    cout << "Enter a number: ";
    cin >> num;

    // Formatted output with endl, \n
    cout << "Name: " << name << ", Number: " << num << endl;

    // ===== TYPE CONVERSION =====
    // Implicit (automatic)
    int x = 10;
    double d = x;  // int -> double (widening)
    cout << "Implicit: " << d << "\n";  // 10.0

    // Explicit (casting)
    double pi = 3.14159;
    int intPi = (int)pi;          // C-style cast
    int intPi2 = static_cast<int>(pi);  // C++ style (preferred)
    cout << "Explicit: " << intPi << "\n";  // 3

    // Data loss in narrowing conversion
    int large = 1000;
    char c = large;  // May lose data
    cout << "Narrowing: " << (int)c << "\n";

    // String to number conversion
    string s = "12345";
    int numFromString = stoi(s);
    double doubleFromString = stod(s);
    cout << "stoi: " << numFromString << "\n";

    // Number to string
    string numToString = to_string(42);
    cout << "to_string: " << numToString << "\n";

    // Character to integer
    char ch = '5';
    int digit = ch - '0';  // '5' - '0' = 5
    cout << "Char to int: " << digit << "\n";

    return 0;
}
