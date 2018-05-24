void scc_dfs(ll v, vector<bool>& used, vector<ll>& vs, const vector<vector<ll>>& G) {
    used[v] = true;
    each(to, G[v]) {
        if (!used[to]) scc_dfs(to, used, vs, G);
    }
    vs.pb(v);
}
void scc_rdfs(ll v, ll k, vector<bool>& used, vector<ll>& cmp, const vector<vector<ll>>& rG) {
    used[v] = true;
    cmp[v] = k;
    each(to, rG[v]) {
        if (!used[to]) scc_rdfs(to, k, used, cmp, rG);
    }
}
// cmpが返る
// 同じcmpは強連結成分
// cmp[i] < cmp[j] なら j から i に行けない
vector<ll> scc(const vector<vector<ll>>& G) {
    const ll n = G.size();
    vector<bool> used(n, false);
    vector<ll> vs;
    rep(i, n) {
        if (!used[i]) scc_dfs(i, used, vs, G);
    }
    used.assign(n, false);
    vector< vector<ll> > rG(n);
    rep(i, n) {
        each(to, G[i]) {
            rG[to].pb(i);
        }
    }
    vector<ll> res(n);
    ll k = 0;
    rrep(i, vs.size()) {
        if (!used[vs[i]]) scc_rdfs(vs[i], k++, used, res, rG);
    }
    return res;
}
vector<vector<ll>> get_scc_graph(const vector<ll>& cmp, const vector<vector<ll>>& G) {
    vector<vector<ll>> res(*max_element(all(cmp))+1);
    rep(i, G.size()) {
        each(to, G[i]) {
            if (cmp[i] != cmp[to]) {
                res[cmp[i]].pb(cmp[to]);
            }
        }
    }
    rep(i, res.size()) {
        sort(all(res[i]));
        res[i].erase(unique(all(res[i])), res[i].end());
    }
    return res;
}
