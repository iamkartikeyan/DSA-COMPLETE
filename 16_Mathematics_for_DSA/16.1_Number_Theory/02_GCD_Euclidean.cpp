// 16.1.02 - GCD using Euclidean Algorithm and Extended GCD
// Euclidean: GCD(a, b) = GCD(b, a % b), base case GCD(a, 0) = a.
// Extended: finds x, y such that a*x + b*y = GCD(a, b).

#include <iostream>

using namespace std;

// Euclidean algorithm - iterative
int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// Euclidean algorithm - recursive
int gcdRecursive(int a, int b) {
    if (b == 0) return a;
    return gcdRecursive(b, a % b);
}

// Extended Euclidean Algorithm
// Returns GCD and sets x, y such that a*x + b*y = gcd
int extendedGCD(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int g = extendedGCD(b, a % b, x1, y1);
    // Back-substitute
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// GCD of an array
int gcdOfArray(int arr[], int n) {
    int result = arr[0];
    for (int i = 1; i < n; i++) {
        result = gcd(result, arr[i]);
    }
    return result;
}

// LCM using GCD: LCM(a, b) = (a / GCD(a, b)) * b
// Divide first to avoid overflow
int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

int main() {
    cout << "=== GCD - Euclidean Algorithm ===" << endl;
    cout << "GCD(48, 18) = " << gcd(48, 18) << endl;       // 6
    cout << "GCD(48, 18) recursive = " << gcdRecursive(48, 18) << endl;

    // LCM
    cout << "LCM(48, 18) = " << lcm(48, 18) << endl;       // 144

    // GCD of array
    int arr[] = {12, 18, 24};
    int n = 3;
    cout << "GCD([12, 18, 24]) = " << gcdOfArray(arr, n) << endl;  // 6

    // Extended GCD
    cout << endl << "=== Extended Euclidean Algorithm ===" << endl;
    int a = 35, b = 15;
    int x, y;
    int g = extendedGCD(a, b, x, y);
    cout << a << "*(" << x << ") + " << b << "*(" << y << ") = " << g << endl;
    // 35*(1) + 15*(-2) = 5 = GCD(35, 15)

    // Verify
    int verify = a * x + b * y;
    cout << "Verification: " << a << "*" << x << " + " << b << "*" << y << " = " << verify << endl;

    cout << endl << "Time: O(log(min(a,b))) for GCD, same for Extended" << endl;
    cout << "Space: O(1) iterative, O(log(min(a,b))) recursive" << endl;

    return 0;
}
