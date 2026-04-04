// ============================================================
// 03_Closest_Pair_Points.cpp
// Closest Pair of Points using Divide and Conquer
// ============================================================

#include <iostream>
#include <cmath>

using namespace std;

// ============================================================
// CLOSEST PAIR OF POINTS IN 2D
//
// Problem: Given n points in a 2D plane, find the pair with
//          the smallest Euclidean distance between them.
//
// Brute Force: Check all pairs => O(n^2)
// D&C Approach: Divide, solve halves, check strip => O(n log n)
//
// Recurrence: T(n) = 2*T(n/2) + O(n)  => O(n log n)
//
// Algorithm:
//   1. Sort points by x-coordinate (done once)
//   2. Divide: split points by vertical line at mid
//   3. Conquer: find closest pair in left and right halves
//   4. Combine: check pairs that cross the dividing line
//      (only need to check points within delta of the line)
// ============================================================

// -----------------------------------------------------------
// Structure to represent a point in 2D
// -----------------------------------------------------------

struct Point
{
    int x;
    int y;
};

// -----------------------------------------------------------
// Distance between two points
// -----------------------------------------------------------

double dist(Point p1, Point p2)
{
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    return sqrt((double)(dx * dx + dy * dy));
}

// -----------------------------------------------------------
// Brute Force for small arrays (base case)
// Checks all pairs, returns minimum distance
// -----------------------------------------------------------

double bruteForce(Point points[], int n)
{
    double minDist = 1e18;  // Very large number

    for (int i = 0; i < n; i = i + 1)
    {
        for (int j = i + 1; j < n; j = j + 1)
        {
            double d = dist(points[i], points[j]);
            if (d < minDist)
            {
                minDist = d;
            }
        }
    }

    return minDist;
}

// -----------------------------------------------------------
// Minimum of two doubles
// -----------------------------------------------------------

double minDouble(double a, double b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}

// -----------------------------------------------------------
// Check the "strip" near the dividing line
// Only points within delta distance from the mid-line matter
// Key insight: each point needs to check at most 7 neighbors
// -----------------------------------------------------------

double checkStrip(Point strip[], int stripSize, double delta)
{
    double minDist = delta;

    for (int i = 0; i < stripSize; i = i + 1)
    {
        // Only check next 7 points (proven to be sufficient)
        int j = i + 1;
        int limit = i + 8;
        if (limit > stripSize)
        {
            limit = stripSize;
        }
        while (j < limit)
        {
            double d = dist(strip[i], strip[j]);
            if (d < minDist)
            {
                minDist = d;
            }
            j = j + 1;
        }
    }

    return minDist;
}

// -----------------------------------------------------------
// Helper to sort points by y-coordinate (simple bubble sort
// for clarity; in practice use qsort or merge sort)
// -----------------------------------------------------------

void sortByY(Point points[], int n)
{
    for (int i = 0; i < n - 1; i = i + 1)
    {
        for (int j = 0; j < n - i - 1; j = j + 1)
        {
            if (points[j].y > points[j + 1].y)
            {
                Point temp = points[j];
                points[j] = points[j + 1];
                points[j + 1] = temp;
            }
        }
    }
}

// -----------------------------------------------------------
// Closest pair using D&C
// Precondition: points[] is sorted by x-coordinate
// -----------------------------------------------------------

double closestPairDC(Point points[], int n)
{
    // Base case: use brute force for small arrays
    if (n <= 3)
    {
        return bruteForce(points, n);
    }

    // Divide: find the middle point
    int mid = n / 2;
    Point midPoint = points[mid];

    // Conquer: solve for left and right halves
    double leftDist = closestPairDC(points, mid);
    double rightDist = closestPairDC(points + mid, n - mid);

    // Minimum of the two halves
    double delta = minDouble(leftDist, rightDist);

    // Combine: build strip of points within delta of midline
    Point strip[1000];
    int stripSize = 0;

    for (int i = 0; i < n; i = i + 1)
    {
        int diff = points[i].x - midPoint.x;
        if (diff < 0)
        {
            diff = -diff;
        }
        if (diff < delta)
        {
            strip[stripSize] = points[i];
            stripSize = stripSize + 1;
        }
    }

    // Sort strip by y-coordinate
    sortByY(strip, stripSize);

    // Check strip for closer pairs
    double stripDist = checkStrip(strip, stripSize, delta);

    return minDouble(delta, stripDist);
}

