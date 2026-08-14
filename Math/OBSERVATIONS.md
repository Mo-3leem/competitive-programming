# ECPC QUICK MATH & OBSERVATIONS

## BITWISE IDENTITIES

```cpp
x + y = (x | y) + (x & y)
x + y = (x ^ y) + 2 * (x & y)

x | y = (x ^ y) + (x & y)
x ^ y = (x | y) - (x & y)
x ^ y = x + y - 2 * (x & y)

```

### No common bits

```cpp
(x & y) == 0
<=> x + y == (x ^ y)
<=> x + y == (x | y)
<=> (x ^ y) == (x | y)
```

### Submask / Supermask

```cpp
x is submask of y
<=> (x & y) == x
<=> (x | y) == y
```

### Bit Tricks

```cpp
check bit k       : x & (1LL << k)
set bit k         : x |= (1LL << k)
clear bit k       : x &= ~(1LL << k)
toggle bit k      : x ^= (1LL << k)

lowest set bit    : x & -x
remove lowest bit : x &= (x - 1)

power of two      : x > 0 && !(x & (x - 1))
popcount           : __builtin_popcountll(x)

all B bits         : (1LL << B) - 1
complement B bits  : x ^ ((1LL << B) - 1)
```

## GCD / LCM / DIVISIBILITY

```text
gcd(a,b) = gcd(b, a%b)
gcd(a,b) = gcd(a, b-a)
gcd(a,b) = gcd(a, b+k*a)

gcd(a,b) * lcm(a,b) = a*b
lcm(a,b) = a/gcd(a,b) * b

a|b and a|c => a|(b+c), a|(b-c)
```

Same remainder modulo `d`:

```text
a[i] ≡ a[j] (mod d)
<=> d | (a[i] - a[j])
```

Useful:

```text
gcd(a1-a0, a2-a0, ..., an-a0)
```

Adding elements:

```text
GCD can only lose prime factors
AND can only lose set bits
OR  can only gain set bits
```

---

## PRIME FACTORIZATION / DIVISORS

If

```text
n = p1^a1 * p2^a2 * ... * pk^ak
```

then

```text
#divisors(n) = (a1+1)(a2+1)...(ak+1)
```

Important:

```text
exactly 2 divisors <=> n is prime
exactly 3 divisors <=> n = p^2, p is prime

n is perfect square <=> floor(sqrt(n))^2 == n
```

Number of distinct prime factors:

```text
omega(n) = number of different primes dividing n
```

---

## SUMS / COUNTING

```text
1+2+...+n = n(n+1)/2

1+3+...+(2n-1) = n^2

1²+2²+...+n² = n(n+1)(2n+1)/6

Arithmetic Progression:
sum = n*(first+last)/2
    = n*(2a+(n-1)d)/2
```

Pairs:

```text
unordered pairs = C(n,2) = n(n-1)/2
ordered i != j  = n(n-1)

C(n,3) = n(n-1)(n-2)/6
```

---

## COMBINATORICS

```text
C(n,k) = n! / (k!(n-k)!)

C(n,k) = C(n,n-k)

C(n,k) = C(n-1,k) + C(n-1,k-1)
```

### Stars & Bars

```text
x1+...+xk = N, xi >= 1
=> C(N-1, k-1)

x1+...+xk = N, xi >= 0
=> C(N+k-1, k-1)
```

Split `N` identical objects into exactly `K` non-empty groups:

```text
C(N-1, K-1)
```

Put `M` separators/gaps around `K` blocks:
often transform mandatory elements first, then Stars & Bars.

---

## MODULAR ARITHMETIC

```cpp
(a+b)%MOD
(a-b+MOD)%MOD
(a*b)%MOD
```

Division:

```text
a/b mod MOD = a * inv(b) mod MOD
```

For prime `MOD`:

```text
inv(a) = a^(MOD-2) mod MOD
```

Fermat:

```text
a^(MOD-1) ≡ 1 (mod MOD), gcd(a,MOD)=1
```

Combinations:

```cpp
C(n,k) = fact[n] * invFact[k] % MOD
                   * invFact[n-k] % MOD;
```

---

## PREFIX / RANGE

### 1D

```text
pref[i] = pref[i-1] + a[i]

sum(l,r) = pref[r] - pref[l-1]
```

### 2D

```text
sum(x1,y1,x2,y2) =
 P[x2][y2]
-P[x1-1][y2]
-P[x2][y1-1]
+P[x1-1][y1-1]
```

### Difference Array

Range add `[l,r] += x`:

```cpp
diff[l] += x;
diff[r+1] -= x;
```

---

## TREES

```text
Tree:
edges = n-1
sum(deg[v]) = 2(n-1)
```

Euler Tour:

```text
subtree(u) <=> [tin[u], tout[u]]
```

So always think:

```text
SUBTREE QUERY -> ARRAY RANGE QUERY
```

Tree distance:

```text
dist(u,v) =
depth[u] + depth[v] - 2*depth[lca(u,v)]
```

Weighted:

```text
dist(u,v) =
D[u] + D[v] - 2*D[lca(u,v)]
```

---

## PROBABILITY / EXPECTATION

```text
E[X+Y] = E[X] + E[Y]
```

No independence required.

Indicator:

```text
I = 1 if event happens, else 0
E[I] = P(event)
```

Therefore:

```text
E[number of successful events]
= sum P(event_i)
```

Probability:

```text
P(A ∪ B) = P(A)+P(B)-P(A ∩ B)

P(A|B) = P(A∩B)/P(B)
```

---

## INCLUSION-EXCLUSION

```text
|A ∪ B|
= |A| + |B| - |A∩B|

|A ∪ B ∪ C|
= singles
- pair intersections
+ triple intersection
```

Mnemonic:

```text
+ singles
- pairs
+ triples
- quadruples ...
```

---

## CONSTRAINT -> FIRST THOUGHT

```text
n <= 20             -> Bitmask DP / 2^n
n <= 40             -> Meet in the Middle
n <= 5,000          -> O(n²) may work
n,q <= 2e5          -> O((n+q)log n)
values <= 1e6       -> Sieve / SPF / frequency
alphabet = 26       -> per-character arrays/Fenwick
subtree query       -> Euler Tour
range pair queries  -> Mo / offline
threshold answer    -> Binary Search on Answer
connectivity offline-> DSU
time intervals      -> Segment Tree over Time + Rollback DSU
n <= 1e18 + small state -> Matrix Exponentiation
100-digit bound     -> Digit DP
```

---

## BEFORE CODING A WEIRD FORMULA

Try in this order:

```text
1. Expand AND / OR / XOR identities.
2. Check the formula BIT BY BIT.
3. Move everything to one side and simplify.
4. Look for submask/supermask condition.
5. Look for parity / modulo invariant.
6. Check whether operation preserves SUM/XOR/GCD.
7. Check monotonicity -> Binary Search?
8. Huge N + tiny state -> Matrix Exponentiation.
9. Subtree -> Euler interval.
10. Range condition + offline queries -> sort/Mo/Fenwick/DSU.
```

### GOLDEN IDENTITIES

```text
x+y = (x|y)+(x&y)
x+y = (x^y)+2(x&y)

(x&y)=0 <=> x+y=x^y=x|y

(x&y)=x <=> x is submask of y
          <=> (x|y)=y

exactly 3 divisors <=> square of a prime

subtree(u) <=> [tin[u],tout[u]]

huge N + small state => MATRIX EXPONENTIATION
```
