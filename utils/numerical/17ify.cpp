#include "../macros.h"
template<typename T> num ssize(const T& x) { return static_cast<num>(x.size()); }
template<typename T> int bit_width(T x) { return numeric_limits<T>::digits - __countl_zero(x); }
template<typename T> T bit_floor(T x) { return x ? T{1} << (bit_width(x) - 1) : 0; }