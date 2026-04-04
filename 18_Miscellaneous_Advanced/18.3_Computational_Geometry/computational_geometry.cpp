// Module 18.3: Computational Geometry
// Covers: Line Sweep, Closest Pair of Points, Polygon Area
// Fundamental algorithms for geometric problems.

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <set>
#include <tuple>

using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-9;

// ============================================================
// Basic Geometry Primitives
// ============================================================
struct Point {
    double x, y;
    bool operator<(const Point& o) const { return x < o.x || (x == o.x && y < o.y); }
    bool operator==(const Point& o) const { return abs(x-o.x) < EPS && abs(y-o.y) < EPS; }
    Point operator-(const Point& o) const { return {x-o.x, y-o.y}; }
    double dist(const Point& o) const { return hypot(x-o.x, y-o.y); }
};

// Cross product of vectors OA and OB: |OA x OB|
double cross(Point O, Point A, Point B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Dot product of vectors OA and OB
double dot(Point O, Point A, Point B) {
    return (A.x - O.x) * (B.x - O.x) + (A.y - O.y) * (B.y - O.y);
}

// ============================================================
// 1. Line Sweep Algorithm
// Concept: Process geometric events sorted by coordinate,
//           maintaining a data structure of "active" objects.
// Classic application: Count/Find intersections of line segments.
// Simplified demo: Find overlapping intervals (1D sweep).
// ============================================================
struct Event {
    double x;
    int type; // +1 = start, -1 = end
    int id;
    bool operator<(const Event& o) const {
        return x < o.x || (x == o.x && type > o.type); // starts before ends
    }
};

// Find overlapping intervals using sweep line
vector<pair<int,int>> findOverlaps(const vector<pair<double,double>>& intervals) {
    vector<Event> events;
    for (int i = 0; i < (int)intervals.size(); i++) {
        events.push_back({intervals[i].first, 1, i});
        events.push_back({intervals[i].second, -1, i});
    }
    sort(events.begin(), events.end());

    vector<pair<int,int>> overlaps;
    set<int> active;

    for (auto& e : events) {
        if (e.type == 1) {
            for (int other : active)
                overlaps.push_back({other, e.id});
            active.insert(e.id);
        } else {
            active.erase(e.id);
        }
    }
    return overlaps;
}

// Count maximum number of overlapping intervals at any point
int maxOverlaps(const vector<pair<double,double>>& intervals) {
    vector<Event> events;
    for (auto& [l, r] : intervals) {
        events.push_back({l, 1, 0});
        events.push_back({r, -1, 0});
    }
    sort(events.begin(), events.end());

    int maxCount = 0, current = 0;
    for (auto& e : events) {
        current += e.type;
        maxCount = max(maxCount, current);
    }
    return maxCount;
}

// ============================================================
// 2. Closest Pair of Points (Divide & Conquer)
// O(n log n) algorithm.
// 1. Sort points by x, split into halves, recursively find closest in each.
// 2. Merge: check strip of width d around the dividing line.
// Key lemma: at most 7 points to check for each point in the strip.
// ============================================================

// Brute force for small inputs
double bruteForce(const vector<Point>& pts) {
    double minD = 1e18;
    for (int i = 0; i < (int)pts.size(); i++)
        for (int j = i+1; j < (int)pts.size(); j++)
            minD = min(minD, pts[i].dist(pts[j]));
    return minD;
}

// Merge step: check strip
double stripClosest(vector<Point>& strip, double d) {
    // Sort strip by y-coordinate
    sort(strip.begin(), strip.end(), [](const Point& a, const Point& b) {
        return a.y < b.y;
    });

    double minD = d;
    for (int i = 0; i < (int)strip.size(); i++) {
        for (int j = i+1; j < (int)strip.size() && strip[j].y - strip[i].y < minD; j++) {
            minD = min(minD, strip[i].dist(strip[j]));
        }
    }
    return minD;
}

// Recursive divide and conquer
double closestPairRec(vector<Point>& Px, int n) {
    if (n <= 3) return bruteForce(vector<Point>(Px.begin(), Px.begin()+n));

    int mid = n / 2;
    Point midPoint = Px[mid];

    double dl = closestPairRec(Px, mid);
    double dr = closestPairRec(Px.begin() + mid, n - mid);
    double d = min(dl, dr);

    // Build strip: points within distance d of midline
    vector<Point> strip;
    for (int i = 0; i < n; i++)
        if (abs(Px[i].x - midPoint.x) < d)
            strip.push_back(Px[i]);

    return min(d, stripClosest(strip, d));
}

double closestPair(vector<Point> pts) {
    sort(pts.begin(), pts.end());
    return closestPairRec(pts, pts.size());
}

// ============================================================
// 3. Polygon Area
// Shoelace Formula: Area = 0.5 * |sum(x_i * y_{i+1} - x_{i+1} * y_i)|
// O(n) time. Works for any simple (non-self-intersecting) polygon.
// Orientation: positive sum = counter-clockwise, negative = clockwise.
// ============================================================
double polygonArea(const vector<Point>& poly) {
    double area = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += poly[i].x * poly[j].y;
        area -= poly[j].x * poly[i].y;
    }
    return abs(area) / 2.0;
}

