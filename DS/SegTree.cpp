struct SegTree {
    int n;
    const int neutral = 0;           // TODO: change if needed
    vector<int> seg, lazy;
    vector<bool> hasLazy;
    
    SegTree(int sz) {
        n = sz;
        seg.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        hasLazy.assign(4 * n, false);
    }

private:
    int merge(int a, int b) {
        return a + b;                // TODO: change
    }

    void apply(int x, int lx, int rx, int v) {
        seg[x] += 1LL * (rx - lx + 1) * v;   // TODO: change
        lazy[x] += v;                        // TODO: change
        hasLazy[x] = true;
    }

    void push(int x, int lx, int rx) {
        if (!hasLazy[x] || lx == rx) return;

        int mid = (lx + rx) / 2;

        apply(x * 2 + 1, lx, mid, lazy[x]);
        apply(x * 2 + 2, mid + 1, rx, lazy[x]);

        lazy[x] = 0;
        hasLazy[x] = false;
    }

    void update(int l, int r, int v, int x, int lx, int rx) {
        if (r < lx || rx < l) return;

        if (l <= lx && rx <= r) {
            apply(x, lx, rx, v);
            return;
        }

        push(x, lx, rx);

        int mid = (lx + rx) / 2;

        update(l, r, v, x * 2 + 1, lx, mid);
        update(l, r, v, x * 2 + 2, mid + 1, rx);

        seg[x] = merge(seg[x * 2 + 1], seg[x * 2 + 2]);
    }

    int query(int l, int r, int x, int lx, int rx) {
        if (r < lx || rx < l) return neutral;
        if (l <= lx && rx <= r) return seg[x];

        push(x, lx, rx);

        int mid = (lx + rx) / 2;

        return merge(
            query(l, r, x * 2 + 1, lx, mid),
            query(l, r, x * 2 + 2, mid + 1, rx)
        );
    }

public:
    void update(int l, int r, int v) {
        update(l, r, v, 0, 0, n - 1);
    }

    int query(int l, int r) {
        return query(l, r, 0, 0, n - 1);
    }
};
