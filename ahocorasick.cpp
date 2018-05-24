class AhoCorasick {
    vector<map<char, int>> G;
    vector<int> failure;
    vector<vector<int>> pattern;
    int fresh_node() {
        const int res = G.size();
        G.resize(res+1);
        pattern.pb(vector<int>());
        return res;
    }
    int follow(int v, char c) const {
        while (v >= 0 && G[v].count(c) == 0) {
            v = failure[v];
        }
        return v < 0 ? 0 : G[v].find(c)->second;
    }
    void generate_trie(const vector<string>& patterns) {
        rep(i, patterns.size()) {
            int v = 0;
            each(c, patterns[i]) {
                if (G[v].count(c) == 0) {
                    G[v][c] = fresh_node();
                }
                v = G[v][c];
            }
            pattern[v].pb(i);
        }
        G.reserve(size());
        pattern.reserve(size());
    }
    void add_failure_edge() {
        queue<int> Q; Q.push(0);
        failure.reserve(size());
        failure.assign(size(), -1);
        while ( !Q.empty() ) {
            int v = Q.front(); Q.pop();
            each(p, G[v]) {
                char c; int to; tie(c, to) = p;
                Q.push(p.second);
                failure[to] = follow(failure[v], c);
            }
        }
    }
public:
    AhoCorasick(const vector<string>& patterns) : G(1), pattern(1) {
        generate_trie(patterns);
        add_failure_edge();
    }
    size_t size() const {
        return G.size();
    }
    pair<int, vector<int>> find(int v, char c) const {
        vector<int> res;
        v = follow(v, c);
        int now = v;
        while (now >= 0) {
            copy(all(pattern[now]), back_inserter(res));
            now = failure[now];
        }
        return {v, res};
    }
    pair<int, vector<P>> find(const string& s) const {
        vector<P> res;
        int v = 0;
        rep(i, s.size()) {
            auto result = find(v, s[i]);
            v = result.first;
            each(pid, result.second) {
                res.pb({i, pid});
            }
        }
        return {v, res};
    }
};
