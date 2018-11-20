struct Edge {
  ll to, cap, rev;
};

vector< vector<Edge> > G;

void add_edge(ll from, ll to, ll cap) {
  G[from].pb({to, cap, (ll)G[to].size()});
  G[to].pb({from, 0, (ll)G[from].size()-1});
}

ll dfs(ll v, ll t, ll f, vector<bool>& used) {
  if (v == t) return f;
  if (used[v]) return 0;
  used[v] = true;
  EACH(e, G[v]) {
    if (e.cap > 0) {
      ll d = dfs(e.to, t, min(f, e.cap), used);
      if (d > 0) {
        e.cap -= d;
        G[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

ll max_flow(ll s, ll t) {
  ll res = 0;
  while (1) {
    vector<bool> used(G.size(), false);
    ll f = dfs(s, t, linf, used);
    if (f == 0) break;
    res += f;
  }
  return res;
}
