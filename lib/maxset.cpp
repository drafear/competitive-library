// スライド最小値
template<typename T>
class SlideMin {
  using P = pair<T, ll>;
  const T id;
  deque<P> deq;
public:
  SlideMin(T id) : id(id) {}
  T get() {
    if (deq.size() == 0) return id;
    return deq.front().first;
  }
  // 値x, 時刻t
  void add(T x, ll t) {
    if (deq.size() > 0) assert(t > deq.back().second);
    while (deq.size() > 0 && deq.back().first >= x) {
      deq.pop_back();
    }
    deq.eush_back(move(x), t);
  }
  // t未満削除
  ll erase(ll t) {
    while (deq.size() > 0 && deq.front().second < t) {
      deq.pop_front();
    }
  }
};
