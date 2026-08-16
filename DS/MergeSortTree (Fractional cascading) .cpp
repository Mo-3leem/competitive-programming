/*
    Merge Sort Tree + Fractional Cascading
    ---------------------------------------
    Supports:
        query(l, r, x) = count of a[i] <= x, l <= i <= r

    Complexity:
        Build  : O(N log N)
        Query  : O(log N)
        Memory : O(N log N)
*/

struct FractionalMergeSortTree {
    struct Node {
        vector<int> val;
        vector<int> lp, rp;
    };

    int n;
    vector<Node> tree;

    void mergeNode(int p) {
        Node &cur = tree[p];
        Node &L = tree[p * 2 + 1];
        Node &R = tree[p * 2 + 2];

        int n1 = L.val.size();
        int n2 = R.val.size();

        cur.val.resize(n1 + n2);
        cur.lp.resize(n1 + n2 + 1);
        cur.rp.resize(n1 + n2 + 1);

        int i = 0, j = 0;

        cur.lp[0] = cur.rp[0] = 0;

        for (int k = 0; k < n1 + n2; k++) {
            if (i < n1 && (j == n2 || L.val[i] <= R.val[j])) {
                cur.val[k] = L.val[i++];
            }
            else {
                cur.val[k] = R.val[j++];
            }

            cur.lp[k + 1] = i;
            cur.rp[k + 1] = j;
        }
    }

    void build(vector<int> &a, int p, int l, int r) {
        if (l == r) {
            tree[p].val = {a[l]};
            tree[p].lp = {0, 0};
            tree[p].rp = {0, 0};

            return;
        }

        int mid = (l + r) / 2;

        build(a, p * 2 + 1, l, mid);
        build(a, p * 2 + 2, mid + 1, r);

        mergeNode(p);
    }

    int query(
        int ql, int qr,
        int p, int l, int r,
        int pos
    ) {
        if (qr < l || r < ql)
            return 0;

        if (ql <= l && r <= qr)
            return pos;

        int mid = (l + r) / 2;

        int leftPos  = tree[p].lp[pos];
        int rightPos = tree[p].rp[pos];

        return query(
                   ql, qr,
                   p * 2 + 1,
                   l, mid,
                   leftPos
               )
             +
               query(
                   ql, qr,
                   p * 2 + 2,
                   mid + 1, r,
                   rightPos
               );
    }

public:

    FractionalMergeSortTree() {}

    FractionalMergeSortTree(vector<int> &a) {
        build(a);
    }

    void build(vector<int> &a) {
        n = a.size();
        tree.assign(4 * n, {});
        build(a, 0, 0, n - 1);
    }

    /*
        Count elements <= x in [l, r].
    */
    int query(int l, int r, int x) {

        int pos = upper_bound(
            tree[0].val.begin(),
            tree[0].val.end(),
            x
        ) - tree[0].val.begin();

        return query(
            l, r,
            0, 0, n - 1,
            pos
        );
    }

    // Count elements < x in [l, r]
    int countLess(int l, int r, int x) {
        return query(l, r, x - 1);
    }

    // Count elements > x in [l, r]
    int countGreater(int l, int r, int x) {
        return (r - l + 1) - query(l, r, x);
    }

    // Count elements >= x in [l, r]
    int countGreaterEqual(int l, int r, int x) {
        return (r - l + 1) - countLess(l, r, x);
    }

    // Count x <= a[i] <= y in [l, r]
    int countRange(int l, int r, int x, int y) {
        return query(l, r, y) - countLess(l, r, x);
    }
};
