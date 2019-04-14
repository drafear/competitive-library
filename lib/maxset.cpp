// スライド最小値
template<typename Op>
class SlideMin {
  using T = typename Op::type;
  using P = pair<T, ll>;
  deque<P> deq;
public:
  SlideMin() {}
  T get() {
    if (deq.size() == 0) return Op::id();
    return deq.front().first;
  }
  // 値x, 時刻t
  void add(T x, ll t) {
    if (deq.size() > 0) assert(t >= deq.back().second);
    while (deq.size() > 0 && !Op::ord(deq.back().first, x)) {
      deq.pop_back();
    }
    deq.eb(move(x), t);
  }
  // t未満削除
  ll erase(ll t) {
    while (deq.size() > 0 && deq.front().second < t) {
      deq.pop_front();
    }
  }
  const deque<P>& deque() {
    return deq;
  }
};

struct Min {
  using type = ll;
  static ll id() { return linf; }
  static bool ord(const type& left, const type& right) {
    return left < right;
  }
};
struct Max {
  using type = ll;
  static ll id() { return -linf; }
  static bool ord(const type& left, const type& right) {
    return left > right;
  }
};
