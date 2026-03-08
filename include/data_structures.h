#pragma once
#include <vector>

using namespace std;

// Segment Tree for Range Sum Queries
// 0-indexed, ranges are [l, r)
struct SegmentTree {
    int n;
    vector<long long> tree;

    void init(int _n) {
        n = 1;
        while (n < _n) n *= 2;
        tree.assign(2 * n, 0);
    }

    void update(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = v;
            return;
        }
        int mid = (lx + rx) / 2;
        if (i < mid) update(i, v, 2 * x + 1, lx, mid);
        else update(i, v, 2 * x + 2, mid, rx);
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void update(int i, int v) {
        update(i, v, 0, 0, n);
    }

    long long query(int l, int r, int x, int lx, int rx) {
        if (lx >= r || rx <= l) return 0;
        if (lx >= l && rx <= r) return tree[x];
        int mid = (lx + rx) / 2;
        return query(l, r, 2 * x + 1, lx, mid) + query(l, r, 2 * x + 2, mid, rx);
    }

    long long query(int l, int r) {
        return query(l, r, 0, 0, n);
    }
};