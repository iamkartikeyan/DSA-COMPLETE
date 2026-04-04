// 10.1 Divide & Conquer Framework
// D&C paradigm: Divide -> Conquer -> Combine
// Recurrence: T(n) = a*T(n/b) + f(n)
// Master Theorem: compares f(n) to n^(log_b(a))

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// MASTER THEOREM REFERENCE
// T(n) = a*T(n/b) + Theta(n^k * log^p(n))
// Case 1: a > b^k  => T(n) = Theta(n^(log_b(a)))
// Case 2: a == b^k => p >= 0: T(n) = Theta(n^k * log^(p+1)(n))
//                      p == -1: T(n) = Theta(n^k * log(log(n)))
// Case 3: a < b^k  => p >= 0: T(n) = Theta(n^k * log^p(n))
//                       p < 0:  T(n) = Theta(n^k)
// ============================================================

// --- Divide Step: Split problem into subproblems ---
template<typename T>
pair<vector<T>, vector<T>> divide(const vector<T>& arr) {
    int mid = arr.size() / 2;
    return {vector<T>(arr.begin(), arr.begin() + mid),
            vector<T>(arr.begin() + mid, arr.end())};
}

// --- Conquer Step: Solve base cases (small inputs) ---
int conquerBase(int x) { return x; }  // e.g., single element is "sorted"

// --- Combine Step: Merge subproblem results ---
template<typename T>
vector<T> combineSorted(const vector<T>& left, const vector<T>& right) {
    vector<T> result;
    int i = 0, j = 0;
    // Merge two sorted halves
    while (i < (int)left.size() && j < (int)right.size()) {
        if (left[i] <= right[j]) result.push_back(left[i++]);
        else result.push_back(right[j++]);
    }
    while (i < (int)left.size()) result.push_back(left[i++]);
    while (j < (int)right.size()) result.push_back(right[j++]);
    return result;
}

// --- Generic D&C: Max Element (T(n) = 2T(n/2) + O(1), a=2, b=2, k=0 -> Case 1: O(n)) ---
int dcMax(const vector<int>& arr, int l, int r) {
    if (l == r) return arr[l];           // Base case
    int mid = l + (r - l) / 2;           // Divide
    int leftMax = dcMax(arr, l, mid);    // Conquer left
    int rightMax = dcMax(arr, mid + 1, r); // Conquer right
    return max(leftMax, rightMax);       // Combine
}

// --- D&C: Min Element (same recurrence pattern) ---
int dcMin(const vector<int>& arr, int l, int r) {
    if (l == r) return arr[l];
    int mid = l + (r - l) / 2;
    return min(dcMin(arr, l, mid), dcMin(arr, mid + 1, r));
}

// --- D&C: Sum of Array (T(n) = 2T(n/2) + O(1) => O(n)) ---
long long dcSum(const vector<int>& arr, int l, int r) {
    if (l == r) return arr[l];
    int mid = l + (r - l) / 2;
    return dcSum(arr, l, mid) + dcSum(arr, mid + 1, r);
}

// --- D&C: Binary Search (T(n) = T(n/2) + O(1) => a=1,b=2,k=0 => Case 2: O(log n)) ---
int dcBinarySearch(const vector<int>& arr, int l, int r, int target) {
    if (l > r) return -1;
    int mid = l + (r - l) / 2;
    if (arr[mid] == target) return mid;        // Found
    if (arr[mid] < target)
        return dcBinarySearch(arr, mid + 1, r, target);  // Right half
    return dcBinarySearch(arr, l, mid - 1, target);      // Left half
}

// --- D&C: Find Power x^n (T(n) = T(n/2) + O(1) => O(log n)) ---
long long dcPower(long long x, int n) {
    if (n == 0) return 1;
    if (n < 0) return 1 / dcPower(x, -n);
    long long half = dcPower(x, n / 2);  // Conquer half
    if (n % 2 == 0) return half * half;   // Combine (even)
    return half * half * x;               // Combine (odd)
}

// --- D&C: Fibonacci (naive, T(n) = T(n-1) + T(n-2) => exponential, for demo) ---
int dcFibonacci(int n) {
    if (n <= 1) return n;
    return dcFibonacci(n - 1) + dcFibonacci(n - 2);
}

// --- Print helper ---
template<typename T>
void printVec(const string& label, const vector<T>& v) {
    cout << label;
    for (auto x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    cout << "=== 10.1 Divide & Conquer Framework ===\n\n";

    vector<int> arr = {3, 7, 1, 9, 4, 6, 2, 8};
    printVec("Array:", arr);

    // D&C Max/Min/Sum
    cout << "DC Max: " << dcMax(arr, 0, arr.size() - 1) << "\n";
    cout << "DC Min: " << dcMin(arr, 0, arr.size() - 1) << "\n";
    cout << "DC Sum: " << dcSum(arr, 0, arr.size() - 1) << "\n";

    // D&C Binary Search
    vector<int> sorted = {1, 2, 3, 4, 6, 7, 8, 9};
    printVec("Sorted:", sorted);
    cout << "Search 6: index " << dcBinarySearch(sorted, 0, sorted.size() - 1, 6) << "\n";
    cout << "Search 5: index " << dcBinarySearch(sorted, 0, sorted.size() - 1, 5) << "\n";

    // D&C Power
    cout << "2^10 = " << dcPower(2, 10) << "\n";
    cout << "3^5  = " << dcPower(3, 5) << "\n";

    // D&C Fibonacci
    cout << "Fib(10) = " << dcFibonacci(10) << "\n";

    // Divide demonstration
    auto [left, right] = divide(arr);
    printVec("Left half:  ", left);
    printVec("Right half: ", right);

    // Combine demonstration
    vector<int> a = {1, 5, 8}, b = {2, 4, 9};
    printVec("Merged:     ", combineSorted(a, b));

    cout << "\n--- Master Theorem Examples ---\n";
    cout << "Merge Sort:    T(n) = 2T(n/2) + O(n)  => a=2, b=2, k=1 => Case 2: O(n log n)\n";
    cout << "Binary Search: T(n) = T(n/2) + O(1)   => a=1, b=2, k=0 => Case 2: O(log n)\n";
    cout << "Max Element:   T(n) = 2T(n/2) + O(1)  => a=2, b=2, k=0 => Case 1: O(n)\n";
    cout << "Power x^n:     T(n) = T(n/2) + O(1)   => O(log n)\n";
    cout << "Strassen's:    T(n) = 7T(n/2) + O(n^2)=> a=7,b=2,k=2 => log2(7)~2.81: O(n^2.81)\n";

    return 0;
}
