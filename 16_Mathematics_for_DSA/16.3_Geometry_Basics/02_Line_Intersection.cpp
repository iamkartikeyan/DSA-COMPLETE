// 16.3.02 - Line Intersection
// Check if two lines intersect, calculate slope, find intersection point.
// Line representation: ax + by + c = 0 (standard form).

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
};

struct Line {
    double a, b, c;  // ax + by + c = 0
};

// Create line from two points: (y1-y2)*x + (x2-x1)*y + (x1*y2 - x2*y1) = 0
Line lineFromPoints(Point p1, Point p2) {
    Line L;
    L.a = p1.y - p2.y;
    L.b = p2.x - p1.x;
    L.c = -(L.a * p1.x + L.b * p1.y);
    return L;
}

// Calculate slope between two points
double slope(Point a, Point b) {
    double dx = a.x - b.x;
    if (dx < 0) dx = -dx;
    if (dx < EPS) return 1e18;  // Vertical line
    return (b.y - a.y) / (b.x - a.x);
}

// Check if two lines are parallel
bool areParallel(Line L1, Line L2) {
    double det = L1.a * L2.b - L2.a * L1.b;
    double d = det;
    if (d < 0) d = -d;
    return d < EPS;
}

// Find intersection point of two lines
// Returns true if they intersect, false if parallel
bool lineIntersection(Line L1, Line L2, Point& out) {
    double det = L1.a * L2.b - L2.a * L1.b;
    double d = det;
    if (d < 0) d = -d;
    if (d < EPS) return false;  // Parallel lines

    out.x = (L1.b * L2.c - L2.b * L1.c) / det;
    out.y = (L2.a * L1.c - L1.a * L2.c) / det;
    return true;
}

// Check if point P lies on line segment AB
bool onSegment(Point A, Point B, Point P) {
    // Check collinearity using cross product
    double cp = (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
    double d = cp;
    if (d < 0) d = -d;
    if (d > EPS) return false;  // Not collinear

    // Check within bounds
    double minX = A.x < B.x ? A.x : B.x;
    double maxX = A.x > B.x ? A.x : B.x;
    double minY = A.y < B.y ? A.y : B.y;
    double maxY = A.y > B.y ? A.y : B.y;

    return P.x >= minX - EPS && P.x <= maxX + EPS &&
           P.y >= minY - EPS && P.y <= maxY + EPS;
}

// Check if two line segments AB and CD intersect
bool segmentsIntersect(Point A, Point B, Point C, Point D) {
    // Cross products
    double d1 = (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
    double d2 = (B.x - A.x) * (D.y - A.y) - (B.y - A.y) * (D.x - A.x);
    double d3 = (D.x - C.x) * (A.y - C.y) - (D.y - C.y) * (A.x - C.x);
    double d4 = (D.x - C.x) * (B.y - C.y) - (D.y - C.y) * (B.x - C.x);

    // General case: endpoints on opposite sides
    bool generalCase = false;
    if (((d1 > EPS && d2 < -EPS) || (d1 < -EPS && d2 > EPS)) &&
        ((d3 > EPS && d4 < -EPS) || (d3 < -EPS && d4 > EPS))) {
        generalCase = true;
    }

    // Special case: collinear points on segments
    bool specialCase = false;
    double dd1 = d1; if (dd1 < 0) dd1 = -dd1;
    double dd2 = d2; if (dd2 < 0) dd2 = -dd2;
    double dd3 = d3; if (dd3 < 0) dd3 = -dd3;
    double dd4 = d4; if (dd4 < 0) dd4 = -dd4;

    if (dd1 < EPS && onSegment(A, B, C)) specialCase = true;
    if (dd2 < EPS && onSegment(A, B, D)) specialCase = true;
    if (dd3 < EPS && onSegment(C, D, A)) specialCase = true;
    if (dd4 < EPS && onSegment(C, D, B)) specialCase = true;

    return generalCase || specialCase;
}

int main() {
    cout << fixed << setprecision(2);
    cout << "=== Line Basics ===" << endl;

    Point a, b;
    a.x = 1; a.y = 2;
    b.x = 3; b.y = 6;

    cout << "Line through (" << a.x << "," << a.y << ") and (" << b.x << "," << b.y << ")" << endl;
    cout << "Slope = " << slope(a, b) << endl;  // 2

    Line L = lineFromPoints(a, b);
    cout << "Standard form: " << L.a << "x + " << L.b << "y + " << L.c << " = 0" << endl;

    // Line intersection
    cout << endl << "=== Line Intersection ===" << endl;
    Point p1, p2, p3, p4;
    p1.x = 0; p1.y = 0;  p2.x = 2; p2.y = 2;   // y = x
    p3.x = 0; p3.y = 2;  p4.x = 2; p4.y = 0;   // y = -x + 2

    Line L1 = lineFromPoints(p1, p2);
    Line L2 = lineFromPoints(p3, p4);

    cout << "Line 1: (" << p1.x << "," << p1.y << ") to (" << p2.x << "," << p2.y << ")" << endl;
    cout << "Line 2: (" << p3.x << "," << p3.y << ") to (" << p4.x << "," << p4.y << ")" << endl;

    Point inter;
    if (lineIntersection(L1, L2, inter)) {
        cout << "Intersection: (" << inter.x << ", " << inter.y << ")" << endl;  // (1, 1)
    } else {
        cout << "Lines are parallel" << endl;
    }

    // Parallel check
    cout << endl << "=== Parallel Lines Check ===" << endl;
    Point q1, q2, q3, q4;
    q1.x = 0; q1.y = 0;  q2.x = 2; q2.y = 2;   // y = x
    q3.x = 0; q3.y = 1;  q4.x = 2; q4.y = 3;   // y = x + 1 (parallel)

    Line L3 = lineFromPoints(q1, q2);
    Line L4 = lineFromPoints(q3, q4);
    cout << "Lines y=x and y=x+1 are parallel: " << (areParallel(L3, L4) ? "Yes" : "No") << endl;

    // Segment intersection
    cout << endl << "=== Segment Intersection ===" << endl;
    cout << "Segments (0,0)-(2,2) and (0,2)-(2,0): ";
    cout << (segmentsIntersect(p1, p2, p3, p4) ? "Intersect" : "No intersection") << endl;

    // Non-intersecting segments
    Point r1, r2, r3, r4;
    r1.x = 0; r1.y = 0;  r2.x = 1; r2.y = 1;
    r3.x = 3; r3.y = 3;  r4.x = 4; r4.y = 4;
    cout << "Segments (0,0)-(1,1) and (3,3)-(4,4): ";
    cout << (segmentsIntersect(r1, r2, r3, r4) ? "Intersect" : "No intersection") << endl;

    cout << endl << "Time: O(1) for all line operations" << endl;
    cout << "Space: O(1)" << endl;

    return 0;
}
