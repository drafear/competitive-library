class UnionFind {
    vector<ll> par, h, sz;
public:
    UnionFind(ll size) : par(size, 0), h(size, 0), sz(size, 1) {
        rep(i, size) par[i] = i;
    }
    void unite(ll u, ll v) {
        u = root(u), v = root(v);
        if (u == v) return;
        if (h[u] < h[v]) {
            par[u] = v;
            sz[v] += sz[u];
        }
        else {
            par[v] = u;
            sz[u] += sz[v];
        }
        if (h[u] == h[v]) ++h[u];
    }
    ll size(ll v) {
        return sz[root(v)];
    }
    bool isUnited(ll u, ll v) {
        return root(u) == root(v);
    }
    ll root(ll v) {
        if (par[v] == v) return v;
        return par[v] = root(par[v]);
    }
};
