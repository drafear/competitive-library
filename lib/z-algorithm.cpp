template<class ForwardIterator>
vector<ll> Z_algorithm(ForwardIterator first, ForwardIterator last) {
  const ll n = last - first;
  vector<ll> Z(n, 0);
  ll left = 0;
  rep(i, 1, n) {
    ll right = left + Z[left];
    if (i < right && Z[i - left] < right - i) {
      Z[i] = Z[i - left];
    }
    else {
      left = i;
      chmax(right, left);
      while (right < n && *(first + right - i) == *(first + right)) {
        ++right;
      }
      Z[i] = right - i;
    }
  }
  Z[0] = n;
  return Z;
}
vector<ll> Z_algorithm(const string& s) {
  return Z_algorithm(all(s));
}
