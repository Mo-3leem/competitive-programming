```cpp
// ============================================================
// PRIME FACTORIZATION METHODS
//
// max(ai) <= 1e7
//      -> SPF (Many queries)
//
// max(ai) <= 1e12
//      -> Trial Division (Few queries)
//
// max(ai) <= 1e18
//      -> Pollard's Rho + Miller-Rabin
//
// Return format:
//      map<prime, exponent>
// ============================================================


// ============================================================
// 1) Smallest Prime Factor (SPF)
//
// Use:
//     • Many queries.
//     • max(ai) <= 1e7.
//     • Need prime factorization frequently.
//
// Preprocessing:
//     O(N log log N)
//
// Factorization:
//     O(log ai)
//
// Space:
//     O(N)
//
// Usage:
//     buildSPF();
//     auto pf = primeFactorizationSPF(x);
// ============================================================



// ============================================================
// 2) Trial Division
//
// Use:
//     • One or a few queries.
//     • max(ai) <= 1e12.
//     • No preprocessing.
//
// Complexity:
//     O(sqrt(ai))
//
// Space:
//     O(1)
//
// Usage:
//     auto pf = primeFactorizationTrial(x);
// ============================================================



// ============================================================
// 3) Pollard's Rho + Miller-Rabin
//
// Use:
//     • max(ai) <= 1e18.
//     • Large numbers.
//     • Standard ICPC / ECPC solution.
//
// Miller-Rabin:
//     O(log^3 ai)
//
// Factorization:
//     ~O(ai^(1/4)) average.
//
// Space:
//     O(log ai)
//
// Usage:
//     auto pf = primeFactorization(x);
// ============================================================
```

---

## 1) SPF (Smallest Prime Factor)

```cpp
const int N = 1e7 + 5;
int spf[N];

// Build: O(N log log N)
void buildSPF() {
    iota(spf, spf + N, 0);

    for (int i = 2; i * i < N; i++)
        if (spf[i] == i)
            for (int j = i * i; j < N; j += i)
                if (spf[j] == j)
                    spf[j] = i;
}

// return {{prime, exponent}, ...}
// Time: O(log x)
map<int,int> primeFactorizationSPF(int x) {
    map<int,int> pf;

    while (x > 1) {
        pf[spf[x]]++;
        x /= spf[x];
    }

    return pf;
}
```

---

## 2) Trial Division

```cpp
// return {{prime, exponent}, ...}
// Time: O(sqrt(x))
// Space: O(1)

map<long long,int> primeFactorizationTrial(long long x) {

    map<long long,int> pf;

    for (long long p = 2; p * p <= x; p++) {

        while (x % p == 0) {
            pf[p]++;
            x /= p;
        }
    }

    if (x > 1)
        pf[x]++;

    return pf;
}
```

---
```cpp

```cpp

// ============================================================
## 3) Pollard's Rho + Miller-Rabin

using ull = unsigned long long;
using u128 = __uint128_t;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// (a * b) % mod
ull mulMod(ull a, ull b, ull mod) {
    return (u128)a * b % mod;
}

// (a^b) % mod
ull powerMod(ull a, ull b, ull mod) {
    ull res = 1;

    while (b) {
        if (b & 1)
            res = mulMod(res, a, mod);

        a = mulMod(a, a, mod);
        b >>= 1;
    }

    return res;
}

// Deterministic Miller-Rabin
bool isPrime(ull n) {

    if (n < 2)
        return false;

    for (ull p : {2,3,5,7,11,13,17,19,23,29,31,37})
        if (n % p == 0)
            return n == p;

    ull d = n - 1;
    int s = 0;

    while (!(d & 1))
        d >>= 1, s++;

    for (ull a : {
            2ULL,
            325ULL,
            9375ULL,
            28178ULL,
            450775ULL,
            9780504ULL,
            1795265022ULL
        }) {

        if (a % n == 0)
            continue;

        ull x = powerMod(a % n, d, n);

        if (x == 1 || x == n - 1)
            continue;

        bool composite = true;

        for (int r = 1; r < s; r++) {
            x = mulMod(x, x, n);

            if (x == n - 1) {
                composite = false;
                break;
            }
        }

        if (composite)
            return false;
    }

    return true;
}

// f(x) = x² + c (mod n)
ull f(ull x, ull c, ull mod) {
    return (mulMod(x, x, mod) + c) % mod;
}

// Returns any non-trivial divisor.
ull pollardRho(ull n) {

    if (n % 2 == 0)
        return 2;

    if (n % 3 == 0)
        return 3;

    while (true) {

        ull c = uniform_int_distribution<ull>(1, n - 1)(rng);
        ull x = uniform_int_distribution<ull>(0, n - 1)(rng);
        ull y = x;
        ull d = 1;

        while (d == 1) {

            x = f(x, c, n);
            y = f(f(y, c, n), c, n);

            d = gcd(x > y ? x - y : y - x, n);
        }

        if (d != n)
            return d;
    }
}

// Stores all prime factors.
void factor(ull n, vector<ull>& factors) {

    if (n == 1)
        return;

    if (isPrime(n)) {
        factors.push_back(n);
        return;
    }

    ull d = pollardRho(n);

    factor(d, factors);
    factor(n / d, factors);
}

// return {{prime, exponent}, ...}
map<ull,int> primeFactorization(ull x) {

    vector<ull> factors;
    factor(x, factors);

    map<ull,int> pf;

    for (ull p : factors)
        pf[p]++;

    return pf;
}
```
