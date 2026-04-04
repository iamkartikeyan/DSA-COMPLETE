// 16.3 Geometry Basics - Points, Lines, Polygons, Convex Hull
// Computational geometry fundamentals for 2D problems.

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-9;  // Floating point tolerance

// ============================================================
// POINT REPRESENTATION
// A point in 2D has (x, y) coordinates.
// Useful operations: distance, midpoint, vector arithmetic.
// ============================================================

struct Point {
    double x, y;
    bool operator==(const Point& other) const {
        return abs(x - other.x) < EPS && abs(y - other.y) < EPS;
    }
    bool operator<(const Point& other) const {
        return x < other.x || (abs(x - other.x) < EPS && y < other.y);
    }
};

// Vector subtraction: b - a
Point operator-(const Point& a, const Point& b) { return {a.x - b.x, a.y - b.y}; }
Point operator+(const Point& a, const Point& b) { return {a.x + b.x, a.y + b.y}; }
Point operator*(const Point& p, double s) { return {p.x * s, p.y * s}; }

// ============================================================
// DISTANCE
// Euclidean: sqrt((x2-x1)^2 + (y2-y1)^2)
// Squared distance (avoids sqrt for comparisons)
// ============================================================

double dist(const Point& a, const Point& b) {
    return hypot(a.x - b.x, a.y - b.y);
}

