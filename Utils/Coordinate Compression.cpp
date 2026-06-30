template <typename T>
class Comp {
private:
    vector<T> values;
    unordered_map<T, int> id;

public:
    Comp() = default;

    Comp(const vector<T>& a) {
        build(a);
    }

    void build(const vector<T>& a) {
        values = a;
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());

        id.clear();
        id.reserve(values.size());      // optional: faster
        for (int i = 0; i < (int)values.size(); i++)
            id[values[i]] = i;
    }

    // Original -> Compressed
    int compress(const T& x) const {
        return id.at(x);                // O(1) average
    }

    // Compressed -> Original
    T decompress(int idx) const {
        return values[idx];
    }

    // Number of distinct values
    int size() const {
        return values.size();
    }

    // Compress in-place
    void compress(vector<T>& a) const {
        for (auto &x : a)
            x = id.at(x);
    }
};
