ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
template<typename T>
map<T, ll> get_zaatu(vector<T> vals) {
  sort(all(vals));
  vals.erase(unique(all(vals)), vals.end());
  map<T, ll> res;
  rep(i, vals.size()) res[vals[i]] = i;
  return res;
}
template<typename T>
void zaatu(vector<T>& vals) {
  map<T, ll> z = get_zaatu(vals);
  each(x, vals) x = z[x];
}
// template<typename T1, T2>
// void zaatu(vector<T1>& vals, const function<T2(T1)>& f) {
//   vector<T&> v;
//   each(x, vals) v.pb(f(x));
//   zaatu(v);
// }