double distSq(const Point& a, const Point& b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

void demoDistance() {
    cout << "=== Distance ===" << endl;
    Point a = {0, 0}, b = {3, 4};
    cout << "Distance (" << a.x << "," << a.y << ") to (" << b.x << "," << b.y << ") = "
         << dist(a, b) << endl;  // 5.0 (3-4-5 triangle)
    cout << "Squared distance = " << distSq(a, b) << endl;  // 25
    cout << endl;
}

// ============================================================
// MIDPOINT
// Midpoint = ((x1+x2)/2, (y1+y2)/2)
// ============================================================

Point midpoint(const Point& a, const Point& b) {
    return {(a.x + b.x) / 2.0, (a.y + b.y) / 2.0};
}

void demoMidpoint() {
    cout << "=== Midpoint ===" << endl;
    Point a = {1, 2}, b = {5, 6};
    auto m = midpoint(a, b);
    cout << "Midpoint of (" << a.x << "," << a.y << ") and (" << b.x << "," << b.y << ") = "
         << "(" << m.x << "," << m.y << ")" << endl;  // (3, 4)
    cout << endl;
}

// ============================================================
// CROSS PRODUCT (2D)
// cross(a, b) = a.x * b.y - a.y * b.x
// Magnitude = |a| * |b| * sin(theta), gives signed area of parallelogram.
// Sign tells orientation: positive = counterclockwise, negative = clockwise.
// ============================================================

double crossProduct(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

// Cross product of vectors OA and OB (O is origin)
// Equivalent to crossProduct(A - O, B - O)
double crossProduct(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

void demoCrossProduct() {
    cout << "=== Cross Product ===" << endl;
    Point a = {1, 0}, b = {0, 1};
    cout << "cross((" << a.x << "," << a.y << "), (" << b.x << "," << b.y << ")) = "
         << crossProduct(a, b) << endl;  // 1 (counterclockwise turn)

    Point O = {0, 0}, A = {1, 1}, B = {-1, 1};
    cout << "cross(O, A, B) = " << crossProduct(O, A, B) << endl;  // 2
    cout << "Positive = counterclockwise turn, Negative = clockwise" << endl;
    cout << endl;
}

// ============================================================
// DOT PRODUCT
// dot(a, b) = a.x * b.x + a.y * b.y = |a| * |b| * cos(theta)
// Positive = acute angle, Zero = perpendicular, Negative = obtuse.
// ============================================================

double dotProduct(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}

void demoDotProduct() {
    cout << "=== Dot Product ===" << endl;
    Point a = {1, 0}, b = {0, 1};
    cout << "dot((" << a.x << "," << a.y << "), (" << b.x << "," << b.y << ")) = "
         << dotProduct(a, b) << endl;  // 0 (perpendicular)

    Point c = {1, 1}, d = {2, 0};
    cout << "dot((1,1), (2,0)) = " << dotProduct(c, d) << endl;  // 2 (acute)
    cout << endl;
}

// ============================================================
// LINE REPRESENTATION
// ax + by + c = 0 (standard form)
// Or y = mx + c (slope-intercept, fails for vertical lines)
// ============================================================

struct Line {
    double a, b, c;  // ax + by + c = 0

    // Construct from two points
    Line(const Point& p1, const Point& p2) {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = -(a * p1.x + b * p1.y);
    }
};

// ============================================================
// SLOPE
// m = (y2 - y1) / (x2 - x1). Vertical lines have infinite slope.
// ============================================================

double slope(const Point& a, const Point& b) {
    if (abs(a.x - b.x) < EPS) return 1e18;  // Vertical line
    return (b.y - a.y) / (b.x - a.x);
}

void demoLineBasics() {
    cout << "=== Line Basics ===" << endl;
    Point a = {1, 2}, b = {3, 6};
    cout << "Slope = " << slope(a, b) << endl;  // 2
    Line L(a, b);
    cout << "Line: " << L.a << "x + " << L.b << "y + " << L.c << " = 0" << endl;  // -4x + 2y + 0 = 0
    cout << endl;
}

// ============================================================
// LINE INTERSECTION
// Two lines a1x + b1y + c1 = 0 and a2x + b2y + c2 = 0
// Intersect when a1*b2 != a2*b1 (not parallel).
// ============================================================

bool lineIntersection(const Line& L1, const Line& L2, Point& out) {
    double det = L1.a * L2.b - L2.a * L1.b;
    if (abs(det) < EPS) return false;  // Parallel
    out.x = (L1.b * L2.c - L2.b * L1.c) / det;
    out.y = (L2.a * L1.c - L1.a * L2.c) / det;
    return true;
}

void demoLineIntersection() {
    cout << "=== Line Intersection ===" << endl;
    Line L1({0, 0}, {2, 2});   // y = x
    Line L2({0, 2}, {2, 0});   // y = -x + 2

    Point inter;
    if (lineIntersection(L1, L2, inter))
        cout << "Intersection: (" << inter.x << "," << inter.y << ")" << endl;  // (1, 1)
    else
        cout << "Lines are parallel" << endl;
    cout << endl;
}

// ============================================================
// POINT ON LINE SEGMENT
// Check if point P lies on segment AB.
// P must be collinear with AB AND within bounds.
// ============================================================

bool onSegment(const Point& A, const Point& B, const Point& P) {
    if (abs(crossProduct(A, B, P)) > EPS) return false;  // Not collinear
    return min(A.x, B.x) - EPS <= P.x && P.x <= max(A.x, B.x) + EPS &&
           min(A.y, B.y) - EPS <= P.y && P.y <= max(A.y, B.y) + EPS;
}

// ============================================================
// SEGMENT INTERSECTION
// Two segments AB and CD intersect if endpoints are on opposite sides.
// ============================================================

bool segmentsIntersect(const Point& A, const Point& B, const Point& C, const Point& D) {
    double d1 = crossProduct(A, B, C);
    double d2 = crossProduct(A, B, D);
    double d3 = crossProduct(C, D, A);
    double d4 = crossProduct(C, D, B);

    // General case: endpoints on opposite sides
    if (((d1 > EPS && d2 < -EPS) || (d1 < -EPS && d2 > EPS)) &&
        ((d3 > EPS && d4 < -EPS) || (d3 < -EPS && d4 > EPS)))
        return true;

    // Special case: collinear points on segments
    if (abs(d1) < EPS && onSegment(A, B, C)) return true;
    if (abs(d2) < EPS && onSegment(A, B, D)) return true;
    if (abs(d3) < EPS && onSegment(C, D, A)) return true;
    if (abs(d4) < EPS && onSegment(C, D, B)) return true;

    return false;
}

void demoSegmentIntersection() {
    cout << "=== Segment Intersection ===" << endl;
    Point A = {0, 0}, B = {2, 2}, C = {0, 2}, D = {2, 0};
    cout << "Segments (0,0)-(2,2) and (0,2)-(2,0): "
         << (segmentsIntersect(A, B, C, D) ? "Intersect" : "No intersection") << endl;  // Intersect
    cout << endl;
}

// ============================================================
// POLYGON AREA (Shoelace Formula)
// Area = 0.5 * |sum(x_i * y_{i+1} - x_{i+1} * y_i)|
// Works for any simple polygon (non-self-intersecting).
// ============================================================

double polygonArea(const vector<Point>& poly) {
    double area = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
    }
    return abs(area) / 2.0;
}

// Check if point is inside polygon (ray casting algorithm)
bool pointInPolygon(const vector<Point>& poly, const Point& P) {
    int n = poly.size(), count = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        // Check if ray from P to +infinity crosses edge (i, j)
        if (((poly[i].y > P.y) != (poly[j].y > P.y)) &&
            (P.x < (poly[j].x - poly[i].x) * (P.y - poly[i].y) / (poly[j].y - poly[i].y) + poly[i].x))
            count++;
    }
    return count % 2 == 1;
}

void demoPolygon() {
    cout << "=== Polygon Area & Point-in-Polygon ===" << endl;
    vector<Point> triangle = {{0, 0}, {4, 0}, {0, 3}};
    cout << "Triangle area = " << polygonArea(triangle) << endl;  // 6

    vector<Point> square = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    cout << "Square area = " << polygonArea(square) << endl;  // 4

    Point inside = {1, 1}, outside = {3, 3};
    cout << "(1,1) in square? " << (pointInPolygon(square, inside) ? "Yes" : "No") << endl;
    cout << "(3,3) in square? " << (pointInPolygon(square, outside) ? "Yes" : "No") << endl;
    cout << endl;
}

// ============================================================
// CONVEX HULL - Graham Scan
// Smallest convex polygon containing all points.
// Algorithm:
//   1. Find bottom-left point (pivot).
//   2. Sort remaining points by polar angle w.r.t. pivot.
//   3. Process with monotonic chain (keep left turns).
// Time: O(n log n)
// ============================================================

vector<Point> convexHull(vector<Point>& points) {
    int n = points.size();
    if (n <= 2) return points;

    // Find bottom-left point
    int pivot = 0;
    for (int i = 1; i < n; i++)
        if (points[i].y < points[pivot].y ||
            (abs(points[i].y - points[pivot].y) < EPS && points[i].x < points[pivot].x))
            pivot = i;
    swap(points[0], points[pivot]);

    // Sort by polar angle with pivot
    Point O = points[0];
    sort(points.begin() + 1, points.end(), [&O](const Point& a, const Point& b) {
        double cp = crossProduct(O, a, b);
        if (abs(cp) > EPS) return cp > 0;  // Counterclockwise
        return distSq(O, a) < distSq(O, b);  // Closer first if collinear
    });

    // Graham scan
    vector<Point> hull;
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 &&
               crossProduct(hull[hull.size() - 2], hull.back(), points[i]) <= EPS)
            hull.pop_back();
        hull.push_back(points[i]);
    }
    return hull;
}

