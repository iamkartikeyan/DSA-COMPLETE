// 13.1 - Container With Most Water
// Maximize area = min(height[left], height[right]) * (right - left)
// Move the shorter pointer inward to potentially find a taller wall.
// Standalone compilable file with basic C++ only.

#include <iostream>
using namespace std;

int minVal(int a, int b) {
    return (a < b) ? a : b;
}

int maxVal(int a, int b) {
    return (a > b) ? a : b;
}

// Brute force: O(n^2) - check every pair of lines
int maxAreaBruteForce(int height[], int n) {
    int maxWater = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int area = minVal(height[i], height[j]) * (j - i);
            if (area > maxWater) {
                maxWater = area;
            }
        }
    }
    return maxWater;
}

// Two pointers: O(n) - move the shorter line inward
int maxArea(int height[], int n) {
    int left = 0;
    int right = n - 1;
    int maxWater = 0;

    while (left < right) {
        int area = minVal(height[left], height[right]) * (right - left);
        maxWater = maxVal(maxWater, area);

        // Move the shorter pointer: it limits the area
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    return maxWater;
}

int main() {
    cout << "=== Container With Most Water ===" << endl;
    cout << endl;

    int height[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    int n = 9;

    cout << "Heights: ";
    for (int i = 0; i < n; i++) {
        cout << height[i] << " ";
    }
    cout << endl;
    cout << endl;

    cout << "Problem: Find two lines that form container with max water." << endl;
    cout << "  Area = min(height[left], height[right]) * (right - left)" << endl;
    cout << endl;

    cout << "Brute Force O(n^2): " << maxAreaBruteForce(height, n) << endl;
    cout << "Two Pointers O(n):  " << maxArea(height, n) << endl;
    cout << endl;

    cout << "Why moving shorter pointer works:" << endl;
    cout << "  - The area is limited by the SHORTER wall" << endl;
    cout << "  - Width always decreases, so we need a taller wall" << endl;
    cout << "  - Moving the taller wall cannot increase area (shorter wall still limits)" << endl;
    cout << "  - Moving the shorter wall might find a taller wall" << endl;
    cout << endl;

    // Visual demonstration of the optimal container
    int left = 0;
    int right = n - 1;
    int maxWater = 0;
    int bestL = 0, bestR = 0;

    while (left < right) {
        int area = minVal(height[left], height[right]) * (right - left);
        if (area > maxWater) {
            maxWater = area;
            bestL = left;
            bestR = right;
        }
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    cout << "Optimal: indices " << bestL << " and " << bestR
         << " -> heights " << height[bestL] << " and " << height[bestR]
         << ", area = " << maxWater << endl;

    return 0;
}
