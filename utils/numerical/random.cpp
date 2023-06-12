#include "../macros.h"

mt19937 rng(static_cast<unsigned>(chrono::steady_clock::now().time_since_epoch().count()));
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

// shuffle(all(a), rng)
// uniform_int_distribution<num>(inc_l, inc_r)(rng);
