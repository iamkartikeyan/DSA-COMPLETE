/*
 * Fractional Knapsack Problem
 *
 * Given n items with weights and values, and a knapsack of
 * capacity W. We can take FRACTIONS of items (unlike 0/1 knapsack).
 *
 * Goal: Maximize total value within capacity W.
 *
 * Greedy Strategy:
 *   1. Compute value/weight ratio for each item.
 *   2. Sort by ratio descending.
 *   3. Fill knapsack greedily: take full items with highest
 *      ratio first. If capacity runs out, take a fraction
 *      of the next best item.
 *
 * Time  : O(n log n)  for sorting
 * Space : O(1)        beyond input storage
 *
 * Why greedy works here (but NOT for 0/1 Knapsack):
 *   Because we can take fractions, there is no "wasted space"
 *   dilemma. We always fill the knapsack optimally by taking
 *   the most value-dense items first.
 *
 *   In 0/1 Knapsack, taking the highest-ratio item might
 *   prevent us from taking a combination of items that would
 *   yield more total value. Greedy fails because choices
 *   are discrete (all or nothing).
 */

#include <iostream>

struct Item {
    int id;
    int weight;
    int value;
    double ratio;  /* value / weight */
};

/* Swap two items */
void swapItems(Item &a, Item &b) {
    Item temp = a;
    a = b;
    b = temp;
}

/* Sort items by value/weight ratio descending */
void sortByRatioDesc(Item arr[], int n) {
    int i = 0;
    while (i < n) {
        int j = 0;
        while (j < n - i - 1) {
            if (arr[j].ratio < arr[j + 1].ratio) {
                swapItems(arr[j], arr[j + 1]);
            }
            j = j + 1;
        }
        i = i + 1;
    }
}

double fractionalKnapsack(Item items[], int n, int capacity) {
    /* Compute ratios */
    int i = 0;
    while (i < n) {
        items[i].ratio = (double)items[i].value / items[i].weight;
        i = i + 1;
    }

    /* Sort by ratio descending */
    sortByRatioDesc(items, n);

    double totalValue = 0;
    int remaining = capacity;

    i = 0;
    while (i < n) {
        if (remaining >= items[i].weight) {
            /* Take the full item */
            totalValue = totalValue + items[i].value;
            remaining = remaining - items[i].weight;
            std::cout << "  Take item " << items[i].id
                      << " fully (w=" << items[i].weight
                      << ", v=" << items[i].value
                      << ", ratio=" << items[i].ratio
                      << ")" << std::endl;
        } else {
            /* Take a fraction of this item */
            double fraction = (double)remaining / items[i].weight;
            double contribution = items[i].value * fraction;
            totalValue = totalValue + contribution;
            remaining = 0;
            std::cout << "  Take item " << items[i].id
                      << " fraction " << (int)(fraction * 100) << "%"
                      << " (v=" << contribution << ")" << std::endl;
            break;
        }
        i = i + 1;
    }

    return totalValue;
}

int main() {
    int n = 5;
    Item items[5];
    items[0].id = 1; items[0].weight = 10; items[0].value = 60;
    items[1].id = 2; items[1].weight = 20; items[1].value = 100;
    items[2].id = 3; items[2].weight = 30; items[2].value = 120;
    items[3].id = 4; items[3].weight = 5;  items[3].value = 50;
    items[4].id = 5; items[4].weight = 15; items[4].value = 45;

    int capacity = 50;

    std::cout << "=== Fractional Knapsack ===" << std::endl;
    std::cout << std::endl;
    std::cout << "Items:" << std::endl;

    int i = 0;
    while (i < n) {
        double r = (double)items[i].value / items[i].weight;
        std::cout << "  Item " << items[i].id
                  << ": weight=" << items[i].weight
                  << ", value=" << items[i].value
                  << ", ratio=" << r << std::endl;
        i = i + 1;
    }

    std::cout << std::endl;
    std::cout << "Knapsack capacity: " << capacity << std::endl;
    std::cout << std::endl;
    std::cout << "Greedy selection (by value/weight ratio):" << std::endl;

    double maxValue = fractionalKnapsack(items, n, capacity);

    std::cout << std::endl;
    std::cout << "Maximum total value: " << maxValue << std::endl;

    std::cout << std::endl;
    std::cout << "Why greedy works for Fractional Knapsack:" << std::endl;
    std::cout << "  We can take FRACTIONS of items." << std::endl;
    std::cout << "  No wasted space: always fill to capacity." << std::endl;
    std::cout << "  Highest value-per-weight items contribute most." << std::endl;
    std::cout << std::endl;
    std::cout << "Why greedy FAILS for 0/1 Knapsack:" << std::endl;
    std::cout << "  We CANNOT take fractions (all or nothing)." << std::endl;
    std::cout << "  A high-ratio heavy item might block several" << std::endl;
    std::cout << "  medium-ratio items whose combined value is higher." << std::endl;
    std::cout << "  Only DP can explore all combinations." << std::endl;

    return 0;
}
