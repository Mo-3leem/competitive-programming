using ll = long long;

// Modulo used in modular combinatorics
const int MOD = 1e9 + 7;

// Must be >= maximum n used in nCrMod / nPrMod
const int MAX = 2e6 + 5;

// Maximum n for Pascal Triangle
// WARNING: C[N][N] uses O(N^2) memory
const int NCR_MAX = 5000;


ll fact[MAX], invFact[MAX];
ll C[NCR_MAX + 1][NCR_MAX + 1];

//==================================================
// Fast Power
//==================================================

// Calculate (a^b) % mod
// Use: fastPower(a, b)
// Complexity: O(log b)
ll fastPower(ll a, ll b, ll mod = MOD) {
    ll res = 1;

    while (b) {
        if (b & 1)
            res = res * a % mod;

        a = a * a % mod;
        b >>= 1;
    }

    return res;
}

//==================================================
// Factorials
//==================================================

// Call this ONCE before using:
// nCrMod() or nPrMod()
//
// fact[i]    = i! % MOD
// invFact[i] = 1 / i! % MOD
//
// Complexity: O(MAX)
void initCombinatorics() {

    fact[0] = 1;

    for (int i = 1; i < MAX; i++)
        fact[i] = fact[i - 1] * i % MOD;

    invFact[MAX - 1] = fastPower(fact[MAX - 1], MOD - 2);

    for (int i = MAX - 2; i >= 0; i--)
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
}

//==================================================
// Pascal Triangle
//==================================================

// Call this ONCE before using nCrPrecomputed()
//
// C[n][r] = nCr
//
// Use only when NCR_MAX is small.
// Complexity: O(NCR_MAX^2)
void initNCR() {

    for (int i = 0; i <= NCR_MAX; i++) {

        C[i][0] = C[i][i] = 1;

        for (int j = 1; j < i; j++)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
}

//==================================================
// Without Mod
//==================================================

// Calculate nCr exactly
//
// Use when:
// - No modulo is needed
// - Answer fits in long long
//
// Complexity: O(r)
ll nCr(ll n, ll r) {

    if (r < 0 || r > n)
        return 0;

    r = min(r, n - r);

    ll ans = 1;

    for (ll i = 1; i <= r; i++)
        ans = ans * (n - r + i) / i;

    return ans;
}

//==================================================

// Calculate nCr using precomputed Pascal Triangle
//
// Must call initNCR() first.
//
// Works only when n <= NCR_MAX
//
// Complexity:
// Precomputation: O(N^2)
// Query: O(1)
ll nCrPrecomputed(int n, int r) {

    if (r < 0 || r > n || n > NCR_MAX)
        return 0;

    return C[n][r];
}

//==================================================

// Calculate nPr exactly
//
// nPr = n * (n-1) * ... * (n-r+1)
//
// Use when:
// - No modulo is needed
// - Answer fits in long long
//
// Complexity: O(r)
ll nPr(ll n, ll r) {

    if (r < 0 || r > n)
        return 0;

    ll ans = 1;

    while (r--)
        ans *= n--;

    return ans;
}

//==================================================
// With Mod
//==================================================

// Calculate nCr % MOD
//
// Must call initCombinatorics() first.
//
// Complexity: O(1)
ll nCrMod(int n, int r) {

    if (r < 0 || r > n)
        return 0;

    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

//==================================================

// Calculate nPr % MOD
//
// Must call initCombinatorics() first.
//
// Complexity: O(1)
ll nPrMod(int n, int r) {

    if (r < 0 || r > n)
        return 0;

    return fact[n] * invFact[n - r] % MOD;
}
