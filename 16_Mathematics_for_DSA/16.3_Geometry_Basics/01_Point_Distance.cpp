// 16.3.01 - Point and Distance
// Euclidean distance: sqrt((x2-x1)^2 + (y2-y1)^2)
// Manhattan distance: |x2-x1| + |y2-y1|
// Midpoint: ((x1+x2)/2, (y1+y2)/2)

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-9;

// Point structure
struct Point {
    double x, y;
};

// Euclidean distance
double euclideanDistance(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// Squared Euclidean distance (avoids sqrt, useful for comparisons)
double distSq(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// Manhattan distance
double manhattanDistance(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    return dx + dy;
}

// Midpoint
Point midpoint(Point a, Point b) {
    Point m;
    m.x = (a.x + b.x) / 2.0;
    m.y = (a.y + b.y) / 2.0;
    return m;
}

// Check if two points are approximately equal
bool pointsEqual(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    return dx < EPS && dy < EPS;
}

int main() {
    cout << fixed << setprecision(2);
    cout << "=== Distance Between Points ===" << endl;

    Point a, b;
    a.x = 0; a.y = 0;
    b.x = 3; b.y = 4;

    cout << "Point A: (" << a.x << ", " << a.y << ")" << endl;
    cout << "Point B: (" << b.x << ", " << b.y << ")" << endl;

    cout << endl << "Euclidean distance = " << euclideanDistance(a, b) << endl;
    // sqrt(9 + 16) = 5.0 (3-4-5 triangle)

    cout << "Squared distance = " << distSq(a, b) << endl;  // 25

    cout << "Manhattan distance = " << manhattanDistance(a, b) << endl;  // 7

    // Midpoint
    cout << endl << "=== Midpoint ===" << endl;
    Point p1, p2;
    p1.x = 1; p1.y = 2;
    p2.x = 5; p2.y = 6;
    Point m = midpoint(p1, p2);
    cout << "Midpoint of (" << p1.x << "," << p1.y << ") and ("
         << p2.x << "," << p2.y << ") = (" << m.x << ", " << m.y << ")" << endl;  // (3, 4)

    // Multiple points - find closest pair (brute force)
    cout << endl << "=== Closest Pair (Brute Force) ===" << endl;
    Point points[4];
    points[0].x = 0; points[0].y = 0;
    points[1].x = 3; points[1].y = 4;
    points[2].x = 1; points[2].y = 1;
    points[3].x = 5; points[3].y = 5;

    int numPts = 4;
    double minDist = 1e18;
    int minI = 0, minJ = 0;
    for (int i = 0; i < numPts; i++) {
        for (int j = i + 1; j < numPts; j++) {
            double d = euclideanDistance(points[i], points[j]);
            if (d < minDist) {
                minDist = d;
                minI = i;
                minJ = j;
            }
        }
    }
    cout << "Closest pair: (" << points[minI].x << "," << points[minI].y << ") and ("
         << points[minJ].x << "," << points[minJ].y << ")" << endl;
    cout << "Distance: " << minDist << endl;

    cout << endl << "Time: O(1) per distance query, O(n^2) for brute force closest pair" << endl;
    cout << "Space: O(1)" << endl;

    return 0;
}
