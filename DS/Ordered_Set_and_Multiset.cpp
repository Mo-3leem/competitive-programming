#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;

// ===================== ordered_set (unique) =====================
template <class T>
using ordered_set = tree<
  T,
  null_type,
  less<T>,
  rb_tree_tag,
  tree_order_statistics_node_update
>;

// ===================== ordered_multiset base (duplicates) =====================
template <class T>
using ordered_multiset = tree<
  pair<T, ll>,
  null_type,
  less<pair<T, ll>>,
  rb_tree_tag,
  tree_order_statistics_node_update
>;

// ===================== ordered_set helpers =====================
template <class T>
int order_of_key(const ordered_set<T>& os, const T& x) { return (int)os.order_of_key(x); }

template <class T>
T kth(const ordered_set<T>& os, int k) { return *os.find_by_order(k); }

template <class T>
bool kth_safe(const ordered_set<T>& os, int k, T& out) {
  if (k < 0 || k >= (int)os.size()) return false;
  out = *os.find_by_order(k);
  return true;
}

template <class T>
bool erase_kth(ordered_set<T>& os, int k) {
  if (k < 0 || k >= (int)os.size()) return false;
  os.erase(os.find_by_order(k));
  return true;
}

template <class T>
bool contains(const ordered_set<T>& os, const T& x) { return os.find(x) != os.end(); }

template <class T>
bool get_min(const ordered_set<T>& os, T& out) {
  if (os.empty()) return false;
  out = *os.begin();
  return true;
}

template <class T>
bool get_max(const ordered_set<T>& os, T& out) {
  if (os.empty()) return false;
  out = *os.rbegin();
  return true;
}

// numeric only (int/ll)
template <class Num>
int count_in_range_num(const ordered_set<Num>& os, Num L, Num R) {
  if (R < L) return 0;
  return (int)(os.order_of_key(R + 1) - os.order_of_key(L));
}

// pair: count by first in [L,R] (A must be numeric)
template <class A, class B>
int count_first_in_range(const ordered_set<pair<A, B>>& os, A L, A R) {
  if (R < L) return 0;
  int left  = (int)os.order_of_key({L, numeric_limits<B>::min()});
  int right = (int)os.order_of_key({(A)(R + 1), numeric_limits<B>::min()});
  return right - left;
}

// ===================== OMS<T> (ordered multiset wrapper) =====================
template <class T>
struct OMS {
  ordered_multiset<T> t;
  ll uid = 0;

  void insert(const T& x) { t.insert({x, uid++}); }

  bool erase_one(const T& x) {
    auto it = t.lower_bound({x, numeric_limits<ll>::min()});
    if (it == t.end() || it->first != x) return false;
    t.erase(it);
    return true;
  }

  bool erase_kth(int k) {
    if (k < 0 || k >= (int)t.size()) return false;
    t.erase(t.find_by_order(k));
    return true;
  }

  int count(const T& x) const {
    int L = (int)t.order_of_key({x, numeric_limits<ll>::min()});
    int R = (int)t.order_of_key({x, numeric_limits<ll>::max()});
    return R - L;
  }

  int order_of_key_value(const T& x) const {
    return (int)t.order_of_key({x, numeric_limits<ll>::min()});
  }

  int order_of_key_leq(const T& x) const {
    return (int)t.order_of_key({x, numeric_limits<ll>::max()});
  }

  T kth(int k) const { return t.find_by_order(k)->first; }

  bool kth_safe(int k, T& out) const {
    if (k < 0 || k >= (int)t.size()) return false;
    out = t.find_by_order(k)->first;
    return true;
  }

  int size() const { return (int)t.size(); }
  bool empty() const { return t.empty(); }
  void clear() { t.clear(); uid = 0; }

  auto lower_bound_value(const T& x) const {
    return t.lower_bound({x, numeric_limits<ll>::min()});
  }

  auto upper_bound_value(const T& x) const {
    return t.upper_bound({x, numeric_limits<ll>::max()});
  }

