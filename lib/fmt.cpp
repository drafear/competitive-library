template <int M, bool IsPrime = false> class Modulo {
  int n;
  static typename std::enable_if<IsPrime, ll>::type inv(ll a, ll p) {
    return (a == 1 ? 1 : (1 - p * inv(p % a, a)) / a + p);
  }

public:
  Modulo() : n(0) { ; }
  Modulo(int m) : n(m) {
    if (n >= M)
      n %= M;
    else if (n < 0)
      n = (n % M + M) % M;
  }
  Modulo(ll m) {
    if (m >= M)
      m %= M;
    else if (m < 0)
      m = (m % M + M) % M;
    n = m;
  }
  explicit operator int() const { return n; }
  explicit operator ll() const { return n; }
  bool operator==(const Modulo &a) const { return n == a.n; }
  Modulo &operator+=(const Modulo &a) {
    n += a.n;
    if (n >= M) n -= M;
    return *this;
  }
  Modulo &operator-=(const Modulo &a) {
    n -= a.n;
    if (n < 0) n += M;
    return *this;
  }
  Modulo &operator*=(const Modulo &a) {
    n = (ll(n) * a.n) % M;
    return *this;
  }
  Modulo operator+(const Modulo &a) const {
    Modulo res = *this;
    return res += a;
  }
  Modulo operator-(const Modulo &a) const {
    Modulo res = *this;
    return res -= a;
  }
  Modulo operator-() const { return Modulo(0) - *this; }
  Modulo operator*(const Modulo &a) const {
    Modulo res = *this;
    return res *= a;
  }

  Modulo operator^(ll m) const {
    if (m == 0) return Modulo(1);
    const Modulo a = *this;
    Modulo res = (a * a) ^ (m / 2);
    return m % 2 ? res * a : res;
  }
  typename std::enable_if<IsPrime, Modulo>::type
  operator/(const Modulo &a) const {
    return *this * inv(ll(a), M);
  }
  typename std::enable_if<IsPrime, Modulo>::type operator/=(const Modulo &a) {
    return *this *= inv(ll(a), M);
  }

  friend bool is_zero(const Modulo &x) { return int(x) == 0; }
  friend int abs(const Modulo &x) { return int(x); }

  static Modulo fact(int n, bool sw = true) {
    static std::vector<Modulo> v1 = { 1 }, v2 = { 1 };
    if (n >= (int)v1.size()) {
      const int from = v1.size(), to = n + 1024;
      v1.reserve(to);
      v2.reserve(to);
      for (int i = from; i < to; ++i) {
        v1.push_back(v1.back() * Modulo<M, true>(i));
        v2.push_back(v2.back() / Modulo<M, true>(i));
      }
    }
    return sw ? v1[n] : v2[n];
  }
  static Modulo comb(int a, int b) {
    if (b < 0 || b > a) return 0;
    return Modulo::fact(a, true) * Modulo::fact(b, false) *
           Modulo::fact(a - b, false);
  }
};

template <int prim_root, int mod, int sign>
void FMT(std::vector<Modulo<mod, true>> &a) {
  using mod_t = Modulo<mod, true>;
  const int n = a.size();
  mod_t h = mod_t(prim_root) ^ ((mod - 1) / n);
  if (sign == -1) h = mod_t(1) / h;
  int x = 0;
  for (int i = 1; i < n - 1; ++i) {
    for (int j = n / 2; j > (x ^= j); j /= 2)
      ;
    if (i < x) std::swap(a[x], a[i]);
  }
  for (int m = 1; m < n; m *= 2) {
    const int m2 = 2 * m;
    const mod_t base = mod_t(h) ^ (n / m2);
    mod_t w = 1;
    for (int i = 0; i < m; ++i) {
      for (int j = i; j < n; j += m2) {
        const mod_t u = a[j], d = a[j + m] * w;
        a[j] = u + d;
        a[j + m] = u - d;
      }
      w *= base;
    }
  }
}

template <int prim_root, int mod>
std::vector<Modulo<mod, true>> convolution(std::vector<Modulo<mod, true>> a,
                                           std::vector<Modulo<mod, true>> b) {
  using mod_t = Modulo<mod, true>;
  int size = a.size() + b.size();
  while ((size & -size) != size) size += (size & -size);
  a.resize(size);
  FMT<prim_root, mod, 1>(a);
  b.resize(size);
  FMT<prim_root, mod, 1>(b);
  for (int i = 0; i < size; ++i) a[i] *= b[i];
  FMT<prim_root, mod, -1>(a);
  const mod_t inv = mod_t(1) / mod_t(size);
  for (auto &x : a) x *= inv;
  return a;
}
