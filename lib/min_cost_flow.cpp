const ll maxV = 3e5;

struct Edge {
  ll to, cap, cost, rev;
};

vector<vector<Edge>> G;

void add_edge(ll from, ll to, ll cap, ll cost) {
  if (from < 0 || to < 0) return;
  G[from].push_back({to, cap, cost, (ll)G[to].size()});
  G[to].push_back({from, 0, -cost, (ll)G[from].size()-1});
}

ll dist[maxV], h[maxV] = {0}, prevV[maxV], prevE[maxV];
ll min_cost_flow(ll s, ll t, ll f, bool is_ford_first = false) {
  ll res = 0;
  while (f > 0) {
    fill(dist, dist+maxV, linf); dist[s] = 0;
    if (is_ford_first) {
      while (1) {
        bool is_update = false;
        rep(v, G.size()) {
          if (dist[v] == linf) continue;
          rep(i, G[v].size()) {
            const Edge& e = G[v][i];
            if (e.cap > 0 && dist[v] + e.cost < dist[e.to]) {
              dist[e.to] = dist[v] + e.cost;
              prevV[e.to] = v;
              prevE[e.to] = i;
              is_update = true;
            }
          }
        }
        if (!is_update) break;
      }
    }
    else {
      priority_queue<P, vector<P>, greater<P> > Q; Q.push({0, s});
      while ( !Q.empty() ) {
        P p = Q.top(); Q.pop();
        ll v = p.second;
        if (p.first > dist[v]) continue;
        for (ll i = 0; i < G[v].size(); ++i) {
          Edge& e = G[v][i];
          if (e.cap > 0 && dist[v]+e.cost+h[v]-h[e.to] < dist[e.to]) {
            dist[e.to] = dist[v]+e.cost+h[v]-h[e.to];
            prevV[e.to] = v;
            prevE[e.to] = i;
            Q.push({dist[e.to], e.to});
          }
        }
      }
    }
    rep(i, G.size()) h[i] += dist[i];
    if (dist[t] == linf) {
      throw res;
    }
    ll d = f;
    for (ll v = t; v != s; v = prevV[v]) {
      d = min(d, G[prevV[v]][prevE[v]].cap);
    }
    f -= d;
    res += d * h[t];
    for (ll v = t; v != s; v = prevV[v]) {
      Edge& e = G[prevV[v]][prevE[v]];
      e.cap -= d;
      G[e.to][e.rev].cap += d;
    }
  }
  return res;
}
