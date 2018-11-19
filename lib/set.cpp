#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
using namespace __gnu_pbds;

// 宣言:
// tree<key,null_type,less<key>,rb_tree_tag,tree_order_statistics_node_update> var_name;
// いきなり長いです。さすがにtypedefするべき
// keyに順序関係の定義された好きな型を入れてね

// 使えること:
// setでできるものは大体できます。insert,erase,iterator関連・swapなど。
// その他に使えるのが、いずれもO(logN)で

// find_by_order 関数
// var_name.find_by_order(k) でk番目（0-indexed）のiteratorを返します。
// order_of_key 関数
// var_name.order_of_key(key)