// -----------------------------------------------------------
// Helper: sort points by x-coordinate (bubble sort for clarity)
// -----------------------------------------------------------

void sortByX(Point points[], int n)
{
    for (int i = 0; i < n - 1; i = i + 1)
    {
        for (int j = 0; j < n - i - 1; j = j + 1)
        {
            if (points[j].x > points[j + 1].x)
            {
                Point temp = points[j];
                points[j] = points[j + 1];
                points[j + 1] = temp;
            }
        }
    }
}

// -----------------------------------------------------------
// Helper to print points
// -----------------------------------------------------------

void printPoints(Point points[], int n)
{
    for (int i = 0; i < n; i = i + 1)
    {
        cout << "(" << points[i].x << "," << points[i].y << ") ";
    }
    cout << endl;
}

// ============================================================

int main()
{
    cout << "============================================" << endl;
    cout << "  Closest Pair of Points (D&C)" << endl;
    cout << "============================================" << endl;
    cout << endl;

    // --- Example 1: Simple case ---
    Point points1[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    int n1 = 6;

    cout << "Example 1:" << endl;
    cout << "  Points: ";
    printPoints(points1, n1);

    // Sort by x-coordinate first
    sortByX(points1, n1);

    double d1 = closestPairDC(points1, n1);
    cout << "  Closest distance: " << d1 << endl;
    cout << "  Expected: 1.414 (between (2,3) and (3,4))" << endl;
    cout << endl;

    // --- Example 2: Points on a line ---
    Point points2[] = {{1, 0}, {3, 0}, {5, 0}, {8, 0}, {10, 0}};
    int n2 = 5;

    cout << "Example 2 (on a line):" << endl;
    cout << "  Points: ";
    printPoints(points2, n2);

    sortByX(points2, n2);

    double d2 = closestPairDC(points2, n2);
    cout << "  Closest distance: " << d2 << endl;
    cout << "  Expected: 2.0" << endl;
    cout << endl;

    // --- Example 3: Two very close points ---
    Point points3[] = {{100, 100}, {101, 101}, {200, 200}, {300, 300}};
    int n3 = 4;

    cout << "Example 3:" << endl;
    cout << "  Points: ";
    printPoints(points3, n3);

    sortByX(points3, n3);

    double d3 = closestPairDC(points3, n3);
    cout << "  Closest distance: " << d3 << endl;
    cout << "  Expected: 1.414 (between (100,100) and (101,101))" << endl;
    cout << endl;

    // --- Algorithm explanation ---
    cout << "============================================" << endl;
    cout << "  Algorithm Steps" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "1. Sort all points by x-coordinate" << endl;
    cout << "2. Divide: split at middle x-coordinate" << endl;
    cout << "3. Conquer: recursively find closest pair" << endl;
    cout << "   in left and right halves" << endl;
    cout << "4. Let delta = min(left closest, right closest)" << endl;
    cout << "5. Combine: build a strip of all points within" << endl;
    cout << "   delta distance from the dividing line" << endl;
    cout << "6. Sort strip by y-coordinate" << endl;
    cout << "7. For each point in strip, check at most 7" << endl;
    cout << "   next points (proven sufficient)" << endl;
    cout << "8. Return min(delta, strip closest)" << endl;
    cout << endl;

    // --- Key insight ---
    cout << "============================================" << endl;
    cout << "  Why check only 7 neighbors in the strip?" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Geometric proof shows that in a delta x 2*delta" << endl;
    cout << "rectangle, at most 8 points can exist such that" << endl;
    cout << "no two are closer than delta apart." << endl;
    cout << "So each point needs to check at most 7 others." << endl;
    cout << "This makes the strip check O(n), not O(n^2)." << endl;
    cout << endl;

    // --- Complexity ---
    cout << "============================================" << endl;
    cout << "  Complexity" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Time: O(n log n)" << endl;
    cout << "  Recurrence: T(n) = 2*T(n/2) + O(n)" << endl;
    cout << "  Master Theorem Case 2: O(n log n)" << endl;
    cout << endl;
    cout << "Space: O(n) for strip and recursion stack" << endl;
    cout << endl;
    cout << "Vs Brute Force: O(n^2)" << endl;
    cout << "  D&C is much faster for large n!" << endl;

    return 0;
}
