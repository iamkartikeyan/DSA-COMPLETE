/*
 * Classic Greedy Algorithms
 *
 * Activity Selection:
 *   - Max non-overlapping activities
 *   - Sort by finish time, greedily pick earliest finish
 *   - Time: O(n log n)
 *
 * Fractional Knapsack:
 *   - Maximize value, can take fractions of items
 *   - Sort by value/weight ratio, fill greedily
 *   - Time: O(n log n)
 *
 * Huffman Coding:
 *   - Build optimal prefix-free binary tree
 *   - Always merge two smallest frequencies
 *   - Time: O(n log n) with min-heap
 *
 * Job Sequencing with Deadlines:
 *   - Maximize profit by scheduling jobs before deadlines
 *   - Sort by profit descending, assign latest available slot
 *   - Time: O(n^2) or O(n log n) with DSU
 *
 * Minimum Coins (Canonical Systems):
 *   - Works for standard coin systems (e.g., US coins)
 *   - Sort coins descending, take as many as possible
 *   - Fails for non-canonical systems (see fundamentals)
 *
 * Interval Scheduling / Merging:
 *   - Merge overlapping intervals
 *   - Sort by start time, merge if overlapping
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <numeric>
using namespace std;

// ============================================================
// 1. ACTIVITY SELECTION
//    Max compatible activities (non-overlapping)
// ============================================================
struct Activity {
    int id, start, finish;
};

vector<int> activitySelection(vector<Activity>& acts) {
    sort(acts.begin(), acts.end(),
         [](const Activity& a, const Activity& b) { return a.finish < b.finish; });

    vector<int> result;
    int lastFinish = -1;
    for (auto& a : acts) {
        if (a.start >= lastFinish) {
            result.push_back(a.id);
            lastFinish = a.finish;
        }
    }
    return result;
}

// ============================================================
// 2. FRACTIONAL KNAPSACK
// ============================================================
struct Item {
    int id, weight, value;
    double ratio() const { return (double)value / weight; }
};

double fractionalKnapsack(vector<Item>& items, int capacity) {
    sort(items.begin(), items.end(),
         [](const Item& a, const Item& b) { return a.ratio() > b.ratio(); });

    double totalValue = 0;
    for (auto& item : items) {
        if (capacity >= item.weight) {
            totalValue += item.value;
            capacity -= item.weight;
            cout << "  Take item " << item.id << " fully (w=" << item.weight
                 << ", v=" << item.value << ")\n";
        } else {
            double fraction = (double)capacity / item.weight;
            totalValue += item.value * fraction;
            cout << "  Take " << (int)(fraction * 100) << "% of item " << item.id
                 << " (weight=" << capacity << ")\n";
            capacity = 0;
            break;
        }
    }
    return totalValue;
}

// ============================================================
// 3. HUFFMAN CODING
//    Build optimal prefix-free codes using min-heap
// ============================================================
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left, *right;
    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    HuffmanNode(int f, HuffmanNode* l, HuffmanNode* r)
        : ch('$'), freq(f), left(l), right(r) {}
};

struct CompareNode {
    bool operator()(HuffmanNode* a, HuffmanNode* b) { return a->freq > b->freq; }
};

void printCodes(HuffmanNode* root, string code, vector<pair<char, string>>& codes) {
    if (!root) return;
    if (root->ch != '$') { codes.push_back({root->ch, code}); return; }
    printCodes(root->left, code + "0", codes);
    printCodes(root->right, code + "1", codes);
}

void huffmanCoding(const vector<pair<char, int>>& freq) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNode> pq;
    for (auto& [ch, f] : freq) pq.push(new HuffmanNode(ch, f));

    while (pq.size() > 1) {
        auto* left = pq.top(); pq.pop();
        auto* right = pq.top(); pq.pop();
        pq.push(new HuffmanNode(left->freq + right->freq, left, right));
    }

    vector<pair<char, string>> codes;
    printCodes(pq.top(), "", codes);

    cout << "  Char | Code\n";
    for (auto& [ch, code] : codes)
        cout << "   " << ch << "   | " << code << "\n";

    // Cleanup
    queue<HuffmanNode*> q; q.push(pq.top());
    while (!q.empty()) {
        auto* node = q.front(); q.pop();
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
        delete node;
    }
}

// ============================================================
// 4. JOB SEQUENCING WITH DEADLINES
//    Maximize profit, each job takes 1 unit, must finish by deadline
// ============================================================
struct Job {
    int id, deadline, profit;
};

pair<int, int> jobSequencing(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(),
         [](const Job& a, const Job& b) { return a.profit > b.profit; });

    int maxDeadline = 0;
    for (auto& j : jobs) maxDeadline = max(maxDeadline, j.deadline);

    vector<bool> slot(maxDeadline + 1, false);
    int count = 0, totalProfit = 0;

    for (auto& job : jobs) {
        // Find latest available slot before deadline
        for (int t = job.deadline; t > 0; --t) {
            if (!slot[t]) {
                slot[t] = true;
                count++;
                totalProfit += job.profit;
                break;
            }
        }
    }
    return {count, totalProfit};
}

// ============================================================
// 5. MINIMUM COINS (Canonical Systems)
//    Works for standard coin systems like {1, 5, 10, 25}
// ============================================================
vector<pair<int, int>> minCoinsGreedy(vector<int>& coins, int amount) {
    sort(coins.rbegin(), coins.rend());
    vector<pair<int, int>> result;
    for (int c : coins) {
        if (amount == 0) break;
        int count = amount / c;
        if (count > 0) {
            result.push_back({c, count});
            amount %= c;
        }
    }
    return result;
}

// ============================================================
// 6. INTERVAL MERGING
//    Merge overlapping intervals
// ============================================================
struct Interval {
    int start, end;
    string toString() const { return "[" + to_string(start) + "," + to_string(end) + "]"; }
};

vector<Interval> mergeIntervals(vector<Interval>& intervals) {
    if (intervals.empty()) return {};
    sort(intervals.begin(), intervals.end(),
         [](const Interval& a, const Interval& b) { return a.start < b.start; });

    vector<Interval> merged = {intervals[0]};
    for (size_t i = 1; i < intervals.size(); ++i) {
        if (intervals[i].start <= merged.back().end)
            merged.back().end = max(merged.back().end, intervals[i].end);
        else
            merged.push_back(intervals[i]);
    }
    return merged;
}

// ============================================================
// 7. INTERVAL SCHEDULING (weighted version hint)
//    Unweighted: sort by finish time (Activity Selection)
//    Weighted: requires DP (Weighted Interval Scheduling)
// ============================================================
int maxNonOverlapping(vector<pair<int, int>>& intervals) {
    sort(intervals.begin(), intervals.end(),
         [](const auto& a, const auto& b) { return a.second < b.second; });

    int count = 0, lastEnd = -1;
    for (auto& [start, end] : intervals) {
        if (start >= lastEnd) { count++; lastEnd = end; }
    }
    return count;
}

// ============================================================
// MAIN: Demonstrate all classic greedy algorithms
// ============================================================
int main() {
    cout << "=== CLASSIC GREEDY ALGORITHMS ===\n\n";

    // --- Activity Selection ---
    cout << "--- Activity Selection ---\n";
    vector<Activity> acts = {
        {1, 1, 3}, {2, 2, 5}, {3, 4, 6}, {4, 6, 8},
        {5, 5, 7}, {6, 8, 9}
    };
    auto selected = activitySelection(acts);
    cout << "Selected: ";
    for (int id : selected) cout << id << " ";
    cout << "(" << selected.size() << " activities)\n\n";

    // --- Fractional Knapsack ---
    cout << "--- Fractional Knapsack (capacity=50) ---\n";
    vector<Item> items = {{1, 10, 60}, {2, 20, 100}, {3, 30, 120}};
    cout << "Total value: " << fractionalKnapsack(items, 50) << "\n\n";

    // --- Huffman Coding ---
    cout << "--- Huffman Coding ---\n";
    vector<pair<char, int>> freq = {{'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}};
    cout << "Frequencies: a=5, b=9, c=12, d=13, e=16, f=45\n";
    huffmanCoding(freq);
    cout << "\n";

    // --- Job Sequencing ---
    cout << "--- Job Sequencing with Deadlines ---\n";
    vector<Job> jobs = {{1, 2, 100}, {2, 1, 19}, {3, 2, 27}, {4, 1, 25}, {5, 3, 15}};
    auto [jobCount, jobProfit] = jobSequencing(jobs);
    cout << "Jobs completed: " << jobCount << ", Max profit: " << jobProfit << "\n";  // 3, 142\n\n";

    // --- Minimum Coins ---
    cout << "--- Minimum Coins (US system: 1, 5, 10, 25) ---\n";
    vector<int> usCoins = {1, 5, 10, 25};
    auto coins = minCoinsGreedy(usCoins, 63);
    cout << "Coins for 63 cents: ";
    for (auto& [c, cnt] : coins) cout << cnt << "x" << c << " ";
    cout << "\n\n";

    // --- Interval Merging ---
    cout << "--- Interval Merging ---\n";
    vector<Interval> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}, {5, 7}};
    cout << "Input: ";
    for (auto& iv : intervals) cout << iv.toString() << " ";
    cout << "\n";
    auto merged = mergeIntervals(intervals);
    cout << "Merged: ";
    for (auto& iv : merged) cout << iv.toString() << " ";
    cout << "\n\n";

    // --- Non-Overlapping Intervals ---
    cout << "--- Max Non-Overlapping Intervals ---\n";
    vector<pair<int, int>> ivs = {{1, 3}, {2, 4}, {3, 5}, {6, 8}, {5, 7}};
    cout << "Max non-overlapping: " << maxNonOverlapping(ivs) << "\n";  // 3\n\n";

    // --- Summary ---
    cout << "--- Classic Greedy Summary ---\n";
    cout << "Activity Selection:    Sort by finish time, O(n log n)\n";
    cout << "Fractional Knapsack:   Sort by value/weight, O(n log n)\n";
    cout << "Huffman Coding:        Merge two smallest, O(n log n)\n";
    cout << "Job Sequencing:        Sort by profit, fill slots, O(n^2)\n";
    cout << "Min Coins (canonical): Sort descending, take most, O(n log n)\n";
    cout << "Interval Merging:      Sort by start, merge overlaps, O(n log n)\n";

    return 0;
}
