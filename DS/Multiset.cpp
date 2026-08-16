class Multiset {
private:
  // use with positive numbers only and limited
  // if you have big or non-positive numbers, compress them
  vector<int> Bit;
  int SZ, size_set;

  void add(int pos, int val) {
    for (++pos; pos <= SZ; pos += pos & -pos)
      Bit[pos - 1] += val;
  }

  int get(int pos) {
    int ret = 0;
    for (++pos; pos; pos -= pos & -pos)
      ret += Bit[pos - 1];
    return ret;
  }

  int BS(int val) {
    int s = 0;
    for (int sz = SZ >> 1; sz; sz >>= 1) {
      if (Bit[s + sz - 1] < val)
        val -= Bit[(s += sz) - 1];
    }
    return s;
  }

public:
  // Time: O(log SZ)
  Multiset() : size_set(0), SZ(1 << 20) {
    Bit.resize(SZ);
    add(0, -1);
  }

  // Time: O(log SZ)
  void insert(int val) {
    ++size_set;
    add(val, 1);
  }

  // Time: O(log SZ)
  int count(int val) {
    return get(val) - get(val - 1);
  }

  // Time: O(log SZ)
  void erase_all(int val) {
    int c = count(val);
    size_set -= c;
    add(val, -c);
  }

  // Time: O(log SZ)
  void erase_idx(int index) {
    --size_set;
    add(BS(index), -1);
  }

  // Time: O(log SZ)
  int order_of_key(int val) {
    return get(val) - count(val) + 1;
  }

  // Time: O(log SZ)
  int operator[](int index) {
    return BS(index);
  }

  // Time: O(1)
  int size() const {
    return size_set;
  }
};
