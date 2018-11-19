// solve {x_i - x_j = c | (i, j, c) in E}
class Potential {
  vector<ll> par, h;
public:
  vector<ll> pot;
  Potential(ll size) : par(size, 0), h(size, 0), pot(size, 0) {
    rep(i, size) par[i] = i;
  }
  // u - v = cost?
  bool check(ll u, ll v, ll cost) {
    return pot[u] - pot[v] == cost;
  }
  // add: u - v = cost
  void add(ll u0, ll v0, ll cost) {
    ll u = root(u0), v = root(v0);
    if (u == v) {
      if (!check(u0, v0, cost)) throw -1;
      return;
    }
    if (h[u] > h[v]) {
      pot[v] = -cost + pot[u0] - pot[v0];
      par[v] = u;
    }
    else {
      pot[u] = cost + pot[v0] - pot[u0];
      par[u] = v;
    }
    if (h[u] == h[v]) ++h[u];
  }
  bool isUnited(ll u, ll v) {
    return root(u) == root(v);
  }
  ll root(ll v) {
    if (par[v] == v) return v;
    ll r = root(par[v]);
    pot[v] += pot[par[v]];
    return par[v] = r;
  }
};
