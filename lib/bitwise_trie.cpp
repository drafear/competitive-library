class BitwiseTrie {
public:
  struct Node {
    Node *lch, *rch;
    ll cnt;
    Node() : lch(nullptr), rch(nullptr), cnt(0) {}
  };
  ll d;
  Node root;
  BitwiseTrie(ll depth) : d(depth), root() {}
  // add x to the set
  void add(ll x, ll cnt = 1) {
    Node *t = &root;
    rep(i, d) {
      t->cnt += cnt;
      if (x>>(d-i-1) & 1) {
        if (t->rch == nullptr) {
          t->rch = new Node();
        }
        t = t->rch;
      }
      else {
        if (t->lch == nullptr) {
          t->lch = new Node();
        }
        t = t->lch;
      }
    }
    t->cnt += cnt;
  }
  bool has(ll x, ll cnt = 1) {
    Node *t = &root;
    rep(i, d) {
      if (x>>(d-i-1) & 1) t = t->rch;
      else t = t->lch;
      if (t == nullptr || t->cnt < cnt) return false;
    }
    return true;
  }
  // remove x from the set if it exists
  void erase(ll x, ll cnt = 1) {
    if (!has(x, cnt)) return;
    add(x, -cnt);
  }
  // find y such that (x XOR y) is minumum for all y in the set
  ll find_min(ll x) {
    Node *t = &root;
    ll res = x;
    rep(i, d) {
      Node *l = t->lch, *r = t->rch;
      if (x>>(d-i-1) & 1) {
        swap(l, r);
      }
      if (l != nullptr && l->cnt > 0) t = l;
      else t = r, res ^= 1LL<<(d-i-1);
    }
    return res;
  }
  ll find_max(ll x) {
    return find_min(x ^ (1LL<<d)-1);
  }
};
