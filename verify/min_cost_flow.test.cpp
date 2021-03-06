/*==start==
judge: aoj
problem_id: GRL_6_B
==end==*/

// vvvvvvvvvvvv TEMPLATE vvvvvvvvvvvv
#include <bits/stdc++.h>
using namespace std; using ll = long long; using P = pair<ll, ll>;
const ll linf = 1e18; const double eps = 1e-12, pi = acos(-1);
#define FOR(i,a,b) for (ll i=(a),__last_##i=(b);i<__last_##i;i++)
#define RFOR(i,a,b) for (ll i=(b)-1,__last_##i=(a);i>=__last_##i;i--)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)
#define __GET_MACRO3(_1, _2, _3, NAME, ...) NAME
#define each(i,a) for (auto&& i : a)
#define rep(...) __GET_MACRO3(__VA_ARGS__, FOR, REP)(__VA_ARGS__)
#define rrep(...) __GET_MACRO3(__VA_ARGS__, RFOR, RREP)(__VA_ARGS__)
#define pb push_back
#define eb emplace_back
#define all(a) begin(a),end(a)
#define chmin(x,v) x = min(x, v)
#define chmax(x,v) x = max(x, v)
#define min(x,y) (x < y ? x : y)
#define max(x,y) (x < y ? y : x)
template<typename Head> void out(Head h) { cout << h << endl; } template<typename Head, typename... Tail>void out(Head h, Tail... t) { cout << h << " "; out(t...); }
template<typename T> istream& operator>>(istream& is, vector<T>& v) { each(x,v) is >> x; return is; }
template<typename T> ostream& operator<<(ostream& os, const vector<T>& v) { rep(i,v.size()) { if (i) os << " "; os << v[i]; } return os; }
template<typename T> ostream& operator<<(ostream& os, const vector<string>& v) { rep(i,v.size()) { if (i) os << endl; os << v[i]; } return os; }
template<typename T> ostream& operator<<(ostream& os, const vector<vector<T>>& v) { rep(i,v.size()) { if (i) os << endl; os << v[i]; } return os; }
struct yes_no : std::numpunct<char> { string_type do_truename() const { return "Yes"; } string_type do_falsename() const { return "No"; } };
void solve(); int main() {
  ios::sync_with_stdio(false); cin.tie(0); locale loc(locale(), new yes_no); cout.imbue(loc); cout << fixed << setprecision(10) << boolalpha;
  solve();
}
// ^^^^^^^^^^^^ TEMPLATE ^^^^^^^^^^^^

#include "../lib/min_cost_flow.cpp"

void solve() {
  ll n, m, F; cin >> n >> m >> F;
  ll s = 0, t = n-1;
  MinCostFlow f(n);
  rep(i, m) {
    ll a, b, c, d; cin >> a >> b >> c >> d;
    f.add(a, b, c, d);
  }
  ll ans = f.min_cost_flow(s, t, F);
  if (ans < 0) cout << -1 << endl;
  else cout << ans << endl;
}
