template<typename Abel, typename Data>
class QueryTree {
    using Result = decltype(declval<Abel>().get_result());
    const int n0, n;
    int pos;
    map<Data, stack<int>> left;
    vector<vector<Data>> data;
    int expand(int m) const { return m == 1 ? m : expand((m + 1) / 2) * 2; }
    void add(int l, int r, const Data& dt) {
        l += n; r += n;
        while (l != r) {
            if (l % 2) { data[l++].push_back(dt); }
            if (r % 2) { data[--r].push_back(dt); }
            l /= 2; r /= 2;
        }
    }
    void dfs(Abel& abel, vector<Result>& res, int l, int r, int v) {
        each(dt, data[v]) abel.add(dt);
        if (r-l > 1) {
            int m = (l + r) / 2;
            dfs(abel, res, l, m, v * 2 + 0);
            dfs(abel, res, m, r, v * 2 + 1);
        }
        else if (res.size() < n0) {
            res.push_back(abel.get_result());
        }
        each(dt, data[v]) abel.undo();
    }
public:
    QueryTree(ll query_num) : pos(0), n0(query_num), n(expand(query_num)), data(2 * expand(query_num)) {}
    void add(const Data& dt) {
        left[dt].push(pos++);
    }
    void remove(const Data& dt) {
        assert(!left[dt].empty());
        add(left[dt].top(), pos++, dt);
        left[dt].pop();
    }
    vector<Result> get_result() {
        each(p, left) {
            while (!p.second.empty()) {
                add(p.second.top(), pos, p.first);
                p.second.pop();
            }
        }
        left.clear();
        Abel abel;
        vector<Result> res;
        dfs(abel, res, 0, n, 1);
        return res;
    }
};
// requirements: 交換法則
struct Min {
    stack<ll> S;
    Min() {
        S.push(linf);
    }
    void add(ll data) {
        S.push(min(S.top(), data));
    }
    void undo() {
        S.pop();
    }
    ll get_result() {
        return S.top();
    }
};

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(0);
//     ll Q; cin >> Q;
//     QueryTree<Min, ll> qt(7);
//     qt.add(50);
//     qt.add(10);
//     qt.add(20);
//     qt.add(10);
//     qt.remove(10);
//     qt.remove(10);
//     qt.remove(50);
//     cout << qt.get_result() << endl;
// }
