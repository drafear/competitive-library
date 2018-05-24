ll mul(ll a, ll b, ll mod) {
    return a * b % mod;
}
ll add(ll a, ll b, ll mod) {
    return (a + b) % mod;
}
ll sub(ll a, ll b, ll mod) {
    return (a - b + mod) % mod;
}
ll power(ll x, ll n, ll mod) {
    ll res = 1;
    for (ll i = 1; i <= n; i <<= 1) {
        if (i & n) res = mul(res, x, mod);
        x = mul(x, x, mod);
    }
    return res;
}
ll inv(ll n, ll mod) {
    return power(n, mod-2, mod);
}

class RollingHash {
private:
    const ll A, mod;
    const string str;
    vector<ll> hash;
    vector<ll> make_hash(const string& s, const ll A, const ll mod) {
        vector<ll> res(s.size()+1, 0);
        ll coe = 1;
        REP(i, s.size()) {
            hash[i+1] = add(hash[i], mul(coe, s[i], mod), mod);
            coe = mul(coe, A, mod);
        }
        return res;
    }
public:
    RollingHash(const string& s, const ll A, const ll mod) : str(s), A(A), mod(mod), hash(make_hash(s, A, mod)) {}
    ll get(ll l, ll r) {
        return mul(sub(hash[r], hash[l], mod), inv(power(A, l, mod), mod), mod);
    }
    bool iseq(ll s1, ll s2, ll len) {
        return get(s1, s1+len) == get(s2, s2+len);
    }
};
