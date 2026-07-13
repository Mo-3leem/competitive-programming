//==============================================================//
// Count exponent of prime p in n! (Legendre's Formula)
//--------------------------------------------------------------//
// Time:  O(log_p(n))
// Space: O(1)
//
// Returns the exponent of prime p in the prime factorization of n!
//
// Example:
//   countPrimeInFact(2, 10) = 8
//   because 10! = 2^8 * ...
//
// Applications:
// • Number of trailing zeros in n!.
// • nCr / nPr prime factorization.
// • Divisibility of n! by x.
//==============================================================//

ll countPrimeInFact(ll p, ll n) {
    ll res = 0;

    for (ll pw = p; pw <= n; ) {
        res += n / pw;

        if (pw > n / p) break; // Prevent overflow
        pw *= p;
    }

    return res;
}
