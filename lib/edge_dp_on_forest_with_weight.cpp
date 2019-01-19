class UnionFind {
  vector<ll> par, h;
public:
  UnionFind(ll size) : par(size, 0), h(size, 0) {
    rep(i, size) par[i] = i;
  }
  void unite(ll u, ll v) {
    u = root(u), v = root(v);
    if (u == v) return;
    if (h[u] < h[v]) {
      par[u] = v;
    }
    else {
      par[v] = u;
    }
    if (h[u] == h[v]) ++h[u];
  }
  bool isUnited(ll u, ll v) {
    return root(u) == root(v);
  }
  ll root(ll v) {
    if (par[v] == v) return v;
    return par[v] = root(par[v]);
  }
};

template<typename Weight, typename Value>
struct DpEdge {
  ll to, rev;
  Weight weight;
  Value value;
};

template<class Calc>
class EdgeDpOnForest {
public:
  using T = typename Calc::type;
  using Weight = typename Calc::edge_type;
  using Edge = DpEdge<Weight, T>;
private:
  ll n;
  void dfs1(ll v, ll pv) {
    ll idx = -1;
    vector<Edge> edges;
    rep(i, G[v].size()) {
      const Edge& e = G[v][i];
      if (e.to == pv) {
        idx = i;
        continue;
      }
      dfs1(e.to, v);
      edges.pb(e);
    }
    // 根以外では親から入る辺の値を更新
    if (idx >= 0) {
      const Edge& e = G[v][idx];
      G[e.to][e.rev].value = Calc::merge(edges, G[v][idx]);
    }
  }
  void dfs2(ll v, ll pv) {
    vector<T> values = Calc::evaluate(G[v], v);
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
  void add(ll u, ll v, Weight w) {
    assert(!uf.isUnited(u, v));
    G[u].pb({v, ll(G[v].size()), w});
    G[v].pb({u, ll(G[u].size())-1, w});
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

struct Merger {
  using type = ll;
  using edge_type = ll;
  using Edge = DpEdge<type, edge_type>;
  // その頂点から出ていく値から入ってくる値を計算する
  static vector<type> evaluate(const vector<Edge>& edges, const ll node_id) {
  }
  // (辺数-1)個の出ていく値から1個の入ってくる値を計算する
  static type merge(const vector<Edge>& edges, const Edge& e) {
  }
};
