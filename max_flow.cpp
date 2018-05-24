class MaxFlow {
public:
    struct Edge {
        ll to, cap, rev;
    };
    vector<vector<Edge>> G;
    vector<ll> iter;
private:
    bool is_debug;
    ll V;
    vector<ll> bfs(ll s) {
        vector<ll> dist(V, linf);
        dist[s] = 0;
        queue<ll> Q; Q.push(s);
        while ( !Q.empty() ) {
            ll v = Q.front(); Q.pop();
            each(e, G[v]) {
                if (e.cap > 0 && dist[e.to] == linf) {
                    dist[e.to] = dist[v]+1;
                    Q.push(e.to);
                }
            }
        }
        return dist;
    }
    ll dfs(ll v, ll t, ll f, const vector<ll>& dist, vector<bool>& used) {
        if (v == t) return f;
        if (used[v]) return 0;
        used[v] = true;
        for (ll& i = iter[v]; i < G[v].size(); ++i) {
            Edge& e = G[v][i];
            if (e.cap > 0 && dist[e.to] == dist[v]+1) {
                ll d = dfs(e.to, t, min(f, e.cap), dist, used);
                if (d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
public:
    const vector<vector<Edge>> Graph() {
        return G;
    }
    MaxFlow(ll V, bool is_debug=false) : V(V), G(V), is_debug(is_debug) {}
    void init(ll n) {
        V = n;
        G.assign(V, vector<Edge>());
    }
    void add(ll from, ll to, ll cap) {
        if (is_debug) cout << "ADD: " << from << " " << to << " " << cap << endl;
        assert(V > 0);
        G[from].pb({to, cap, (ll)G[to].size()});
        G[to].pb({from, 0, (ll)G[from].size()-1});
    }
    // S -> s, T -> t に inf は自力で
    void add(ll from, ll to, ll min_flow, ll cap, ll S, ll T) {
        if (is_debug) cout << endl << "ADD_MIN:" << from << " " << to << " " << min_flow << " " << cap << endl;
        add(from, to, cap-min_flow);
        add(S, to, min_flow);
        add(from, T, cap);
        if (is_debug) cout << endl;
    }
    ll flow(ll s, ll t, ll f=linf) {
        ll res = 0;
        while (f > 0) {
            vector<ll> dist = bfs(s);
            if (dist[t] == linf) break;
            iter.assign(G.size(), 0);
            while (f > 0) {
                vector<bool> used(V, false);
                ll df = dfs(s, t, f, dist, used);
                if (df == 0) break;
                f -= df;
                res += df;
            }
        }
        return res;
    }
};