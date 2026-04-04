/*
 * Assign Cookies (Maximize Content Children)
 *
 * You have g children, each with a "greed factor" (minimum cookie
 * size they will accept). You have s cookies, each with a size.
 *
 * Each child can receive at most one cookie.
 * A cookie of size j satisfies a child with greed factor g if j >= g.
 *
 * Goal: Maximize the number of satisfied (content) children.
 *
 * Greedy Strategy:
 *   1. Sort children by greed factor (ascending).
 *   2. Sort cookies by size (ascending).
 *   3. For each child (least greedy first), give the smallest
 *      cookie that satisfies them.
 *   4. If a cookie is too small, skip it (try the next bigger one).
 *
 * Time  : O(g log g + s log s)  for sorting
 * Space : O(1)                  beyond input storage
 *
 * Why greedy works:
 *   By satisfying the least greedy child first with the smallest
 *   possible cookie, we save larger cookies for more greedy children.
 *   Wasting a large cookie on a child with small greed factor is
 *   suboptimal - that large cookie might be needed for a greedier child.
 */

#include <iostream>

/* Swap two integers */
void swapInt(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

/* Sort array ascending */
void sortArray(int arr[], int n) {
    int i = 0;
    while (i < n) {
        int j = 0;
        while (j < n - i - 1) {
            if (arr[j] > arr[j + 1]) {
                swapInt(arr[j], arr[j + 1]);
            }
            j = j + 1;
        }
        i = i + 1;
    }
}

int assignCookies(int greed[], int g, int cookies[], int s) {
    /* Step 1: Sort both arrays */
    sortArray(greed, g);
    sortArray(cookies, s);

    /* Step 2: Two-pointer greedy assignment */
    int childIdx = 0;   /* current child being considered */
    int cookieIdx = 0;  /* current cookie being considered */
    int content = 0;

    while (childIdx < g && cookieIdx < s) {
        if (cookies[cookieIdx] >= greed[childIdx]) {
            /* This cookie satisfies this child */
            content = content + 1;
            childIdx = childIdx + 1;
            cookieIdx = cookieIdx + 1;
        } else {
            /* Cookie too small, try next bigger one */
            cookieIdx = cookieIdx + 1;
        }
    }

    return content;
}

int main() {
    int g = 5;
    int greed[5] = {1, 2, 2, 3, 4};
    int s = 5;
    int cookies[5] = {3, 1, 2, 3, 2};

    std::cout << "=== Assign Cookies ===" << std::endl;
    std::cout << std::endl;
    std::cout << "Children greed factors: ";
    int i = 0;
    while (i < g) {
        std::cout << greed[i];
        if (i < g - 1) std::cout << ", ";
        i = i + 1;
    }
    std::cout << std::endl;

    std::cout << "Cookie sizes: ";
    i = 0;
    while (i < s) {
        std::cout << cookies[i];
        if (i < s - 1) std::cout << ", ";
        i = i + 1;
    }
    std::cout << std::endl;

    std::cout << std::endl;

    /* Show the greedy process */
    /* Make copies to show sorted order */
    int sortedGreed[5] = {1, 2, 2, 3, 4};
    int sortedCookies[5] = {1, 2, 2, 3, 3};

    std::cout << "After sorting:" << std::endl;
    std::cout << "  Children: ";
    i = 0;
    while (i < g) {
        std::cout << sortedGreed[i];
        if (i < g - 1) std::cout << ", ";
        i = i + 1;
    }
    std::cout << std::endl;

    std::cout << "  Cookies:  ";
    i = 0;
    while (i < s) {
        std::cout << sortedCookies[i];
        if (i < s - 1) std::cout << ", ";
        i = i + 1;
    }
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "Greedy assignment (least greedy child first):" << std::endl;

    int childIdx = 0;
    int cookieIdx = 0;
    int content = 0;

    while (childIdx < g && cookieIdx < s) {
        if (sortedCookies[cookieIdx] >= sortedGreed[childIdx]) {
            std::cout << "  Child (greed=" << sortedGreed[childIdx] << ")"
                      << " gets cookie (size=" << sortedCookies[cookieIdx] << ")"
                      << " -> SATISFIED" << std::endl;
            content = content + 1;
            childIdx = childIdx + 1;
            cookieIdx = cookieIdx + 1;
        } else {
            std::cout << "  Cookie (size=" << sortedCookies[cookieIdx] << ")"
                      << " too small for child (greed=" << sortedGreed[childIdx] << ")"
                      << " -> skip cookie" << std::endl;
            cookieIdx = cookieIdx + 1;
        }
    }

    int result = assignCookies(greed, g, cookies, s);

    std::cout << std::endl;
    std::cout << "Maximum content children: " << result << std::endl;

    std::cout << std::endl;
    std::cout << "Why greedy works:" << std::endl;
    std::cout << "  By satisfying the least greedy child with the" << std::endl;
    std::cout << "  smallest possible cookie, we save bigger cookies" << std::endl;
    std::cout << "  for greedier children. Using a bigger cookie than" << std::endl;
    std::cout << "  needed wastes it and might leave a greedier child" << std::endl;
    std::cout << "  unsatisfied." << std::endl;

    return 0;
}
