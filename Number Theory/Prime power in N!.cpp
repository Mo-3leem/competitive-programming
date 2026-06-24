// O(Log p(n))

ll count_p_in_nfact(ll p, ll n) {
    ll res = 0;
    for (ll q = p; q <= n; ) {
        res += n / q;
        if (q > n / p) break; // prevent overflow
        q *= p;
    }
    return res;
}
