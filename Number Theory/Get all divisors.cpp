// Get all divisors of n
// Time: O(sqrt(n))
// Space: O(number of divisors)

vector<long long> getDivisors(long long n) {
    vector<long long> divisors;

    for (long long i = 1; i <= n / i; i++) {
        if (n % i == 0) {
            divisors.push_back(i);

            if (i != n / i)
                divisors.push_back(n / i);
        }
    }

    sort(divisors.begin(), divisors.end()); // Remove if order doesn't matter
    return divisors;
}
