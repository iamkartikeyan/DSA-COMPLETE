// 10.2 Divide & Conquer Applications
// Merge Sort, Quick Sort, Closest Pair of Points, Strassen's concept

#include <bits/stdc++.h>
#include <cmath>
using namespace std;

// ============================================================
// MERGE SORT: T(n) = 2T(n/2) + O(n) => O(n log n), stable, O(n) space
// ============================================================
void merge(vector<int>& arr, int l, int mid, int r) {
    vector<int> left(arr.begin() + l, arr.begin() + mid + 1);
    vector<int> right(arr.begin() + mid + 1, arr.begin() + r + 1);
    int i = 0, j = 0, k = l;
    // Merge two sorted halves
    while (i < (int)left.size() && j < (int)right.size())
        arr[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];
    while (i < (int)left.size()) arr[k++] = left[i++];
    while (j < (int)right.size()) arr[k++] = right[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;                     // Base: single element
    int mid = l + (r - l) / 2;              // Divide
    mergeSort(arr, l, mid);                 // Sort left half
    mergeSort(arr, mid + 1, r);             // Sort right half
    merge(arr, l, mid, r);                  // Combine (merge)
}

// ============================================================
// QUICK SORT: Avg T(n) = O(n log n), Worst O(n^2), in-place, not stable
// Pivot selection: median-of-three for better average case
// ============================================================
int partition(vector<int>& arr, int l, int r) {
    int pivot = arr[r];                     // Pick last element as pivot
    int i = l - 1;                          // Index of smaller element
    for (int j = l; j < r; j++) {
        if (arr[j] <= pivot) {              // Elements <= pivot go left
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[r]);              // Place pivot in correct position
    return i + 1;
}

void quickSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int pi = partition(arr, l, r);          // Partition around pivot
    quickSort(arr, l, pi - 1);              // Sort elements before pivot
    quickSort(arr, pi + 1, r);              // Sort elements after pivot
}

// ============================================================
// D&C BINARY SEARCH: T(n) = T(n/2) + O(1) => O(log n)
// ============================================================
int binarySearch(const vector<int>& arr, int l, int r, int target) {
    if (l > r) return -1;
    int mid = l + (r - l) / 2;
    if (arr[mid] == target) return mid;
    return (arr[mid] < target) ? binarySearch(arr, mid + 1, r, target)
                                : binarySearch(arr, l, mid - 1, target);
}

// ============================================================
// CLOSEST PAIR OF POINTS (1D simplified): T(n) = 2T(n/2) + O(n) => O(n log n)
// Full 2D version uses divide on x-coordinate + strip checking on y
// ============================================================
double closestPair1D(vector<int>& points) {
    if (points.size() < 2) return -1;
    sort(points.begin(), points.end());     // Must be sorted
    double minDist = INT_MAX;
    for (size_t i = 1; i < points.size(); i++)
        minDist = min(minDist, (double)abs(points[i] - points[i - 1]));
    return minDist;
}

// 2D closest pair (simplified D&C with strip)
struct Point { int x, y; };
double dist(const Point& a, const Point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double bruteForceClosest(const vector<Point>& pts) {
    double d = DBL_MAX;
    for (size_t i = 0; i < pts.size(); i++)
        for (size_t j = i + 1; j < pts.size(); j++)
            d = min(d, dist(pts[i], pts[j]));
    return d;
}

double stripClosest(vector<Point>& strip, double d) {
    // Sort by y-coordinate
    sort(strip.begin(), strip.end(), [](const Point& a, const Point& b) {
        return a.y < b.y;
    });
    // Only need to check next 7 points (geometric proof)
    for (size_t i = 0; i < strip.size(); i++)
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < d; j++)
            d = min(d, dist(strip[i], strip[j]));
    return d;
}

double closest2D(vector<Point>& pts) {
    // Base case: brute force for small sets
    if (pts.size() <= 3) return bruteForceClosest(pts);

    int mid = pts.size() / 2;
    Point midPoint = pts[mid];

    // Divide: split into left and right halves
    vector<Point> left(pts.begin(), pts.begin() + mid);
    vector<Point> right(pts.begin() + mid, pts.end());

    // Conquer: recursively find closest in each half
    double d1 = closest2D(left);
    double d2 = closest2D(right);
    double d = min(d1, d2);

    // Combine: check strip of width 2d around mid line
    vector<Point> strip;
    for (auto& p : pts)
        if (abs(p.x - midPoint.x) < d) strip.push_back(p);

    return min(d, stripClosest(strip, d));
}

// ============================================================
// STRASSEN'S MATRIX MULTIPLICATION CONCEPT
// Naive: O(n^3), Strassen: O(n^log2(7)) ~ O(n^2.81)
// Reduces 8 multiplications to 7 using clever additions
// ============================================================
// Naive matrix multiplication for reference
vector<vector<int>> naiveMultiply(const vector<vector<int>>& A,
                                   const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                C[i][j] += A[i][k] * B[k][j];  // Classic triple loop
    return C;
}

void strassenConcept() {
    cout << "--- Strassen's Matrix Multiplication Concept ---\n";
    cout << "Standard: C[i][j] = Sum(A[i][k] * B[k][j]) for k=0..n-1 => O(n^3)\n";
    cout << "Strassen reduces 8 sub-matrix mults to 7:\n";
    cout << "  Divide each n x n matrix into four n/2 x n/2 blocks\n";
    cout << "  Compute 7 products (P1..P7) using add/sub of blocks\n";
    cout << "  P1 = (A11+A22)(B11+B22), P2 = (A21+A22)B11, ...\n";
    cout << "  Recombine: C11 = P5+P4-P2+P6, etc.\n";
    cout << "Recurrence: T(n) = 7T(n/2) + O(n^2) => O(n^log2(7)) = O(n^2.807)\n";
    cout << "Used for large matrices; overhead makes it slower for small n\n\n";
}

void printMatrix(const vector<vector<int>>& M, const string& label) {
    cout << label << "\n";
    for (auto& row : M) {
        for (int v : row) cout << setw(4) << v;
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    cout << "=== 10.2 Divide & Conquer Applications ===\n\n";

    // --- Merge Sort ---
    vector<int> a = {38, 27, 43, 3, 9, 82, 10};
    cout << "Merge Sort:\n  Before: ";
    for (int x : a) cout << x << " ";
    mergeSort(a, 0, a.size() - 1);
    cout << "\n  After:  ";
    for (int x : a) cout << x << " ";
    cout << "\n\n";

    // --- Quick Sort ---
    vector<int> b = {12, 7, 25, 1, 33, 9, 18};
    cout << "Quick Sort:\n  Before: ";
    for (int x : b) cout << x << " ";
    quickSort(b, 0, b.size() - 1);
    cout << "\n  After:  ";
    for (int x : b) cout << x << " ";
    cout << "\n\n";

    // --- Binary Search ---
    vector<int> sorted = {1, 3, 5, 7, 9, 11, 13};
    cout << "Binary Search in {1,3,5,7,9,11,13}:\n";
    cout << "  Find 7: index " << binarySearch(sorted, 0, sorted.size() - 1, 7) << "\n";
    cout << "  Find 4: index " << binarySearch(sorted, 0, sorted.size() - 1, 4) << "\n\n";

    // --- Closest Pair (1D) ---
    vector<int> pts1d = {10, 3, 7, 1, 15, 2, 8};
    cout << "Closest Pair 1D {10,3,7,1,15,2,8}: distance = "
         << closestPair1D(pts1d) << "\n\n";

    // --- Closest Pair (2D) ---
    vector<Point> pts2d = {{2,3}, {12,30}, {40,50}, {5,1}, {12,10}, {3,4}};
    sort(pts2d.begin(), pts2d.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
    });
    cout << "Closest Pair 2D: distance = " << fixed << setprecision(2)
         << closest2D(pts2d) << "\n\n";

    // --- Matrix Multiplication ---
    vector<vector<int>> A = {{1,2},{3,4}}, B = {{5,6},{7,8}};
    printMatrix(A, "Matrix A:");
    printMatrix(B, "Matrix B:");
    auto C = naiveMultiply(A, B);
    printMatrix(C, "A x B (naive):");
    strassenConcept();

    return 0;
}
