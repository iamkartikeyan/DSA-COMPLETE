// 16.3.04 - Geometry Basics Summary
// Complete summary: points, distance, lines, intersection, polygon area.

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-9;
const double PI = 3.14159265358979;

struct Point {
    double x, y;
};

struct Line {
    double a, b, c;  // ax + by + c = 0
};

// ---- Distance ----
double euclideanDistance(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

double manhattanDistance(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    return dx + dy;
}

// ---- Midpoint ----
Point midpoint(Point a, Point b) {
    Point m;
    m.x = (a.x + b.x) / 2.0;
    m.y = (a.y + b.y) / 2.0;
    return m;
}

// ---- Slope ----
double slope(Point a, Point b) {
    double dx = a.x - b.x;
    if (dx < 0) dx = -dx;
    if (dx < EPS) return 1e18;
    return (b.y - a.y) / (b.x - a.x);
}

// ---- Line from points ----
Line lineFromPoints(Point p1, Point p2) {
    Line L;
    L.a = p1.y - p2.y;
    L.b = p2.x - p1.x;
    L.c = -(L.a * p1.x + L.b * p1.y);
    return L;
}

// ---- Line intersection ----
bool lineIntersection(Line L1, Line L2, Point& out) {
    double det = L1.a * L2.b - L2.a * L1.b;
    double d = det;
    if (d < 0) d = -d;
    if (d < EPS) return false;
    out.x = (L1.b * L2.c - L2.b * L1.c) / det;
    out.y = (L2.a * L1.c - L1.a * L2.c) / det;
    return true;
}

// ---- Cross product ----
double crossProduct(Point O, Point A, Point B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// ---- Dot product ----
double dotProduct(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

// ---- Polygon area (Shoelace) ----
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

// ---- Point in polygon (ray casting) ----
bool pointInPolygon(Point poly[], int n, Point P) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        bool cond1 = (poly[i].y > P.y) != (poly[j].y > P.y);
        if (!cond1) continue;
        double xIntersect = (poly[j].x - poly[i].x) * (P.y - poly[i].y) / (poly[j].y - poly[i].y) + poly[i].x;
        if (P.x < xIntersect) count++;
    }
    return count % 2 == 1;
}

int main() {
    cout << fixed << setprecision(2);
    cout << "========================================" << endl;
    cout << "  GEOMETRY BASICS - COMPLETE SUMMARY" << endl;
    cout << "========================================" << endl;

    // 1. Distance
    cout << endl << "1. DISTANCE" << endl;
    Point a, b;
    a.x = 0; a.y = 0;
    b.x = 3; b.y = 4;
    cout << "   A(0,0) to B(3,4):" << endl;
    cout << "   Euclidean: " << euclideanDistance(a, b) << endl;  // 5
    cout << "   Manhattan: " << manhattanDistance(a, b) << endl;  // 7

    // 2. Midpoint
    cout << endl << "2. MIDPOINT" << endl;
    Point p1, p2;
    p1.x = 1; p1.y = 2;
    p2.x = 5; p2.y = 6;
    Point m = midpoint(p1, p2);
    cout << "   Midpoint of (1,2) and (5,6) = (" << m.x << ", " << m.y << ")" << endl;  // (3, 4)

    // 3. Line and slope
    cout << endl << "3. LINE AND SLOPE" << endl;
    cout << "   Slope of (1,2)-(3,6) = " << slope(p1, p2) << endl;  // 2
    Line L = lineFromPoints(p1, p2);
    cout << "   Line: " << L.a << "x + " << L.b << "y + " << L.c << " = 0" << endl;

    // 4. Line intersection
    cout << endl << "4. LINE INTERSECTION" << endl;
    Point q1, q2, q3, q4;
    q1.x = 0; q1.y = 0;  q2.x = 2; q2.y = 2;
    q3.x = 0; q3.y = 2;  q4.x = 2; q4.y = 0;
    Line L1 = lineFromPoints(q1, q2);
    Line L2 = lineFromPoints(q3, q4);
    Point inter;
    if (lineIntersection(L1, L2, inter)) {
        cout << "   Intersection: (" << inter.x << ", " << inter.y << ")" << endl;  // (1, 1)
    }

    // 5. Cross and dot product
    cout << endl << "5. CROSS AND DOT PRODUCT" << endl;
    Point O, A, B;
    O.x = 0; O.y = 0;
    A.x = 1; A.y = 0;
    B.x = 0; B.y = 1;
    cout << "   cross((1,0), (0,1)) = " << crossProduct(O, A, B) << endl;  // 1
    cout << "   dot((1,0), (0,1)) = " << dotProduct(A, B) << endl;  // 0 (perpendicular)

    // 6. Polygon area
    cout << endl << "6. POLYGON AREA (Shoelace)" << endl;
    Point tri[3];
    tri[0].x = 0; tri[0].y = 0;
    tri[1].x = 4; tri[1].y = 0;
    tri[2].x = 0; tri[2].y = 3;
    cout << "   Triangle (0,0),(4,0),(0,3): area = " << polygonArea(tri, 3) << endl;  // 6

    Point sq[4];
    sq[0].x = 0; sq[0].y = 0;
    sq[1].x = 2; sq[1].y = 0;
    sq[2].x = 2; sq[2].y = 2;
    sq[3].x = 0; sq[3].y = 2;
    cout << "   Square (0,0),(2,0),(2,2),(0,2): area = " << polygonArea(sq, 4) << endl;  // 4

    // 7. Point-in-polygon
    cout << endl << "7. POINT-IN-POLYGON (Ray Casting)" << endl;
    Point inside, outside;
    inside.x = 1; inside.y = 1;
    outside.x = 3; outside.y = 3;
    cout << "   (1,1) in square? " << (pointInPolygon(sq, 4, inside) ? "Yes" : "No") << endl;
    cout << "   (3,3) in square? " << (pointInPolygon(sq, 4, outside) ? "Yes" : "No") << endl;

    // Complexity summary
    cout << endl << "========================================" << endl;
    cout << "  COMPLEXITY SUMMARY" << endl;
    cout << "========================================" << endl;
    cout << "  Distance:        O(1) time, O(1) space" << endl;
    cout << "  Midpoint:        O(1) time, O(1) space" << endl;
    cout << "  Slope:           O(1) time, O(1) space" << endl;
    cout << "  Line intersection: O(1) time, O(1) space" << endl;
    cout << "  Cross/Dot product: O(1) time, O(1) space" << endl;
    cout << "  Polygon area:    O(n) time, O(1) space" << endl;
    cout << "  Point-in-polygon: O(n) time, O(1) space" << endl;

    return 0;
}
