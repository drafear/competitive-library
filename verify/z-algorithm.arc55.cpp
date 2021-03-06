/*==start==
judge: atcoder
contest_name: arc055
task_name: arc055_c
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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string s; cin >> s;
  const ll n = s.size();
  string rs = s;
  reverse(all(rs));
  vector<ll> Z = Z_algorithm(s);
  vector<ll> rZ = Z_algorithm(rs);
  ll ans = 0;
  rep(i, 1, n) {
    ll AClen = n-i;
    if (i <= AClen) continue;
    if (AClen < 2) continue;
    ll left = min(AClen-1, Z[i]);
    ll right = min(AClen-1, rZ[n-i]);
    if (left + right >= AClen) {
      ans += left + right - AClen + 1;
      // cout << i << " " << left << " " << right << " " << AClen << " " << left+right-AClen+1 << endl;
    }
  }
  cout << ans << endl;
}
