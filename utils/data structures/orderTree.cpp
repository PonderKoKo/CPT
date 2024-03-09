#include "../macros.h"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
template<typename T> using orderset = tree<T,null_type,less<>,rb_tree_tag,tree_order_statistics_node_update>;
// find_by_order(idx) -> iterator for 0 based idx or end if past the end
// order_of_key(T) -> Count of strictly smaller items