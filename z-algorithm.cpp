vector<ll> Z_algorithm(const string& s) {
  const ll n = s.size();
  vector<ll> Z(n, 0);
  Z[0] = n;
  ll left = 0, right = 0;
  rep(i, 1, n) {
    if (i > right) {
      left = right = i;
      for (; right < n && s[right - left] == s[right]; right++);
      Z[i] = right - left;
      right--;
    }
    else {
      int k = i - left;
      if (Z[k] < right - i + 1) {
          Z[i] = Z[k];
      }
      else {
        left = i;
        for (; right < n && s[right - left] == s[right]; right++);
        Z[i] = right - left;
        right--;
      }
    }
  }
  return Z;
}
