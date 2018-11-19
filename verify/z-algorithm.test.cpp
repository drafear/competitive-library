/*==start==
judge: atcoder
contest_name: yahoo-procon2018-final
task_name: yahoo_procon2018_final_d
==end==*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> P;

#define each(i,a) for (auto&& i : a)
#define FOR(i,a,b) for (ll i=(a),__last_##i=(b);i<__last_##i;i++)
#define RFOR(i,a,b) for (ll i=(b)-1,__last_##i=(a);i>=__last_##i;i--)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)
#define __GET_MACRO3(_1, _2, _3, NAME, ...) NAME
#define rep(...) __GET_MACRO3(__VA_ARGS__, FOR, REP)(__VA_ARGS__)
#define rrep(...) __GET_MACRO3(__VA_ARGS__, RFOR, RREP)(__VA_ARGS__)
#define pb push_back
#define all(a) (a).begin(),(a).end()
#define chmin(x,v) x = min(x, v)
#define chmax(x,v) x = max(x, v)

const ll linf = 1e18;
const double eps = 1e-12;
const double pi = acos(-1);

template<typename T>
istream& operator>>(istream& is, vector<T>& vec) {
    each(x,vec) is >> x;
    return is;
}
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& vec) {
    rep(i,vec.size()) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, const vector< vector<T> >& vec) {
    rep(i,vec.size()) {
        if (i) os << endl;
        os << vec[i];
    }
    return os;
}

#include "../lib/z-algorithm.cpp"
#include "../lib/unionfind.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  const ll M = 20;
  ll n; cin >> n;
  vector<ll> l(n); cin >> l;
  vector<UnionFind> uf(M, UnionFind(n));
  rep(i, n) {
    if (l[i] == 0) continue;
    ll k = 0;
    while ((1LL<<k+1) <= l[i]) ++k;
    ll d = l[i] - (1LL<<k);
    // cout << k << " " << l[i] << " " << d << endl;
    assert(0 <= d && d < (1LL<<k));
    uf[k].unite(0, n-i-1);
    uf[k].unite(d, n-i-1+d);
  }
  rrep(i, 1, M) rep(j, n) {
    uf[i-1].unite(j, uf[i].root(j));
    // if (j != uf[i].root(j)) cout << i-1 << " " << j << " " << uf[i].root(j) << endl;
    ll u = j+(1LL<<i-1), v = uf[i].root(j)+(1LL<<i-1);
    if (u < n && v < n) {
      // cout << i-1 << " " << u << " " << v << endl;
      uf[i-1].unite(u, v);
    }
  }
  vector<ll> s(n);
  rep(i, n) s[i] = uf[0].root(i);
  vector<ll> Z = Z_algorithm(all(s));
  reverse(all(Z));
  if (Z == l) {
    cout << "Yes" << endl;
  }
  else {
    cout << "No" << endl;
  }
}
