class StarrySkyTree {
  using T = long long;
  const int n;
  vector<T> data, lazy;
  int expand(int m) const { return m == 1 ? m : expand((m + 1) / 2) * 2; }
public:
  StarrySkyTree(int count) : n(expand(count)), data(n * 2, 0), lazy(n * 2, 0) {}
  void add(int l, int r, const T &val) {
    if (l >= r) return;
    l += n; r += n;
    const int left = l, right = r;
    while (l != r) {
      if (l % 2) { lazy[l] += val; data[l++] += val; }
      if (r % 2) { lazy[--r] += val; data[r] += val; }
      l /= 2; r /= 2;
    }
    l = left; r = right - 1;
    while (l /= 2, r /= 2) {
      data[l] = min(data[l * 2], data[l * 2 + 1]) + lazy[l];
      data[r] = min(data[r * 2], data[r * 2 + 1]) + lazy[r];
    }
  }
  T find(int l, int r) const {
    if (l >= r) return linf;
    l += n; r += n;
    T res1 = linf, res2 = linf;
    while (l != r) {
      if (l % 2) res1 = min(res1, data[l++]);
      if (r % 2) res2 = min(res2, data[--r]);
      l /= 2; r /= 2; res1 += lazy[l - 1]; res2 += lazy[r];
    }
    --l;
    while (l /= 2, r /= 2) { res1 += lazy[l]; res2 += lazy[r]; }
    return min(min(res1, res2), linf);
  }
  using value_type = T;
  using update_type = T;
};
