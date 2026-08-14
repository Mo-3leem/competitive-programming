std::vector<int> getDivisors(int n) {
    std::vector<int> divisors;
    
    // Loop up to the square root of n
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            divisors.push_back(i); // First divisor
            
            // Avoid adding the square root twice (e.g., 6*6 = 36)
            if (i * i != n) {
                divisors.push_back(n / i); // Paired divisor
            }
        }
    }
    
    // Optional: Sort divisors in ascending order
    std::sort(divisors.begin(), divisors.end());
    
    return divisors;
}
