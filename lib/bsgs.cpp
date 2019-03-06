// find min y s.t. g^y % mod = x
class BSGS {
  const ll g, mod;
  vector<pair<ll,ll>> baby;
  ll mul(ll x, ll y) {
    return x * y % mod;
  }
  ll power(ll x, ll n) {
    ll res = 1;
    for (ll i = 1; i <= n; i <<= 1) {
      if (n & i) res = mul(res, x);
      x = mul(x, x);
    }
    return res;
  }
  void init_baby(ll sz) {
    baby.resize(sz);
    baby[0] = make_pair(1LL, 0LL);
    rep(i, 1, sz) {
      baby[i] = P(mul(baby[i-1].first, g), i);
    }
    sort(begin(baby), end(baby));
  }
public:
  // mod must be a prime number
  BSGS(ll g, ll mod, ll baby_size=1000000) : g(g % mod), mod(mod) {
    init_baby(baby_size);
  }
  // find min y s.t. g^y % mod = x /\ lb <= y < ub
  ll find_min(ll x, ll lb, ll ub) {
    assert(0 <= x && x < mod);
    assert(0 <= lb && lb <= ub);
    ll x0 = x;
    ll coe = power(power(g, mod-2), baby.size()); // g^{-baby_size}
    ll i0 = lb/baby.size();
    x = mul(x, power(coe, i0));
    rep(i, i0, ub/baby.size()+1) {
      ll base = i * baby.size();
      auto it = lower_bound(begin(baby), end(baby), make_pair(x, lb - base));
      if (it != end(baby) && it->first == x) {
        ll res = base + it->second;
        if (res < ub) return res;
      }
      x = mul(x, coe);
    }
    return -1;
  }
  // find min y s.t. g^y % mod = x
  ll find_min(ll x) {
    return find_min(x, 0, mod);
  }
};
