#pragma once
#include <vector>
#include <map>
#include <numeric>
#include <cmath>
#include <algorithm>

using namespace std;

long long MOD = 1e9 + 7;

// --- BASIC MODULAR ARITHMETIC ---

inline long long mod_add(long long a, long long b) { return (a + b) % MOD; }
inline long long mod_sub(long long a, long long b) { return (a - b + MOD) % MOD; }
inline long long mod_mul(long long a, long long b) { return (a * b) % MOD; }

// --- ADVANCED NUMBER THEORY ---

// 1. GCD & LCM
inline long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

inline long long lcm(long long a, long long b) {
    return (a / gcd(a, b)) * b;
}

// 2. Modular Exponentiation (a^b % m)
inline long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = mod_mul(res, base);
        base = mod_mul(base, base);
        exp /= 2;
    }
    return res;
}

inline long long modInverse(long long n) {
    return power(n, MOD - 2);
}

// 3. Combinatorics (nCr and nPr)
inline long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n / 2) r = n - r;
    
    long long res = 1;
    for (int i = 0; i < r; ++i) {
        res = mod_mul(res, (n - i));
        res = mod_mul(res, modInverse(i + 1));
    }
    return res;
}

inline long long nPr(int n, int r) {
    if (r < 0 || r > n) return 0;
    long long res = 1;
    for (int i = 0; i < r; i++) {
        res = mod_mul(res, (n - i));
    }
    return res;
}

// 4. Euler's Totient Function (phi)
// Counts numbers <= n that are coprime to n. O(sqrt(n))
inline long long euler_phi(long long n) {
    long long result = n;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

// 5. Prime Factorization
// Returns a map: {prime -> exponent}. Ex: 12 -> {2:2, 3:1}
inline map<long long, int> prime_factors(long long n) {
    map<long long, int> factors;
    for (long long i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            factors[i]++;
            n /= i;
        }
    }
    if (n > 1) factors[n]++;
    return factors;
}

// 6. Sieve of Eratosthenes (Primes up to N)
inline vector<int> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= n; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= n; i += p)
                is_prime[i] = false;
        }
    }
    vector<int> primes;
    for (int p = 2; p <= n; p++) {
        if (is_prime[p]) primes.push_back(p);
    }
    return primes;
}