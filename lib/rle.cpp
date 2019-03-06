// ランレングス圧縮
vector<pair<char, int>> rle(string s) {
  char prev = '\0';
  int cnt = 0;
  vector<pair<char, int>> res;
  REP(i, s.size()+1) {
    if (i == s.size() || s[i] != prev) {
      if (prev != '\0') {
        res.pb({prev, cnt});
      }
      prev = s[i];
      cnt = 1;
    }
    else {
      ++cnt;
    }
  }
  return res;
}
