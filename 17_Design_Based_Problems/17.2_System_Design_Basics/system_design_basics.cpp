#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <random>
using namespace std;

// ===== RATE LIMITER =====
// Concept: Limit number of requests per time window

// 1. Fixed Window Counter
class FixedWindowRateLimiter {
    unordered_map<string, pair<int, int>> counters;  // key -> {count, windowStart}
    int limit, windowMs;
public:
    FixedWindowRateLimiter(int l, int w) : limit(l), windowMs(w) {}

    bool allow(string key, int timestamp) {
        auto &p = counters[key];
        if (timestamp - p.second >= windowMs) {
            p = {1, timestamp};  // Reset window
            return true;
        }
        if (p.first < limit) { p.first++; return true; }
        return false;
    }
};

// 2. Sliding Window Log
class SlidingWindowRateLimiter {
    unordered_map<string, vector<int>> logs;
    int limit, windowMs;
public:
    SlidingWindowRateLimiter(int l, int w) : limit(l), windowMs(w) {}

    bool allow(string key, int timestamp) {
        auto &log = logs[key];
        // Remove expired entries
        while (!log.empty() && log.front() <= timestamp - windowMs)
            log.erase(log.begin());
        if (log.size() < limit) {
            log.push_back(timestamp);
            return true;
        }
        return false;
    }
};

// 3. Token Bucket
class TokenBucket {
    double tokens, maxTokens, refillRate;
    int lastRefillTime;
public:
    TokenBucket(double maxT, double rate) : maxTokens(maxT), tokens(maxT), refillRate(rate), lastRefillTime(0) {}

    bool allow(int timestamp) {
        // Refill tokens
        double elapsed = timestamp - lastRefillTime;
        tokens = min(maxTokens, tokens + elapsed * refillRate);
        lastRefillTime = timestamp;

        if (tokens >= 1) { tokens--; return true; }
        return false;
    }
};

// ===== URL SHORTENER (Conceptual) =====
class URLShortener {
    unordered_map<string, string> shortToLong;
    unordered_map<string, string> longToShort;
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string baseUrl = "http://tinyurl.com/";
    mt19937 rng;

    string generateShort() {
        string key;
        for (int i = 0; i < 6; i++) key += chars[rng() % chars.size()];
        return key;
    }
public:
    URLShortener() : rng(random_device{}()) {}

    string encode(string longUrl) {
        if (longToShort.count(longUrl)) return baseUrl + longToShort[longUrl];
        string key;
        do { key = generateShort(); } while (shortToLong.count(key));
        shortToLong[key] = longUrl;
        longToShort[longUrl] = key;
        return baseUrl + key;
    }

    string decode(string shortUrl) {
        string key = shortUrl.substr(shortUrl.find_last_of('/') + 1);
        return shortToLong.count(key) ? shortToLong[key] : "";
    }
};

// ===== KEY-VALUE STORE (Conceptual) =====
class KVStore {
    unordered_map<string, string> data;
    unordered_map<string, vector<pair<int, string>>> history;  // key -> [(timestamp, val)]
public:
    void put(string key, string value) { data[key] = value; }
    string get(string key) { return data.count(key) ? data[key] : ""; }
    bool remove(string key) { return data.erase(key); }

    // Versioned KV Store
    void putAt(string key, int timestamp, string value) {
        history[key].push_back({timestamp, value});
    }

    string getAt(string key, int timestamp) {
        if (!history.count(key)) return "";
        auto &versions = history[key];
        // Binary search for largest timestamp <= given
        int l = 0, r = versions.size() - 1, result = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (versions[mid].first <= timestamp) { result = mid; l = mid + 1; }
            else r = mid - 1;
        }
        return result != -1 ? versions[result].second : "";
    }
};

int main() {
    // Rate Limiter
    cout << "=== Fixed Window Rate Limiter ===\n";
    FixedWindowRateLimiter fwr(3, 1000);
    cout << "t=0: " << fwr.allow("user1", 0) << "\n";    // true
    cout << "t=500: " << fwr.allow("user1", 500) << "\n"; // true
    cout << "t=800: " << fwr.allow("user1", 800) << "\n"; // true
    cout << "t=900: " << fwr.allow("user1", 900) << "\n"; // false (limit reached)

    cout << "\n=== Token Bucket ===\n";
    TokenBucket tb(5, 0.01);  // 5 tokens, refill 0.01/ms
    for (int i = 0; i < 7; i++)
        cout << "Request " << i << ": " << tb.allow(i * 10) << "\n";

    // URL Shortener
    cout << "\n=== URL Shortener ===\n";
    URLShortener url;
    string short1 = url.encode("https://www.example.com/very/long/url");
    cout << "Short: " << short1 << "\n";
    cout << "Long: " << url.decode(short1) << "\n";

    // KV Store
    cout << "\n=== Key-Value Store ===\n";
    KVStore kv;
    kv.put("name", "Alice");
    cout << "get(name): " << kv.get("name") << "\n";

    kv.putAt("key", 1, "v1");
    kv.putAt("key", 3, "v3");
    kv.putAt("key", 5, "v5");
    cout << "getAt(key, t=4): " << kv.getAt("key", 4) << "\n";  // v3
    cout << "getAt(key, t=6): " << kv.getAt("key", 6) << "\n";  // v5

    return 0;
}
