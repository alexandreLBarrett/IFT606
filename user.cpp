#include "user.h"
#include <math.h>
#include <random>
#include <functional>

using namespace std;

uint64_t User::exponent_mod(uint64_t base, uint64_t exponent, uint64_t mod) const {
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

uint32_t User::generate_x() const {
    auto diff = numeric_limits<uint32_t>::max() - uint32_t{1};
    return rand() % diff + 1;
}

void User::receive_message(const uint64_t message) {
    secret = exponent_mod(message, x, p);
}

uint64_t User::get_h() const {
    return exponent_mod(g, x, p);
}