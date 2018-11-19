class StarrySkyTree {
private:
  ll base;
  vector<ll> s;
  vector<ll> mn;
  void update_mn(ll n) {
    if (n == 0) return;
    mn[n] = min(get_min(n*2), get_min(n*2+1));
  }
  void add(ll l, ll r, ll n, ll L, ll R, ll val) {
    if (r <= L || R <= l) return;
    if (L <= l && r <= R) {
      s[n] += val;
      return;
    }
    ll m = (l + r) / 2;
    add(l, m, n*2, L, R, val);
    add(m, r, n*2+1, L, R, val);
    mn[n] = min(get_min(n*2), get_min(n*2+1));
  }
  ll get_min(ll n) {
    return min(linf, mn[n] + s[n]);
  }
  ll get_min(ll l, ll r, ll n, ll L, ll R) {
    if (r <= L || R <= l) return linf;
    if (L <= l && r <= R) return get_min(n);
    ll m = (l + r) / 2;
    ll res = min(get_min(l, m, n*2, L, R), get_min(m, r, n*2+1, L, R));
    return min(linf, res+s[n]);
  }
  void get_min_pos(ll l, ll r, ll n, ll L, ll R, ll sum, vector<ll>& res) {
    if (r <= L || R <= l) return;
    if (mn[n] + s[n] + sum > 0) return;
    assert(l < r);
    if (r - l == 1) {
      res.pb(n-base);
    }
    else {
      ll m = (l + r) / 2;
      get_min_pos(l, m, n*2, L, R, sum+s[n], res);
      get_min_pos(m, r, n*2+1, L, R, sum+s[n], res);
    }
  }
public:
  StarrySkyTree(ll n) {
    for (base = 1; base < n; base <<= 1);
    s = vector<ll>(base*2, 0);
    mn = vector<ll>(base*2, 0);
  }
  void add(ll l, ll r, ll val) {
    add(0, base, 1, l, r, val);
  }
  ll get_min(ll l, ll r) {
    assert(0 <= l && l < r && r <= base);
    return get_min(0, base, 1, l, r);
  }
  vector<ll> get_min_pos(ll l, ll r) {
    ll min_value = get_min(l, r);
    vector<ll> res;
    get_min_pos(0, base, 1, l, r, -min_value, res);
    return res;
  }
};
