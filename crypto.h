#include <inttypes.h>

uint64_t exponent_mod(uint64_t base, uint64_t exponent, uint64_t mod) {
    uint64_t res = 0;
    base = base % mod;

    while (exponent > 0) {
        if (exponent % 2 == 1)
            res = (res + base) % mod;

        base = (base * 2) % mod;
        exponent /= 2;
    }
 
    return res % mod;
}