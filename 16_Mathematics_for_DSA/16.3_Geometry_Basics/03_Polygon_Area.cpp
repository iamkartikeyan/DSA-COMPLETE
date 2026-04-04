// 16.3.03 - Polygon Area
// Shoelace formula: Area = 0.5 * |sum(x_i * y_{i+1} - x_{i+1} * y_i)|
// Works for any simple (non-self-intersecting) polygon.
// Also checks if a point is inside a polygon using ray casting.

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
};

// Shoelace formula for polygon area - O(n)
// Area = 0.5 * |sum(x_i * y_{i+1} - x_{i+1} * y_i)|
double polygonArea(Point poly[], int n) {
    double area = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += poly[i].x * poly[j].y;
        area -= poly[j].x * poly[i].y;
    }
    double d = area;
    if (d < 0) d = -d;
    return d / 2.0;
}

// Check if polygon vertices are in counter-clockwise order
bool isCCW(Point poly[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        sum += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
    }
    return sum > 0;
}

// Cross product of vectors OA and OB
double crossProduct(Point O, Point A, Point B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Check if point P is inside polygon using ray casting algorithm
bool pointInPolygon(Point poly[], int n, Point P) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        // Check if ray from P to +infinity crosses edge (i, j)
        bool cond1 = (poly[i].y > P.y) != (poly[j].y > P.y);
        if (!cond1) continue;
        double xIntersect = (poly[j].x - poly[i].x) * (P.y - poly[i].y) / (poly[j].y - poly[i].y) + poly[i].x;
        if (P.x < xIntersect) {
            count++;
        }
    }
    return count % 2 == 1;
}

int main() {
    cout << fixed << setprecision(2);
    cout << "=== Polygon Area (Shoelace Formula) ===" << endl;

    // Triangle: (0,0), (4,0), (0,3) -> area = 6
    Point triangle[3];
    triangle[0].x = 0; triangle[0].y = 0;
    triangle[1].x = 4; triangle[1].y = 0;
    triangle[2].x = 0; triangle[2].y = 3;

    cout << "Triangle vertices: (0,0), (4,0), (0,3)" << endl;
    cout << "Area = " << polygonArea(triangle, 3) << " (expected: 6)" << endl;
    cout << "CCW order: " << (isCCW(triangle, 3) ? "Yes" : "No") << endl;

    // Square: (0,0), (2,0), (2,2), (0,2) -> area = 4
    Point square[4];
    square[0].x = 0; square[0].y = 0;
    square[1].x = 2; square[1].y = 0;
    square[2].x = 2; square[2].y = 2;
    square[3].x = 0; square[3].y = 2;

    cout << endl << "Square vertices: (0,0), (2,0), (2,2), (0,2)" << endl;
    cout << "Area = " << polygonArea(square, 4) << " (expected: 4)" << endl;

    // Pentagon
    Point pentagon[5];
    pentagon[0].x = 1; pentagon[0].y = 0;
    pentagon[1].x = 4; pentagon[1].y = 1;
    pentagon[2].x = 5; pentagon[2].y = 3;
    pentagon[3].x = 3; pentagon[3].y = 5;
    pentagon[4].x = 0; pentagon[4].y = 3;

    cout << endl << "Pentagon area = " << polygonArea(pentagon, 5) << endl;

    // Point-in-polygon
    cout << endl << "=== Point-in-Polygon (Ray Casting) ===" << endl;
    Point inside, outside;
    inside.x = 1; inside.y = 1;
    outside.x = 3; outside.y = 3;

    cout << "(1,1) in square? " << (pointInPolygon(square, 4, inside) ? "Yes" : "No") << endl;
    cout << "(3,3) in square? " << (pointInPolygon(square, 4, outside) ? "Yes" : "No") << endl;

    // Cross product and orientation
    cout << endl << "=== Cross Product (Orientation) ===" << endl;
    Point O, A, B;
    O.x = 0; O.y = 0;
    A.x = 1; A.y = 1;
    B.x = -1; B.y = 1;

    double cp = crossProduct(O, A, B);
    cout << "cross(O(0,0), A(1,1), B(-1,1)) = " << cp << endl;
    cout << "Positive = counterclockwise turn, Negative = clockwise" << endl;

    cout << endl << "Time: O(n) for polygon area and point-in-polygon" << endl;
    cout << "Space: O(1)" << endl;

    return 0;
}
