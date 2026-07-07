/*
============================== MEX Template ==============================

MEX = Minimum EXcluded value.
The smallest non-negative integer that does NOT exist.

Time Complexity
---------------
init(n)   : O(n log n)
clear()   : O(n log n)
add(x)    : O(log n)
remove(x) : O(log n)
mex()     : O(1)

Memory
------
O(n)

Common Uses
-----------

1) Whole Array
--------------
MEX mex(n);
for (int x : a) mex.add(x);
cout << mex.mex();

2) Prefix MEX
-------------
MEX mex(n);
for (int i = 0; i < n; i++) {
    mex.add(a[i]);
    pref[i] = mex.mex();
}

3) Suffix MEX
-------------
MEX mex(n);
for (int i = n - 1; i >= 0; i--) {
    mex.add(a[i]);
    suf[i] = mex.mex();
}

4) Sliding Window
-----------------
MEX mex(n);

for (int i = 0; i < k; i++)
    mex.add(a[i]);

cout << mex.mex();

for (int i = k; i < n; i++) {
    mex.remove(a[i - k]);
    mex.add(a[i]);
    cout << mex.mex();
}

5) Point Update
---------------
mex.remove(a[pos]);
a[pos] = newValue;
mex.add(a[pos]);

6) Mo's Algorithm
-----------------
void Add(int idx){
    mex.add(a[idx]);
}

void Remove(int idx){
    mex.remove(a[idx]);
}

answer = mex.mex();

7) Rebuild
----------
mex.clear();

for (int x : a)
    mex.add(x);

=======================================================================
*/

struct MEX {
    vector<int> freq;
    set<int> missing;

    MEX(int n = 0) { init(n); }

    void init(int n) {
        freq.assign(n + 2, 0);
        missing.clear();
        for (int i = 0; i <= n + 1; i++)
            missing.insert(i);
    }

    void add(int x) {
        if (x < 0 || x >= freq.size()) return;
        if (++freq[x] == 1)
            missing.erase(x);
    }

    void remove(int x) {
        if (x < 0 || x >= freq.size()) return;
        if (--freq[x] == 0)
            missing.insert(x);
    }

    int mex() const {
        return *missing.begin();
    }

    void clear() {
        fill(freq.begin(), freq.end(), 0);
        missing.clear();
        for (int i = 0; i < freq.size(); i++)
            missing.insert(i);
    }
};