  bool get_min(T& out) const {
    if (t.empty()) return false;
    out = t.begin()->first;
    return true;
  }

  bool get_max(T& out) const {
    if (t.empty()) return false;
    out = t.rbegin()->first;
    return true;
  }

  int count_in_range(const T& L, const T& R) const {
    if (R < L) return 0;
    int right = (int)t.order_of_key({R, numeric_limits<ll>::max()}); // <= R
    int left  = (int)t.order_of_key({L, numeric_limits<ll>::min()}); // < L
    return right - left;
  }

  bool contains(const T& x) const { return count(x) > 0; }
};

/*
====================== PBDS QUICK GUIDE (CONTEST) ======================
All operations are on a balanced BST (RB-tree).
Let n = current size.

ordered_set<T>  (unique like set)
-----------------------------------------------------------------------
Basics (same as set):
- os.insert(x)                 : insert x (unique)                     O(log n)
- os.erase(x)                  : erase value x                         O(log n)
- os.erase(it)                 : erase by iterator                     O(log n)
- os.find(x)                   : iterator to x / os.end()              O(log n)
- os.count(x)                  : 0 or 1                                O(log n)
- os.lower_bound(x)            : first >= x                            O(log n)
- os.upper_bound(x)            : first >  x                            O(log n)
- *os.begin() / *os.rbegin()   : min / max (if not empty)              O(1)
- os.size(), os.empty()        : size / empty                          O(1)
- os.clear()                   : clear                                 O(n)

Order Statistics (PBDS):
- os.order_of_key(x)           : #elements strictly < x                O(log n)
- os.find_by_order(k)          : iterator to k-th (0-indexed)          O(log n)

Helpers in this template:
- order_of_key(os, x)          : same as os.order_of_key(x)            O(log n)
- kth(os, k)                   : value of k-th (ASSUME valid)          O(log n)
- kth_safe(os, k, out)         : safe kth (bool)                       O(log n)
- erase_kth(os, k)             : erase k-th (bool)                     O(log n)
- contains(os, x)              : exists?                               O(log n)
- get_min(os, out)             : min value (bool)                      O(1)
- get_max(os, out)             : max value (bool)                      O(1)
- count_in_range_num(os,L,R)   : count in [L,R] numeric only           O(log n)
- count_first_in_range(os,L,R) : for set<pair<A,B>> count by first     O(log n)

-----------------------------------------------------------------------
OMS<T>  (ordered multiset / duplicates allowed)
Let n = ms.size().
-----------------------------------------------------------------------
Insert/Delete:
- ms.insert(x)                 : insert x (duplicates allowed)         O(log n)
- ms.erase_one(x)              : erase ONE occurrence of x (bool)      O(log n)
- ms.erase_kth(k)              : erase k-th (0-indexed) (bool)         O(log n)
- ms.clear()                   : clear all                             O(n)

Counts / Queries:
- ms.count(x)                  : occurrences of x                      O(log n)
- ms.contains(x)               : exists?                               O(log n)
- ms.order_of_key_value(x)     : #elements strictly < x                O(log n)
- ms.order_of_key_leq(x)       : #elements <= x                        O(log n)
- ms.count_in_range(L,R)       : #elements in [L,R]                    O(log n)
- ms.kth(k)                    : k-th value (ASSUME valid)             O(log n)
- ms.kth_safe(k,out)           : safe kth (bool)                       O(log n)
- ms.lower_bound_value(x)      : iterator to first value >= x          O(log n)
- ms.upper_bound_value(x)      : iterator to first value >  x          O(log n)
- ms.get_min(out) / get_max(out): min/max value (bool)                 O(1)
- ms.size(), ms.empty()        : size / empty                          O(1)

-----------------------------------------------------------------------
PAIR ORDERING NOTE
-----------------------------------------------------------------------
- Default ordering is lexicographic:
  (a,b) < (c,d) if a<c or (a==c and b<d)
=======================================================================
*/
