class Bit {
    ll n;
    vector<ll> v;
public:
    Bit(ll sz) : n((sz+1)*2), v((sz+1)*2, 0) {}
    // v[pos] += val
    void add(ll pos, ll val) {
        ++pos;
        while (pos < n) {
            v[pos] += val;
            pos += pos & -pos;
        }
    }
    // [l, r)
    ll get(ll l, ll r) {
        return get(r) - get(l);
    }
    // [0, pos)
    ll get(ll pos) {
        ll res = 0;
        while (pos >= 1) {
            res += v[pos];
            if (pos == 0) break;
            pos -= pos & -pos;
        }
        return res;
    }
};