// ============================================================
// MONOTONE CHAIN (Alternative Convex Hull)
// Simpler implementation, same O(n log n).
// Builds upper and lower chains separately.
// ============================================================

vector<Point> monotoneChain(vector<Point>& points) {
    sort(points.begin(), points.end());
    int n = points.size(), k = 0;
    vector<Point> hull(2 * n);

    // Build lower hull
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && crossProduct(hull[k - 2], hull[k - 1], points[i]) <= EPS) k--;
        hull[k++] = points[i];
    }

    // Build upper hull
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && crossProduct(hull[k - 2], hull[k - 1], points[i]) <= EPS) k--;
        hull[k++] = points[i];
    }

    hull.resize(k - 1);  // Remove duplicate of starting point
    return hull;
}

void demoConvexHull() {
    cout << "=== Convex Hull ===" << endl;
    vector<Point> points = {{0, 3}, {1, 1}, {2, 2}, {4, 1}, {3, 0}, {5, 3}};
    cout << "Points: ";
    for (auto& p : points) cout << "(" << p.x << "," << p.y << ") ";
    cout << endl;

    auto hull = convexHull(points);
    cout << "Convex Hull (Graham Scan): ";
    for (auto& p : hull) cout << "(" << p.x << "," << p.y << ") ";
    cout << endl;

    points = {{0, 3}, {1, 1}, {2, 2}, {4, 1}, {3, 0}, {5, 3}};
    auto hull2 = monotoneChain(points);
    cout << "Convex Hull (Monotone Chain): ";
    for (auto& p : hull2) cout << "(" << p.x << "," << p.y << ") ";
    cout << endl;

    cout << "Hull area = " << polygonArea(hull) << endl;
    cout << endl;
}

// ============================================================
// CLOSEST PAIR OF POINTS (Concept - Divide and Conquer)
// Find minimum distance between any two points.
// Brute force: O(n^2). Divide & conquer: O(n log n).
// ============================================================

void demoClosestPair() {
    cout << "=== Closest Pair of Points (Concept) ===" << endl;
    cout << "Brute force: check all pairs = O(n^2)" << endl;
    cout << "Divide & Conquer: sort, split, merge strip = O(n log n)" << endl;
    cout << "Key insight: strip comparison needs only 7 neighbors." << endl;

    vector<Point> points = {{0, 0}, {3, 4}, {1, 1}, {5, 5}};
    double minDist = 1e18;
    for (size_t i = 0; i < points.size(); i++)
        for (size_t j = i + 1; j < points.size(); j++)
            minDist = min(minDist, dist(points[i], points[j]));
    cout << "Closest pair distance: " << fixed << setprecision(4) << minDist << endl;
    cout << endl;
}

int main() {
    demoDistance();
    demoMidpoint();
    demoCrossProduct();
    demoDotProduct();
    demoLineBasics();
    demoLineIntersection();
    demoSegmentIntersection();
    demoPolygon();
    demoConvexHull();
    demoClosestPair();
    return 0;
}
