// Sum of first n natural numbers
long long sumAll(long long n) {
    return n * (n + 1) / 2;
}

// Sum of even numbers from 1 to n
// Example: n = 10 -> 2 + 4 + 6 + 8 + 10 = 30
long long sumEven(long long n) {
    long long cnt = n / 2;
    return cnt * (cnt + 1);
}

// Sum of odd numbers from 1 to n
// Example: n = 10 -> 1 + 3 + 5 + 7 + 9 = 25
long long sumOdd(long long n) {
    long long cnt = (n + 1) / 2;
    return cnt * cnt;
}

// Sum of even numbers in [L, R]
long long sumEven(long long L, long long R) {
    return sumEven(R) - sumEven(L - 1);
}

// Sum of odd numbers in [L, R]
long long sumOdd(long long L, long long R) {
    return sumOdd(R) - sumOdd(L - 1);
}
