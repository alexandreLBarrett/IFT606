#include <math.h>
#include <random>
#include <functional>

#include "user.h"
#include "crypto.h"

using namespace std;

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