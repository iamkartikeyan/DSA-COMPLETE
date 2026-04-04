/*
 * Job Sequencing with Deadlines
 *
 * Given n jobs, each with a deadline and a profit.
 * Each job takes 1 unit of time.
 * Only one job can be done at a time.
 *
 * Goal: Maximize total profit.
 *
 * Greedy Strategy:
 *   1. Sort jobs by profit in descending order.
 *   2. For each job (highest profit first), assign it to the
 *      latest available time slot before its deadline.
 *   3. If no slot is available before deadline, skip the job.
 *
 * Time  : O(n^2)  with array-based slot assignment
 * Space : O(n)    for the slot array
 *
 * Why greedy works:
 *   By placing high-profit jobs in the latest possible slot,
 *   we leave earlier slots open for other jobs that might
 *   have tighter deadlines. This maximizes our options.
 */

#include <iostream>

struct Job {
    int id;
    int deadline;
    int profit;
};

/* Swap two jobs */
void swapJobs(Job &a, Job &b) {
    Job temp = a;
    a = b;
    b = temp;
}

/* Sort jobs by profit descending */
void sortByProfitDesc(Job arr[], int n) {
    int i = 0;
    while (i < n) {
        int j = 0;
        while (j < n - i - 1) {
            if (arr[j].profit < arr[j + 1].profit) {
                swapJobs(arr[j], arr[j + 1]);
            }
            j = j + 1;
        }
        i = i + 1;
    }
}

int jobSequencing(Job jobs[], int n, int schedule[]) {
    /* Step 1: Sort by profit descending */
    sortByProfitDesc(jobs, n);

    /* Step 2: Find maximum deadline to size our slot array */
    int maxDeadline = 0;
    int i = 0;
    while (i < n) {
        if (jobs[i].deadline > maxDeadline) {
            maxDeadline = jobs[i].deadline;
        }
        i = i + 1;
    }

    /* Step 3: Track which time slots are filled */
    int slot[100];  /* slot[t] = job ID assigned to time t, 0 = free */
    i = 0;
    while (i <= maxDeadline) {
        slot[i] = 0;
        i = i + 1;
    }

    /* Step 4: Assign each job to latest free slot before deadline */
    int totalProfit = 0;
    int jobsDone = 0;

    i = 0;
    while (i < n) {
        /* Try slots from deadline down to 1 */
        int t = jobs[i].deadline;
        while (t > 0) {
            if (slot[t] == 0) {
                slot[t] = jobs[i].id;
                totalProfit = totalProfit + jobs[i].profit;
                jobsDone = jobsDone + 1;
                break;
            }
            t = t - 1;
        }
        i = i + 1;
    }

    /* Build schedule array for caller */
    int s = 0;
    while (s <= maxDeadline) {
        schedule[s] = slot[s];
        s = s + 1;
    }

    return totalProfit;
}

int main() {
    int n = 7;
    Job jobs[7];
    jobs[0].id = 1; jobs[0].deadline = 2; jobs[0].profit = 100;
    jobs[1].id = 2; jobs[1].deadline = 1; jobs[1].profit = 19;
    jobs[2].id = 3; jobs[2].deadline = 2; jobs[2].profit = 27;
    jobs[3].id = 4; jobs[3].deadline = 1; jobs[3].profit = 25;
    jobs[4].id = 5; jobs[4].deadline = 3; jobs[4].profit = 15;
    jobs[5].id = 6; jobs[5].deadline = 3; jobs[5].profit = 40;
    jobs[6].id = 7; jobs[6].deadline = 4; jobs[6].profit = 55;

    std::cout << "=== Job Sequencing with Deadlines ===" << std::endl;
    std::cout << std::endl;
    std::cout << "Jobs:" << std::endl;

    int i = 0;
    while (i < n) {
        std::cout << "  Job " << jobs[i].id
                  << ": deadline=" << jobs[i].deadline
                  << ", profit=" << jobs[i].profit << std::endl;
        i = i + 1;
    }

    std::cout << std::endl;

    int schedule[100];
    int maxProfit = jobSequencing(jobs, n, schedule);

    std::cout << "Jobs sorted by profit (descending):" << std::endl;
    i = 0;
    while (i < n) {
        std::cout << "  Job " << jobs[i].id << " (profit=" << jobs[i].profit << ")" << std::endl;
        i = i + 1;
    }

    std::cout << std::endl;
    std::cout << "Schedule:" << std::endl;
    int maxDeadline = 0;
    i = 0;
    while (i < n) {
        if (jobs[i].deadline > maxDeadline) {
            maxDeadline = jobs[i].deadline;
        }
        i = i + 1;
    }

    i = 1;
    while (i <= maxDeadline) {
        if (schedule[i] > 0) {
            std::cout << "  Time slot " << i << ": Job " << schedule[i] << std::endl;
        } else {
            std::cout << "  Time slot " << i << ": (empty)" << std::endl;
        }
        i = i + 1;
    }

    std::cout << std::endl;
    std::cout << "Maximum profit: " << maxProfit << std::endl;

    std::cout << std::endl;
    std::cout << "Why greedy works:" << std::endl;
    std::cout << "  By picking highest-profit jobs first and placing them" << std::endl;
    std::cout << "  in the latest available slot before their deadline," << std::endl;
    std::cout << "  we leave earlier slots free for jobs with tighter" << std::endl;
    std::cout << "  deadlines. This maximizes total profit." << std::endl;

    return 0;
}
