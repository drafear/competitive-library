class Segtree {
  struct Node {
    Node *lch, *rch;
    ll lb, ub, x, sum;
    Node() : x(0), sum(0), lch(nullptr), rch(nullptr) {
    }
    Node(ll lb, ll ub) : x(0), sum(0), lch(nullptr), rch(nullptr), lb(lb), ub(ub) {}
    ~Node() {
      if (lch != nullptr) delete lch;
      if (rch != nullptr) delete rch;
    }
    ll add(ll l, ll r, ll val) {
      if (r <= lb || ub <= l) return sum + x * (ub - lb);
      if (l <= lb && ub <= r) {
        x += val;
      }
      else {
        ll mid = (lb + ub) / 2;
        if (lch == nullptr) lch = new Node(lb, mid);
        if (rch == nullptr) rch = new Node(mid, ub);
        sum = lch->add(l, r, val) + rch->add(l, r, val);
      }
      return x * (ub - lb);
    }
    ll find(ll l, ll r) {
      if (r <= lb || ub <= l) return 0;
      if (l <= lb && ub <= r) {
        return sum + x * (ub - lb);
      }
      else {
        ll mid = (lb + ub) / 2;
        ll res = x * (min(ub, r) - max(lb, l));
        if (lch != nullptr) res += lch->find(l, r);
        if (rch != nullptr) res += rch->find(l, r);
        return res;
      }
    }
  };
  Node *root;
public:
  Segtree() : Segtree(0) {}
  Segtree(ll n) : root(new Node(0, n)) {}
  void add(ll l, ll r, ll val) {
    root->add(l, r, val);
  }
  ll find(ll l, ll r) {
    return root->find(l, r);
  }
};
