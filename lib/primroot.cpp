ll powmod (ll x, ll n, ll mod) {
  ll res = 1;
  for (ll i = 1; i <= n; i <<= 1) {
    if (n & i) res = res * x % mod;
    x = x * x % mod;
  }
  return res;
}

// 素数pの原始根を求める
ll primroot(ll p) {
  vector<ll> fact;
  ll phi = p-1, n = phi;
  for (ll i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      fact.push_back(i);
      while (n % i == 0) {
        n /= i;
      }
    }
  }
  if (n > 1) fact.push_back(n);
  for (ll res = 2; res <= p; ++res) {
    bool ok = true;
    for (size_t i = 0; i < fact.size() && ok; ++i) {
      ok &= powmod(res, phi / fact[i], p) != 1;
    }
    if (ok) return res;
  }
  return -1;
}
