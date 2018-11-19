
void scc_dfs(ll v, vector<bool>& used, vector<ll>& vs, const vector<vector<ll>>& G) {
  used[v] = true;
  each(to, G[v]) {
    if (!used[to]) scc_dfs(to, used, vs, G);
  }
  vs.pb(v);
}
void scc_rdfs(ll v, ll k, vector<bool>& used, vector<ll>& cmp, const vector<vector<ll>>& rG) {
  used[v] = true;
  cmp[v] = k;
  each(to, rG[v]) {
    if (!used[to]) scc_rdfs(to, k, used, cmp, rG);
  }
}
// cmpが返る
// 同じcmpは強連結成分
// cmp[i] < cmp[j] なら j から i に行けない
vector<ll> scc(const vector<vector<ll>>& G) {
  const ll n = G.size();
  vector<bool> used(n, false);
  vector<ll> vs;
  rep(i, n) {
    if (!used[i]) scc_dfs(i, used, vs, G);
  }
  used.assign(n, false);
  vector<vector<ll>> rG(n);
  rep(i, n) {
    each(to, G[i]) {
      rG[to].pb(i);
    }
  }
  vector<ll> res(n);
  ll k = 0;
  rrep(i, vs.size()) {
    if (!used[vs[i]]) scc_rdfs(vs[i], k++, used, res, rG);
  }
  return res;
}
vector<vector<ll>> get_scc_graph(const vector<ll>& cmp, const vector<vector<ll>>& G) {
  vector<vector<ll>> res(*max_element(all(cmp))+1);
  rep(i, G.size()) {
    each(to, G[i]) {
      if (cmp[i] != cmp[to]) {
        res[cmp[i]].pb(cmp[to]);
      }
    }
  }
  rep(i, res.size()) {
    sort(all(res[i]));
    res[i].erase(unique(all(res[i])), res[i].end());
  }
  return res;
}
class Sat {
  ll n;
  vector<vector<ll>> G;
  ll node_id(ll id, bool b) const {
    return id * 2 + b;
  }
public:
  Sat(ll size) : n(size), G(size*2) {}
  // (id1, b1) => (id2, b2)
  void add(ll id1, bool b1, ll id2, bool b2) {
    // cout << "add: " << id1 << " " << b1 << " " << id2 << " " << b2 << endl;
    G[node_id(id1, b1)].pb(node_id(id2, b2));
    G[node_id(id2, !b2)].pb(node_id(id1, !b1));
  }
  bool check() const {
    vector<ll> cmp = scc(G);
    rep(i, n) {
      if (cmp[node_id(i, true)] == cmp[node_id(i, false)]) {
        return false;
      }
    }
    return true;
  }
  vector<bool> solve() const {
    assert( check() );
    vector<ll> cmp = scc(G);
    vector<bool> used(n, false), res(n);
    vector<P> v;
    rep(i, 2*n) v.eb(cmp[i], i);
    sort(all(v), greater<P>());
    stack<ll> S;
    each(p, v) {
      ll i = p.second;
      if (used[i/2]) continue;
      used[i/2] = true;
      S.push(i);
      while ( !S.empty() ) {
        ll v = S.top(); S.pop();
        res[v/2] = v & 1;
        each(to, G[v]) {
          if (used[to/2]) continue;
          used[to/2] = true;
          S.push(to);
        }
      }
    }
    return res;
  }
};
