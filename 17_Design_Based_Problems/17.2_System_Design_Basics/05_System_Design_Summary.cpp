// 17.2.05 - System Design Summary
// Complete summary of system design concepts: scalability,
// load balancing, caching, CAP theorem, databases.

#include <iostream>

using namespace std;

// ---- Rate Limiter (Fixed Window) ----
class FixedWindowRateLimiter {
private:
    int limit;
    int windowMs;
    int count;
    int windowStart;

public:
    FixedWindowRateLimiter(int l, int w) {
        limit = l;
        windowMs = w;
        count = 0;
        windowStart = 0;
    }

    bool allow(int timestamp) {
        if (timestamp - windowStart >= windowMs) {
            count = 0;
            windowStart = timestamp;
        }
        if (count < limit) {
            count++;
            return true;
        }
        return false;
    }
};

// ---- Token Bucket ----
class TokenBucket {
private:
    double tokens;
    double maxTokens;
    double refillRate;
    int lastRefillTime;

public:
    TokenBucket(double maxT, double rate) {
        maxTokens = maxT;
        tokens = maxT;
        refillRate = rate;
        lastRefillTime = 0;
    }

    bool allow(int timestamp) {
        double elapsed = timestamp - lastRefillTime;
        tokens = (tokens + elapsed * refillRate < maxTokens) ?
                 (tokens + elapsed * refillRate) : maxTokens;
        lastRefillTime = timestamp;
        if (tokens >= 1) {
            tokens -= 1;
            return true;
        }
        return false;
    }
};

// ---- URL Shortener (Simplified) ----
class URLShortener {
private:
    static const int MAX_ENTRIES = 100;
    int keys[MAX_ENTRIES];
    char shortCodes[MAX_ENTRIES][10];
    char longUrls[MAX_ENTRIES][200];
    int count;
    int nextId;

public:
    URLShortener() {
        count = 0;
        nextId = 1000;
        for (int i = 0; i < MAX_ENTRIES; i++) keys[i] = -1;
    }

    int encode(const char* longUrl, char* shortCode) {
        // Check if already encoded
        for (int i = 0; i < count; i++) {
            // Simple comparison (in real system, compare strings)
            if (keys[i] != -1) {
                // Already exists, reuse
                int j = 0;
                while (shortCodes[i][j] != '\0' && j < 9) {
                    shortCode[j] = shortCodes[i][j];
                    j++;
                }
                shortCode[j] = '\0';
                return keys[i];
            }
        }
        if (count >= MAX_ENTRIES) return -1;

        int id = nextId++;
        keys[count] = id;
        int j = 0;
        while (longUrl[j] != '\0' && j < 199) {
            longUrls[count][j] = longUrl[j];
            j++;
        }
        longUrls[count][j] = '\0';

        // Generate short code from id
        int idx = 0;
        int temp = id;
        char chars[] = "abcdefghijklmnopqrstuvwxyz0123456789";
        for (int k = 0; k < 6 && k < 9; k++) {
            shortCodes[count][k] = chars[temp % 36];
            temp /= 36;
            idx++;
        }
        shortCodes[count][idx] = '\0';

        int m = 0;
        while (shortCodes[count][m] != '\0' && m < 9) {
            shortCode[m] = shortCodes[count][m];
            m++;
        }
        shortCode[m] = '\0';

        count++;
        return id;
    }
};

// ---- Key-Value Store ----
class KVStore {
private:
    static const int MAX_ENTRIES = 100;
    char keys[MAX_ENTRIES][50];
    char values[MAX_ENTRIES][200];
    int count;

public:
    KVStore() { count = 0; }

