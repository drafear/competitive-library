template<typename String>
vector<ll> manachar(const String& s) {
  vector<ll> res(s.size());
  ll i = 0, j = 0;
  while (i < s.size()) {
    while (i-j >= 0 && i+j < s.size() && s[i-j] == s[i+j]) ++j;
    res[i] = j;
    ll k = 1;
    while (i-k >= 0 && i+k < s.size() && k+res[i-k] < j) res[i+k] = res[i-k], ++k;
    i += k; j -= k;
  }
  return res;
}
