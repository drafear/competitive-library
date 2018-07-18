template <typename T> struct skew_heap {
  T val;
  skew_heap *l, *r;
  skew_heap() : l(nullptr), r(nullptr) {}
  skew_heap(T v) : val(v), l(nullptr), r(nullptr) {}
};

template <typename T> skew_heap<T> *meld(skew_heap<T> *a, skew_heap<T> *b) {
  if (!a) return b;
  if (!b) return a;
  if (a->val > b->val) swap(a, b);
  a->r = meld(a->r, b);
  swap(a->l, a->r);
  return a;
}

template <typename T> skew_heap<T> *push(skew_heap<T> *h, T v) {
  skew_heap<T> *p = new skew_heap<T>(v);
  return meld(h, p);
}

template <typename T> skew_heap<T> *pop(skew_heap<T> *h) {
  skew_heap<T> *res = meld(h->l, h->r);
  free(h);
  return res;
}
