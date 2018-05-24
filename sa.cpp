class SuffixArray {
    const ll n;
    const string str;
    vector<ll> sa, lcp;
public:
    SuffixArray(const string& s) : str(s), n(s.size()) {}
    vector<ll> make_sa() {
        sa.assign(n+1, 0);
        rep(i, n+1) sa[i] = i;
        vector<ll> rank(all(str));
        rank.pb(-1);
        auto f = [&](ll idx, ll len) {
            return idx + len <= n ? rank[idx+len] : -1;
        };
        for (ll k = 1; k <= n; k <<= 1) {
            auto compare = [&](ll a, ll b) {
                if (rank[a] != rank[b]) return rank[a] < rank[b];
                else return f(a, k) < f(b, k);
            };
            sort(all(sa), compare);
            vector<ll> nrank(n+1, 0);
            rep(i, 1, n+1) {
                nrank[sa[i]] = nrank[sa[i-1]] + compare(sa[i-1], sa[i]);
            }
            rank = nrank;
        }
        return sa;
    }
    vector<ll> make_lcp() {
        assert(sa.size() > 0);
        lcp.assign(sa.size(), 0);
        vector<ll> rank(n+1);
        rep(i, n+1) rank[sa[i]] = i;
        ll h = 0;
        rep(i, n) {
            if (h > 0) --h;
            assert(rank[i] > 0);
            for (ll j = sa[rank[i]-1]; j + h < n && i + h < n; h++) {
                if (str[j+h] != str[i+h]) break;
            }
            lcp[rank[i]-1] = h;
        }
        return lcp;
    }
    vector<ll> search(const string& s) {
        assert(lcp.size() > 0);
        ll l = -1, r = -1;
        {
            ll lb = 0, ub = n+1;
            while (ub - lb > 1) {
                ll mid = (lb + ub) / 2;
                if (str.substr(sa[mid], s.size()) >= s) {
                    ub = mid;
                }
                else {
                    lb = mid;
                }
            }
            l = ub;
        }
        {
            ll lb = 0, ub = n+1;
            while (ub - lb > 1) {
                ll mid = (lb + ub) / 2;
                if (str.substr(sa[mid], s.size()) > s) {
                    ub = mid;
                }
                else {
                    lb = mid;
                }
            }
            r = ub;
        }
        vector<ll> res;
        if (str.substr(sa[l], s.size()) == s) {
            rep(i, l, r) {
                res.pb(sa[i]);
            }
        }
        return res;
    }
};
