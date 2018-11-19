template<typename Weight>
class Graph {
  bool is_directed;
  ll next_eid;
  vector<ll> G;
  struct Edge {
    ll id, from, to;
    Weight cost;
  };
public:
  Graph() : next_eid(0), is_directed(true) {}
  Graph(size_t size, bool is_directed=true) : G(size), next_eid(0), is_directed(is_directed) {}
  size_t size() const { return G.size(); }
  const vector<Edge>& operator[](ll idx) const {
    assert(0 <= idx && idx < G.size());
    return G[idx];
  }
  ll add_node() {
    ll id = G.size();
    G.resize(id+1);
    return id;
  }
  ll add_edge(ll from, ll to, T cost = T(1)) {
    G[from].pb({next_eid, from, to, cost});
    if (!is_directed) {
      G[to].pb({next_eid, to, from, cost});
    }
    return next_eid++;
  }
  // Graph rev() {
  // }
  // Graph tree(ll root) {
  // }
  // vector<T> dijkstra() {
  // }
  // vector<ll> bfs() {
  // }
  // LCA make_lca() {
  // }
};
bool operator<(const Edge& e1, const Graph::Edge& e2) {
  return e1.cost < e2.cost;
}
bool operator>(const Edge& e1, const Graph::Edge& e2) {
  return e2 < e1;
}
