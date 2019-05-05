// クエリが単調増加でなくてもok
class CHT {
public:
// first * x + second
  vector<P> deq;
  ll s,t;
  // n : クエリ数
  CHT(ll n) {
    deq.resize(n);
    s=0, t=0;
  }
  // a : 単調減少
  // ax + b
  void add(ll a, ll b) {
    const P p(a,b);
    while(s+1<t && check(deq[t-2],deq[t-1],p)) t--;
    deq[t++] = p;
  }
  // x 単調増加
  ll incl_query(ll x) {
    while(s+1<t && f(deq[s], x) >= f(deq[s+1], x)) s++;
    return f(deq[s], x);
  }
  // 条件なし
  ll query(ll x) {
    ll low = s-1, high = t-1;
    while(low+1<high) {
      ll mid = low+high>>1;
      if (isright(deq[mid], deq[mid+1], x)) low = mid;
      else high = mid;
    }
    return f(deq[high], x);
  }
private:
  bool isright(const P &p1, const P &p2, ll x) {
    return (p1.second-p2.second) >= x * (p2.first-p1.first);
  }
  bool check(const P &p1, const P &p2, const P &p3) {
    return (p2.first-p1.first)*(p3.second-p2.second) >=
      (p2.second-p1.second)*(p3.first-p2.first);
  }
  ll f(const P &p, ll x) {
    return p.first * x + p.second;
  }
};
