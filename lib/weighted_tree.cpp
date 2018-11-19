class WeightedTree {
    const ll id = 0;
    ll merge(ll a, ll b) {
        return a + b;
    }
    ll expand(ll x) {
        ll res = 0;
        while ((1LL<<res) < x) ++res;
        return res;
    }
    void prepare_lca() {
        if (par.size() == 0) dfs();
        par2.assign(expand(n)+1, vector<ll>(par.size()));
        cost.assign(par2.size(), vector<ll>(par.size(), id));
        rep(i, n) {
            par2[0][i] = par[i].to;
            cost[0][i] = par[i].cost;
        }
        rep(i, 1, par2.size()) {
            rep(j, n) {
                if (par2[i-1][j] < 0) {
                    par2[i][j] = par2[i-1][j];
                    cost[i][j] = cost[i-1][j];
                }
                else {
                    par2[i][j] = par2[i-1][par2[i-1][j]];
                    cost[i][j] = merge(cost[i-1][j], cost[i-1][par2[i-1][j]]);
                }
            }
        }
    }
    void dfs(ll v, ll pv, ll d) {
        depth[v] = d;
        size[v] = 1;
        each(e, G[v]) {
            if (e.to == pv) continue;
            chs[v].pb(e);
            par[e.to] = {v, e.cost};
            dfs(e.to, v, d+1);
            size[v] += size[e.to];
        }
    }
public:
    struct Edge {
        ll to, cost;
    };
    ll n;
    vector<vector<Edge>> G, chs;
    vector<Edge> par;
    vector<ll> depth, size;
    vector<vector<ll>> par2;
    vector<vector<ll>> cost;
    WeightedTree(ll sz) : n(sz), G(sz) {
    }
    void add(ll u, ll v, ll c) {
        G[u].pb({v, c});
        G[v].pb({u, c});
    }
    void dfs() {
        par.assign(n, {-1, id});
        chs.clear(); chs.resize(n);
        size.assign(n, 0);
        depth.assign(n, 0);
        dfs(0, -1, 0);
    }
    P lca(ll u, ll v) {
        if (par2.size() == 0) prepare_lca();
        if (depth[u] > depth[v]) swap(u, v);
        ll res = id;
        rrep(i, par2.size()) {
            if ((depth[v] - depth[u]) & (1LL<<i)) {
                res = merge(res, cost[i][v]);
                v = par2[i][v];
            }
        }
        assert(depth[u] == depth[v]);
        if (u == v) return {u, res};
        rrep(i, par2.size()) {
            if (par2[i][u] != par2[i][v]) {
                res = merge(res, cost[i][u]);
                res = merge(res, cost[i][v]);
                u = par2[i][u];
                v = par2[i][v];
            }
        }
        assert(par[u].to == par[v].to && par[u].to >= 0);
        return {par[u].to, res};
    }
};
