// ランレングス圧縮
vector<pair<char, int>> rle(const string& s) {
  char prv = '\0';
  ll cnt = 0;
  vector<pair<char, int>> res;
  rep(i, s.size()+1) {
    if (i == s.size() || s[i] != prv) {
      if (prv != '\0') {
        res.eb(prv, cnt);
      }
      prv = s[i];
      cnt = 1;
    }
    else {
      ++cnt;
    }
  }
  return res;
}
