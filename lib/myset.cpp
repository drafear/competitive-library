template<class Type>
class Set {
  using T = typename Type::type;
  using Int = typename Type::counting_type;
  const Type t;
  struct Node {
    Int sum;
    Node *lch, *rch;
    Node(Int sum = Int(0), Node* lch = nullptr, Node* rch = nullptr) : sum(sum), lch(lch), rch(rch) {}
    ~Node() {
      if (lch != nullptr) delete lch;
      if (rch != nullptr) delete rch;
    }
    void clear_childs() {
      if (lch != nullptr) {
        delete lch;
        lch = nullptr;
      }
      if (rch != nullptr) {
        delete rch;
        rch = nullptr;
      }
    }
    Node* left() {
      if (lch == nullptr) lch = new Node();
      return lch;
    }
    Node* right() {
      if (rch == nullptr) rch = new Node();
      return rch;
    }
  };
  Int sz;
  int depth;
  Node *root;
  void expand(const Int& val) {
    while (sz <= val) {
      sz <<= 1;
      ++depth;
      root = new Node(root->sum, root, nullptr);
    }
  }
  void insert_(const Int& val) {
    if (count_(val, val+1) == Int(1)) return;
    expand(val);
    Node *node = root;
    Int lb(0), ub = sz;
    for (int i = 0; i < depth; ++i) {
      Int mid = (lb + ub) / 2;
      ++node->sum;
      if (val < mid) {
        ub = move(mid);
        node = node->left();
      }
      else {
        lb = move(mid);
        node = node->right();
      }
    }
    node->sum = Int(1);
  }
  void erase_(const Int& val) {
    if (count_(val, val+1) == Int(0)) return;
    Node *node = root;
    Int lb(0), ub = sz;
    for (int i = 0; i < depth; ++i) {
      Int mid = (lb + ub) / 2;
      if (--node->sum == Int(0)) {
        node->clear_childs();
        return;
      }
      if (val < mid) {
        ub = move(mid);
        node = node->lch;
      }
      else {
        lb = move(mid);
        node = node->rch;
      }
    }
    node->sum = Int(0);
  }
  Int count_left(const Int& search_lb, const Node* node, Int lb, Int ub, int i0) const {
    if (node == nullptr) return Int(0);
    Int res(0);
    for (int i = move(i0); i <= depth; ++i) {
      // 完全に一致
      if (lb == search_lb) return res + node->sum;
      Int mid = (lb + ub) / 2;
      // rch は全部含む
      if (mid >= search_lb) {
        if (node->rch != nullptr) res += node->rch->sum;
        ub = move(mid);
        node = node->lch;
      }
      else {
        lb = move(mid);
        node = node->rch;
      }
      if (node == nullptr || ub <= search_lb) return res;
    }
    return res + node->sum;
  }
  Int count_right(const Int& search_ub, const Node* node, Int lb, Int ub, int i0) const {
    if (node == nullptr) return Int(0);
    Int res(0);
    for (int i = move(i0); i <= depth; ++i) {
      // 完全に一致
      if (ub == search_ub) return res + node->sum;
      Int mid = (lb + ub) / 2;
      // lch は全部含む
      if (mid <= search_ub) {
        if (node->lch != nullptr) res += node->lch->sum;
        lb = move(mid);
        node = node->rch;
      }
      else {
        ub = move(mid);
        node = node->lch;
      }
      if (node == nullptr || lb >= search_ub) return res;
    }
    return res + node->sum;
  }
  Int count_(const Int& search_lb, Int search_ub) const {
    if (search_ub > sz) search_ub = sz;
    if (search_lb >= search_ub || search_lb >= sz) return Int(0);
    const Node* node = root;
    Int lb(0), ub = sz;
    // common
    for (int i = 0; i < depth; ++i) {
      Int mid = (lb + ub) / 2;
      if (lb <= search_lb && search_ub <= mid) {
        ub = move(mid);
        node = node->lch;
      }
      else if (mid <= search_lb && search_ub <= ub) {
        lb = move(mid);
        node = node->rch;
      }
      else {
        return count_left(search_lb, node->lch, lb, mid, i+1) + count_right(search_ub, node->rch, mid, ub, i+1);
      }
      if (node == nullptr) return 0;
    }
    return node->sum;
  }
public:
  Set() : t(Type()), sz(1), depth(0), root(new Node()) {}
  Set(Type t) : t(t), sz(1), depth(0), root(new Node()) {}
  ~Set() { delete root; }
  void insert(T val) { insert_(t.nth(val)); }
  void erase(const T& val) { erase_(t.nth(val)); }
  Int count(const T& x) const { return count_(t.nth(x), t.nth(x)+1); }
  Int count(const T& lb, const T& ub) const { return count_(t.nth(lb), t.nth(ub)); }
  T zero_nth(Int n) const {
    const Node* node = root;
    Int lb(0), ub = sz;
    Int rest = (ub - lb) - node->sum;
    if (n >= rest) return t.nth(sz + n - rest);
    for (int i = 0; i < depth; ++i) {
      Int mid = (lb + ub) / 2;
      Int lsum = (mid - lb) - (node->lch == nullptr ? 0 : node->lch->sum);
      if (n >= lsum) {
        n -= lsum;
        node = node->rch;
        lb = move(mid);
      }
      else {
        node = node->lch;
        ub = move(mid);
      }
      if (node == nullptr) return t.nth(lb + n);
    }
    assert(n == Int(0));
    return t.nth(lb);
  }
  void clear() {
    sz = 0;
    root = Node();
  }
  Int size() const { return root->sum; }
};
class Integer {
public:
  using type = long long;
  using counting_type = type;
  type nth(const counting_type& x) const { return x; }
};
class PairSet {
  const int n, m;
  long long f(int n) const {
    return (long long)n * (n+1) / 2;
  }
public:
  using type = pair<int,int>;
  using counting_type = long long;
  PairSet(int n, int m) : n(n), m(m) {}
  counting_type nth(const type& x) const { return f(x.first-1) + x.second; }
  type nth(const counting_type& x) const {
    int lb = 0, ub = (int)1e9;
    for (int t = 0; t < 30; ++t) {
      int mid = (lb + ub) / 2;
      if (f(mid) <= x) lb = mid;
      else ub = mid;
    }
    return type(lb+1, x - f(lb));
  }
};
// [0, n) からランダムに m 個選ぶ
vector<ll> select(ll n, ll m) {
  assert(n >= m);
  Set<Integer> s;
  vector<ll> res(m);
  rep(i, m) {
    ll val = s.zero_nth(rnd.next(n-i));
    res[i] = val;
    s.insert(val);
  }
  return res;
}