    void put(const char* key, const char* value) {
        // Check if key exists
        for (int i = 0; i < count; i++) {
            if (keys[i][0] == key[0]) {  // Simple first-char check
                int j = 0;
                while (keys[i][j] != '\0' && value[j] != '\0') {
                    values[i][j] = value[j];
                    j++;
                }
                values[i][j] = '\0';
                return;
            }
        }
        if (count < MAX_ENTRIES) {
            int j = 0;
            while (key[j] != '\0' && j < 49) {
                keys[count][j] = key[j];
                j++;
            }
            keys[count][j] = '\0';
            j = 0;
            while (value[j] != '\0' && j < 199) {
                values[count][j] = value[j];
                j++;
            }
            values[count][j] = '\0';
            count++;
        }
    }

    const char* get(const char* key) {
        for (int i = 0; i < count; i++) {
            if (keys[i][0] == key[0]) {
                return values[i];
            }
        }
        return "";
    }
};

int main() {
    cout << "========================================" << endl;
    cout << "  SYSTEM DESIGN - COMPLETE SUMMARY" << endl;
    cout << "========================================" << endl;

    // 1. Scalability
    cout << endl << "1. SCALABILITY" << endl;
    cout << "   Vertical (Scale Up): Add resources to single server" << endl;
    cout << "     - Simple, but has hardware limits" << endl;
    cout << "   Horizontal (Scale Out): Add more servers" << endl;
    cout << "     - Unlimited scale, but adds complexity" << endl;

    // 2. Load Balancing
    cout << endl << "2. LOAD BALANCING" << endl;
    cout << "   Round Robin: Cycle through servers (fair, simple)" << endl;
    cout << "   Least Connections: Send to least busy server" << endl;
    cout << "   Weighted RR: Proportional to server capacity" << endl;
    cout << "   IP Hash: Sticky sessions for cache affinity" << endl;

    // 3. Caching
    cout << endl << "3. CACHING STRATEGIES" << endl;
    cout << "   FIFO: Evict oldest (simple)" << endl;
    cout << "   LRU: Evict least recently used (temporal locality)" << endl;
    cout << "   LFU: Evict least frequently used (popularity-based)" << endl;

    // 4. Rate Limiting
    cout << endl << "4. RATE LIMITING" << endl;
    FixedWindowRateLimiter rl(3, 1000);
    cout << "   Fixed window (3 per 1000ms):" << endl;
    cout << "   t=0: " << (rl.allow(0) ? "allowed" : "denied") << endl;
    cout << "   t=500: " << (rl.allow(500) ? "allowed" : "denied") << endl;
    cout << "   t=900: " << (rl.allow(900) ? "allowed" : "denied") << endl;
    cout << "   t=999: " << (rl.allow(999) ? "allowed" : "denied") << endl;

    TokenBucket tb(5, 0.01);
    cout << endl << "   Token bucket (5 tokens, 0.01/ms refill):" << endl;
    for (int i = 0; i < 7; i++) {
        cout << "   Request " << i << " (t=" << i * 10 << "): "
             << (tb.allow(i * 10) ? "allowed" : "denied") << endl;
    }

    // 5. CAP Theorem
    cout << endl << "5. CAP THEOREM" << endl;
    cout << "   Consistency: Every read gets latest write" << endl;
    cout << "   Availability: Every request gets a response" << endl;
    cout << "   Partition Tolerance: Works despite network failures" << endl;
    cout << "   Choose CP (SQL) or AP (NoSQL)" << endl;

    // 6. Database Types
    cout << endl << "6. DATABASE TYPES" << endl;
    cout << "   SQL: Structured, ACID, vertical scaling" << endl;
    cout << "   NoSQL: Flexible schema, horizontal scaling" << endl;
    cout << "   Sharding: Split data across servers by key" << endl;

    cout << endl << "========================================" << endl;
    cout << "  KEY DESIGN PRINCIPLES" << endl;
    cout << "========================================" << endl;
    cout << "  1. Start simple, scale when needed" << endl;
    cout << "  2. Use caching to reduce DB load" << endl;
    cout << "  3. Load balance for horizontal scaling" << endl;
    cout << "  4. Rate limit to protect backend" << endl;
    cout << "  5. Choose DB based on consistency needs" << endl;
    cout << "  6. Monitor and iterate" << endl;

    return 0;
}
