class Tree {
  ll expand(ll x) {
    ll res = 0;
    while ((1LL<<res) < x) ++res;
    return res;
  }
  void prepare_lca() {
    if (par.size() == 0) dfs();
    par2.assign(expand(n)+1, par);
    rep(i, 1, par2.size()) {
      rep(j, n) {
        if (par2[i-1][j] < 0) par2[i][j] = par2[i-1][j];
        else par2[i][j] = par2[i-1][par2[i-1][j]];
      }
    }
  }
  void dfs(ll v, ll pv, ll d) {
    par[v] = pv;
    depth[v] = d;
    size[v] = 1;
    each(to, G[v]) {
      if (to == pv) continue;
      chs[v].pb(to);
      dfs(to, v, d+1);
      size[v] += size[to];
    }
  }
public:
  ll n;
  vector<vector<ll>> G, chs;
  vector<ll> par, depth, size;
  vector<vector<ll>> par2;
  Tree(ll sz) : n(sz), G(sz) {
  }
  void add(ll u, ll v) {
    G[u].pb(v);
    G[v].pb(u);
  }
  void dfs() {
    par.assign(n, -1);
    chs.clear(); chs.resize(n);
    size.assign(n, 0);
    depth.assign(n, 0);
    dfs(0, -1, 0);
  }
  ll lca(ll u, ll v) {
    if (par2.size() == 0) prepare_lca();
    if (depth[u] > depth[v]) swap(u, v);
    rrep(i, par2.size()) {
      if ((depth[v] - depth[u]) & (1LL<<i)) {
        v = par2[i][v];
      }
    }
    assert(depth[u] == depth[v]);
    if (u == v) return u;
    rrep(i, par2.size()) {
      if (par2[i][u] != par2[i][v]) {
        u = par2[i][u];
        v = par2[i][v];
      }
    }
    assert(par[u] == par[v] && par[u] >= 0);
    return par[u];
  }
};
