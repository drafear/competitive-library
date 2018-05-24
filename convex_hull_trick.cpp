// 傾き単調減少
// getクエリ単調増加
class ConvexHull {
    deque<ll> a, b;
    bool check(ll f1, ll f2, ll aa, ll bb) {
        return (a[f2] - a[f1]) * (bb - b[f2]) >= (b[f2] - b[f1]) * (aa - a[f2]);
    }
    ll f(ll fid, ll x) {
        return a[fid] * x + b[fid];
    }
public:
    void add(ll aa, ll bb) {
        while (a.size() >= 2 && check(a.size()-2, a.size()-1, aa, bb)) {
            a.pop_back();
            b.pop_back();
        }
        a.push_back(aa);
        b.push_back(bb);
    }
    ll get_min(ll x) {
        while (a.size() >= 2 && f(0, x) >= f(1, x)) {
            a.pop_front();
            b.pop_front();
        }
        return a[0] * x + b[0];
    }
};
