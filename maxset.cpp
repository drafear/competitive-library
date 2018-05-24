class MaxSet {
    deque<P> deq;
public:
    MaxSet() {}
    ll get() {
        if (deq.size() == 0) return -linf;
        return deq.front().first;
    }
    // 値x, 時刻t
    ll add(ll x, ll t) {
        if (deq.size() > 0) assert(t > deq.back().second);
        while (deq.size() > 0 && deq.back().first <= x) {
            deq.pop_back();
        }
        deq.push_back(P(x, t));
    }
    // t未満削除
    ll erase(ll t) {
        while (deq.size() > 0 && deq.front().second < t) {
            deq.pop_front();
        }
    }
};
