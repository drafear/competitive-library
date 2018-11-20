// shared_ptr使っているので低速
struct po {
  int index;
  vector<int> coors;
  po(int _d):coors(_d) {
    index = -1;
  }
  po() {}
};
template<class T>
class axisSorter {
  int k;
public:
  axisSorter(int _k) : k(_k) {}
  bool operator()(const T &a, const T &b) {
    return a.coors[k] < b.coors[k];
  }
};
long long int getdis(const po&l, const po&r) {
  long long int dis = 0;
  for (int i = 0; i < l.coors.size(); ++i) {
    dis += (l.coors[i] - r.coors[i])*(l.coors[i] - r.coors[i]);
  }
  return dis;
}
template<class T, int Dim = 2>
struct kdtree {
public:
  T val;
  shared_ptr<kdtree<T>> ltree, rtree;
  int depth;
  int axis;
  kdtree(const T &p_) :val(p_), ltree(nullptr), rtree(nullptr) {

  }

  kdtree(vector<T>&ps_, const int& l, const int& r, const int depth_ = 0) : ltree(nullptr), rtree(nullptr), depth(depth_), axis(depth%Dim) {
    init(ps_, l, r);
  }
~kdtree() {
  if (ltree != nullptr)	delete(ltree);

  if (rtree != nullptr)delete(rtree);
}
//直方体内にある点の数を求める。
  vector<T>query(const T & amin, const T&amax) {
    vector<T>ans;
    bool aok = true;
    for (int i = 0; i < Dim; ++i) {
      if (amin.coors[i] <= val.coors[i] && val.coors[i] <= amax.coors[i]) {

      }
      else {
        aok = false;
        break;
      }
    }
    if (aok) {
      ans.emplace_back(val);
    }
    axisSorter<T> as(axis);
    if (as(val, amax) || val.coors[axis] == amax.coors[axis]) {
      if (rtree != nullptr) {
        vector<T>tans(rtree->query(amin, amax));
        ans.insert(ans.end(), tans.begin(), tans.end());
      }
    }
    if (as(amin, val) || val.coors[axis] == amin.coors[axis]) {
      if (ltree != nullptr) {
        vector<T>tans(ltree->query(amin, amax));
        ans.insert(ans.end(), tans.begin(), tans.end());
      }
    }
    return ans;
  }
// 最近傍点を求める。
void get_closest(const T& apo, long long int &ans) {
  ans = min(ans, getdis(apo, val));
  axisSorter<T> as(axis);
  if (as(apo, val) || val.coors[axis] == apo.coors[axis]) {
    if (ltree)ltree->get_closest(apo, ans);
    long long int dis = apo.coors[axis] - val.coors[axis];
    if (dis*dis >= ans)return;
    else {
      if (rtree)rtree->get_closest(apo, ans);
    }
  }
  else {
    if (rtree)rtree->get_closest(apo, ans);
    long long int dis = val.coors[axis] - apo.coors[axis];
    if (dis*dis >= ans)return;
    else {
      if (ltree)ltree->get_closest(apo, ans);
    }
  }
}
private:
  void init(vector<T>&ps, const int& l, const int& r) {
    if (l >= r) {
      return;
    }
    const int mid = (l + r) / 2;
    nth_element(ps.begin() + l, ps.begin() + mid, ps.begin() + r, axisSorter<T>(axis));
    val = ps[mid];
    ltree = make_kdtree(ps, l, mid, depth + 1);
    rtree = make_kdtree(ps, mid + 1, r, depth + 1);
  }

};
//[l..r)
template<class T>
unique_ptr<kdtree<T>>make_kdtree(vector<T>&ps_, const int& l, const int& r, const int& depth = 0) {
  if (l >= r)return nullptr;
  else {
    return make_unique<kdtree<T>>(ps_, l, r, depth);
  }
}
