// select S ⊆ {1, 2, ..., n} and |S| = m
vector<ll> select(ll n, ll m) {
  assert(m <= n);
  if (m * 50 <= n) {
    set<ll> used;
    vector<ll> res(m);
    rep(i, m) {
      ll x;
      do {
        x = rnd.next(n);
      } while (used.count(x) > 0);
      res[i] = x;
      used.insert(x);
    }
    sort(all(res));
    return res;
  }
  if (m * 2 <= n) {
    vector<bool> used(n, false);
    vector<ll> res(m);
    rep(i, m) {
      ll x;
      do {
        x = rnd.next(n);
      } while (used[x]);
      res[i] = x;
      used[x] = true;
    }
    sort(all(res));
    return res;
  }
  vector<ll> unselect = select(n, n-m);
  vector<ll> res;
  ll j = 0;
  rep(i, n) {
    while (j < unselect.size() && unselect[j] < i) ++j;
    if (j < unselect.size() && unselect[j] == i) {
      continue;
    }
    res.pb(i);
  }
  return res;
}

// select m elements from v
template<class T>
vector<T> select(const vector<T>& v, const ll m) {
  vector<ll> sel = select(v.size(), m);
  vector<T> res(m);
  rep(i, m) res[i] = v[sel[i]];
  sort(all(res));
  return res;
}
vector<ll> sub(const vector<ll>& a, const vector<ll>& b) {
  ll j = 0;
  vector<ll> res;
  rep(i, a.size()) {
    while (j < b.size() && b[j] < a[i]) ++j;
    if (j < b.size() && b[j] == a[i]) continue;
    res.pb(a[i]);
  }
  return res;
}
