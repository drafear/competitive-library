class SegmentManager {
    ll len;
    set<P> s;
    ll length(const P& p) {
        return p.second - p.first;
    }
    set<P>::iterator erase(const set<P>::iterator it) {
        len -= length(*it);
        return s.erase(it);
    }
    void insert(const P& p) {
        len += length(p);
        s.insert(p);
    }
    set<P>::iterator lb(ll l) {
        return s.lower_bound({l, l});
    }
    set<P>::iterator ub(ll l) {
        return lb(l+1);
    }
public:
    SegmentManager() : len(0) {}
    void add(ll l, ll r) {
        if (r <= l) return;
        erase(l, r);
        // merge right
        {
            auto it = lb(r);
            if (it != s.end() && it->first == r) {
                r = it->second;
                erase(it);
            }
        }
        // merge left
        {
            auto it = lb(l);
            if (it != s.begin()) {
                --it;
                if (it->second == l) {
                    l = it->first;
                    erase(it);
                }
            }
        }
        // add
        insert({l, r});
    }
    void erase(ll l, ll r) {
        if (r <= l) return;
        // cut left
        {
            auto it = lb(l);
            if (it != s.begin()) {
                --it;
                if (it->second > l) {
                    insert({it->first, l});
                    if (it->second > r) {
                        insert({r, it->second});
                        erase(it);
                        return;
                    }
                    erase(it);
                }
            }
        }
        auto it = lb(l);
        auto itr = lb(r);
        while (it != itr) {
            if (it->second > r) {
                insert({r, it->second});
                it = erase(it);
                break;
            }
            it = erase(it);
        }
    }
    bool is_in(ll l, ll r) {
        assert(r >= l);
        auto it = ub(l);
        if (it == s.begin()) return false;
        --it;
        return it->first <= l && r <= it->second;
    }
    bool is_in(ll pos) { return is_in(pos, pos+1); }
    ll length() { return len; }
    ll count() { return s.size(); }
    void out() {
        each(p, s) {
            cout << "[" << p.first << ", " << p.second << ")" << endl;
        }
    }
};