// Check if polygon vertices are in counter-clockwise order
bool isCCW(const vector<Point>& poly) {
    double sum = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        sum += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
    }
    return sum > 0;
}

// ============================================================
// Convex Hull (Graham Scan) - bonus utility
// O(n log n): sort by polar angle, then build upper/lower hull.
// ============================================================
vector<Point> convexHull(vector<Point> pts) {
    if (pts.size() <= 2) return pts;
    sort(pts.begin(), pts.end());

    auto build = [&](vector<Point>& hull) {
        for (auto& p : pts) {
            while (hull.size() >= 2 &&
                   cross(hull[hull.size()-2], hull.back(), p) <= EPS)
                hull.pop_back();
            hull.push_back(p);
        }
    };

    vector<Point> upper, lower;
    build(upper);
    reverse(pts.begin(), pts.end());
    build(lower);

    // Remove last point (duplicate of first in other hull)
    upper.pop_back();
    lower.pop_back();
    upper.insert(upper.end(), lower.begin(), lower.end());
    return upper;
}

// ============================================================
// Main: Demonstrate all computational geometry algorithms
// ============================================================
int main() {
    cout << fixed << setprecision(2);
    cout << "===== Module 18.3: Computational Geometry =====\n\n";

    // --- 1. Line Sweep ---
    cout << "1. Line Sweep (Interval Overlaps):\n";
    vector<pair<double,double>> intervals = {
        {1, 5}, {2, 7}, {4, 6}, {8, 10}, {9, 12}
    };
    cout << "  Intervals: ";
    for (auto& [l,r] : intervals) cout << "[" << l << "," << r << "] ";
    cout << "\n";

    auto overlaps = findOverlaps(intervals);
    cout << "  Overlapping pairs:\n";
    for (auto& [i, j] : overlaps)
        cout << "    [" << intervals[i].first << "," << intervals[i].second
             << "] and [" << intervals[j].first << "," << intervals[j].second << "]\n";
    cout << "  Max simultaneous overlaps: " << maxOverlaps(intervals) << "\n";

    // --- 2. Closest Pair ---
    cout << "\n2. Closest Pair of Points:\n";
    vector<Point> pts = {
        {2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}, {50, 55}, {11, 12}
    };
    cout << "  Points: ";
    for (auto& p : pts) cout << "(" << p.x << "," << p.y << ") ";
    cout << "\n";
    double minDist = closestPair(pts);
    cout << "  Minimum distance: " << minDist << "\n";

    // --- 3. Polygon Area ---
    cout << "\n3. Polygon Area (Shoelace Formula):\n";

    // Triangle: (0,0), (4,0), (0,3) -> area = 6
    vector<Point> triangle = {{0,0}, {4,0}, {0,3}};
    cout << "  Triangle (0,0),(4,0),(0,3): area = " << polygonArea(triangle) << " (expect 6)\n";
    cout << "  Is CCW: " << boolalpha << isCCW(triangle) << "\n";

    // Square: (0,0), (5,0), (5,5), (0,5) -> area = 25
    vector<Point> square = {{0,0}, {5,0}, {5,5}, {0,5}};
    cout << "  Square (0,0),(5,0),(5,5),(0,5): area = " << polygonArea(square) << " (expect 25)\n";

    // Pentagon (regular-ish)
    vector<Point> pentagon = {{1,0}, {4,1}, {5,3}, {3,5}, {0,3}};
    cout << "  Pentagon: area = " << polygonArea(pentagon) << "\n";

    // --- Bonus: Convex Hull ---
    cout << "\n4. Bonus - Convex Hull (Graham Scan):\n";
    vector<Point> scatter = {
        {0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {3, 0}, {5, 1}, {4, 3}, {2, 5}
    };
    cout << "  Input points: ";
    for (auto& p : scatter) cout << "(" << p.x << "," << p.y << ") ";
    cout << "\n";
    auto hull = convexHull(scatter);
    cout << "  Convex hull: ";
    for (auto& p : hull) cout << "(" << p.x << "," << p.y << ") ";
    cout << "\n";
    cout << "  Hull area: " << polygonArea(hull) << "\n";

    cout << "\n===== All computational geometry algorithms demonstrated =====\n";
    return 0;
}
