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

template<class Calc>
class EdgeDpOnForest {
public:
  using T = typename Calc::type;
  struct Edge {
    ll to, rev;
    T value;
  };
private:
  ll n;
  void dfs1(ll v, ll pv) {
    ll idx = -1;
    vector<T> values;
    rep(i, G[v].size()) {
      const Edge& e = G[v][i];
      if (e.to == pv) {
        idx = i;
        continue;
      }
      dfs1(e.to, v);
      values.pb(e.value);
    }
    // 根以外では親から入る辺の値を更新
    if (idx >= 0) {
      const Edge& e = G[v][idx];
      G[e.to][e.rev].value = Calc::merge(values);
    }
  }
  void dfs2(ll v, ll pv) {
    vector<T> values;
    each(e, G[v]) values.pb(e.value);
    values = Calc::evaluate(values);
    rep(i, G[v].size()) {
      const Edge& e = G[v][i];
      if (e.to == pv) continue;
      G[e.to][e.rev].value = values[i];
      dfs2(e.to, v);
    }
  }
public:
  UnionFind uf;
  vector<vector<Edge>> G;
  EdgeDpOnForest(ll n) : n(n), uf(n), G(n) {}
  void add(ll u, ll v) {
    assert(!uf.isUnited(u, v));
    G[u].pb({v, ll(G[v].size())});
    G[v].pb({u, ll(G[u].size())-1});
    uf.unite(u, v);
  }
  void dp() {
    vector<bool> used(n, false);
    rep(i, n) {
      if (used[uf.root(i)]) continue;
      dfs1(i, -1);
      used[uf.root(i)] = true;
    }
    used.assign(n, false);
    rep(i, n) {
      if (used[uf.root(i)]) continue;
      dfs2(i, -1);
      used[uf.root(i)] = true;
    }
  }
  size_t size() const {
    return G.size();
  }
};

struct Diameter {
  using type = ll;
  // その頂点から出ていく値から入ってくる値を計算する
  static vector<type> evaluate(const vector<type>& value) {
    const ll n = value.size();
    vector<type> v = value;
    v.pb(0);
    sort(all(v), greater<type>());
    vector<type> res(n);
    rep(i, n) {
      if (value[i] == v[0]) {
        res[i] = v[1]+1;
      }
      else {
        res[i] = v[0]+1;
      }
    }
    return res;
  }
  // (辺数-1)個の出ていく値から1個の入ってくる値を計算する
  static type merge(const vector<type>& value) {
    if (value.size() == 0) return 1;
    return *max_element(all(value)) + 1;
  }
};
