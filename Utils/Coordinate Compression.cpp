template <typename T>
class Comp {
private:
  vector<T> values;
  unordered_map<T, int> id;
  Comp() {}
  void build(const vector<T>& a) {
    values = a;
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    id.clear();
    for (int i = 0; i < values.size(); i++)
      id[values[i]] = i;
  }
public:
  Comp(const vector<T>& a) {
    build(a);
  }
  // Original -> Compressed (O(1) average)
  int compress(const T& x) const {
    return id.at(x);
  }
  // Compressed -> Original (O(1))
  T decompress(int idx) const {
    return values[idx];
  }
};
