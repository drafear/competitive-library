constexpr ll mod = 1e9+7;
constexpr ll mul(ll a, ll b) { return a * b % mod; }
ll mul(initializer_list<ll> t) { ll res = 1; each(v, t) res = mul(res, v); return res; }
ll add(ll a, ll b) { return (a + b) % mod; }
ll add(initializer_list<ll> t) { ll res = 0; each(v, t) res = add(res, v); return res; }
ll sub(ll a, ll b) { return (a - b + mod) % mod; }
ll sub(initializer_list<ll> t) { auto it = t.begin(); ll res = *(it++); while (it != t.end()) res = sub(res, *(it++)); return res; }
ll inv(ll n); ll power(ll x, ll n) { if (n < 0) return inv(power(x, -n)); ll res = 1; for (ll i = 1; i <= n; i <<= 1) { if (i & n) res = mul(res, x); x = mul(x, x); } return res; }
ll inv(ll n) { return power(n, mod-2); }
ll divi(ll a, ll b) { return mul(a, inv(b)); }
ll divi(initializer_list<ll> t) { auto it = t.begin(); ll res = *(it++); while (it != t.end()) res = divi(res, *(it++)); return res; }
vector<ll> fact, rfact;
void init_fact(ll n) { fact.resize(n+1); fact[0] = 1; rep(i, n) fact[i+1] = mul(fact[i], i+1); rfact.resize(n+1); rfact[n] = inv(fact[n]); rrep(i, n) rfact[i] = mul(rfact[i], i+1); }
ll comb(ll n, ll r) { if (r < 0) return 0; if (r > n) return 0; return divi(fact[n], mul(fact[r], fact[n-r])); }
ll perm(ll n, ll r) { if (r < 0) return 0; if (r > n) return 0; return divi(fact[n], fact[n-r]); }

using Row = vector<ll>;
using Matrix = vector<Row>;
Matrix E(ll n) { Matrix res(n, Row(n, 0)); rep(i, n) res[i][i] = 1; return res; }
Matrix mul(const Matrix& A, const Matrix& B) { const ll n = A.size(), m = A[0].size(), l = B[0].size(); assert(m == B.size()); Matrix res(n, Row(l, 0)); rep(i, n) rep(j, m) rep(k, l) res[i][k] = add(res[i][k], mul(A[i][j], B[j][k])); return res; }
Row mul(const Matrix& A, const Row& x) { Matrix tx(x.size()); rep(i, x.size()) tx[i] = Row(1, x[i]); tx = mul(A, tx); Row res(x.size()); rep(i, x.size()) res[i] = tx[i][0]; return res; }
Matrix power(Matrix A, ll n) { assert(A.size() == A[0].size()); Matrix res = E(A.size()); for (ll i = 1; i <= n; i <<= 1) { if (i & n) res = mul(res, A); A = mul(A, A); } return res; }
