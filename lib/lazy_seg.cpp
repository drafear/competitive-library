template<typename Struct>
class SegmentTreeLazy {
public:
  using Monoid = typename Struct::Monoid;
  using Update = typename Struct::Update;
  using value_type = typename Struct::value_type;
  using update_type = typename Struct::update_type;

private:
  const int n;
  std::vector<value_type> data;
  std::vector<update_type> lazy;
  std::vector<bool> flag;
  int log2ceil(int n) {
    --n;
    n |= n >> 16;
    n |= n >> 8;
    n |= n >> 4;
    n |= n >> 2;
    n |= n >> 1;
    return n + 1;
  }
  void lazyset(int node, const update_type &update) {
    if (node < n) {
      if (flag[node]) {
        lazy[node] = Update::op(update, lazy[node]);
      }
      else {
        lazy[node] = update;
        flag[node] = true;
      }
    }
    data[node] = Struct::evaluate(update, data[node]);
  }
  void evaluate(int node) {
    if (!flag[node]) return;
    flag[node] = false;
    lazyset(node * 2 + 0, lazy[node]);
    lazyset(node * 2 + 1, lazy[node]);
  }
  void update_sub(int l, int r, int node, int lb, int ub,
                  const update_type &update) {
    if (ub <= l || r <= lb) {
      return;
    }
    if (l <= lb && ub <= r) {
      lazyset(node, update);
      return;
    }
    evaluate(node);
    const int mid = (lb + ub) / 2;
    update_sub(l, r, node * 2 + 0, lb, mid, update);
    update_sub(l, r, node * 2 + 1, mid, ub, update);
    data[node] = Monoid::op(data[node * 2 + 0], data[node * 2 + 1]);
  }
  value_type query_sub(int l, int r, int node, int lb, int ub) {
    if (ub <= l || r <= lb) return Monoid::id();
    if (l <= lb && ub <= r) {
      return data[node];
    }
    evaluate(node);
    const int mid = (lb + ub) / 2;
    value_type lval = query_sub(l, r, node * 2 + 0, lb, mid);
    value_type rval = query_sub(l, r, node * 2 + 1, mid, ub);
    return Monoid::op(lval, rval);
  }

public:
  SegmentTreeLazy(int count, const value_type &init = Monoid::id()) :
    n(log2ceil(count)), data(n * 2), lazy(n), flag(n, false) {
    fill(begin(data) + n, end(data), init);
    for (int i = n - 1; i >= 1; i--) {
      data[i] = Monoid::op(data[i * 2 + 0], data[i * 2 + 1]);
    }
  };
  SegmentTreeLazy(const vector<value_type> &init) :
    n(log2ceil(int(init.size()))), data(n * 2), lazy(n), flag(n, false) {
    rep(i, init.size()) data[n+i] = init[i];
    fill(begin(data) + n + init.size(), end(data), Monoid::id());
    for (int i = n - 1; i >= 1; i--) {
      data[i] = Monoid::op(data[i * 2 + 0], data[i * 2 + 1]);
    }
  };
  void update(int l, int r, const update_type &f) {
    update_sub(l, r, 1, 0, n, f);
  }
  value_type query(int l, int r) { return query_sub(l, r, 1, 0, n); }
  value_type find(int l, int r) { return query(l, r); }
};

array<ll, 10> zero = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

struct Node {
  using value_type = array<ll, 10>;
  using update_type = array<ll, 10>;
  struct Monoid {
    static value_type id() { return zero; }
    static value_type op(const value_type& l, const value_type& r) {
      value_type res;
      rep(i, 10) {
        res[i] = l[i] + r[i];
      }
      return res;
    }
  };
  struct Update {
    static update_type op(const update_type& update_new, const update_type& update_old) {
      update_type res;
      rep(i, 10) {
        res[i] = update_new[update_old[i]];
      }
      return res;
    }
  };
  static value_type evaluate(const update_type& update, const value_type& value) {
    array<ll, 10> res = zero;
    rep(i, 10) {
      res[update[i]] += value[i];
    }
    return res;
  }
};

// struct MulSum {
//   using value_type = ll;
//   using update_type = P;
//   struct Monoid {
//     static value_type id() { return 0; }
//     static value_type op(const value_type& l, const value_type& r) {
//       return add(l, r);
//     }
//   };
//   struct Update {
//     static update_type op(const update_type& update_new, const update_type& update_old) {
//       if (update_new.first == 0) {
//         return update_new;
//       }
//       return P(update_old.first, mul(update_old.second, update_new.second));
//     }
//   };
//   static value_type evaluate(const update_type& update, const value_type& value) {
//     if (update.first == 0) {
//       return update.second;
//     }
//     return mul(value, update.second);
//   }
// };
