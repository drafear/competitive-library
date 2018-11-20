#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
using namespace __gnu_pbds;
template<class T>
class Set : public tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update> {
public:
  // 小さい方からidx番目の要素
  const T& operator[](size_t idx) { return *this->find_by_order(idx); }
  // keyが小さい方から何番目か
  size_t order(const T& key) const { return this->order_of_key(key); }
  size_t order(typename Set<T>::iterator it) const {
    if (it == end(*this)) return this->size();
    return this->order_of_key(*it);
  }
};
