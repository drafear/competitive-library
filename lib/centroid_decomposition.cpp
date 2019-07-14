
template<class Edge>
class CentroidDecomposition {
  using Graph = vector<vector<typename Edge::type>>;
  const Graph G;
  const vector<ll> ids;
  void centroid_dfs(ll v, ll pv, vector<ll>& sz) const {
    sz[v] = 1;
    each(e, G[v]) {
      if (Edge::to(e) == pv) continue;
      centroid_dfs(Edge::to(e), v, sz);
      sz[v] += sz[Edge::to(e)];
    }
  }
  void build_tree(ll v, ll pv, ll pvid, vector<vector<typename Edge::type>>& nG, vector<ll>& nids) const {
    const ll vid = nG.size();
    nG.resize(nG.size()+1);
    nids.pb(ids[v]);
    each(e, G[v]) {
      if (Edge::to(e) == pv) {
        if (pvid >= 0) {
          typename Edge::type ne = e;
          Edge::to(ne) = pvid;
          nG[vid].pb(ne);
        }
      }
      else {
        typename Edge::type ne = e;
        Edge::to(ne) = nG.size();
        nG[vid].pb(ne);
        build_tree(Edge::to(e), v, vid, nG, nids);
      }
    }
  }
public:
  struct Result {
    ll centroid;
    vector<pair<vector<vector<typename Edge::type>>, vector<ll>>> trees;
  };
  CentroidDecomposition(Graph tree, vector<ll> ids) : G(move(tree)), ids(move(ids)) {}
  ll centroid() const {
    const ll n = G.size();
    vector<ll> sz(n);
    centroid_dfs(0, -1, sz);
    assert(sz[0] == n);
    rep(v, n) {
      ll mx = sz[0] - sz[v];
      each(e, G[v]) {
        if (sz[Edge::to(e)] < sz[v]) {
          chmax(mx, sz[Edge::to(e)]);
        }
      }
      if (mx <= n / 2) {
        return v;
      }
    }
    assert(false);
  }
  Result build() const {
    using Graph = vector<vector<typename Edge::type>>;
    vector<pair<Graph, vector<ll>>> res;
    ll g = centroid();
    each(e, G[g]) {
      Graph nG;
      vector<ll> nids;
      build_tree(Edge::to(e), g, -1, nG, nids);
      res.eb(nG, nids);
    }
    return {g, res};
  }
};
struct PEdge {
  using type = P;
  static ll to(const type& e) {
    return e.first;
  }
  static ll& to(type& e) {
    return e.first;
  }
};
struct llEdge {
  using type = ll;
  static ll to(const type& e) {
    return e;
  }
  static ll& to(type& e) {
    return e;
  }
};
